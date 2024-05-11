#pragma once
#include "Matrix.hpp"
#include "Fp.hpp"

template<int p>
class HammingCode {
public:
    HammingCode(size_t m){
        this->n = ((int)pow(p, m)-1)/(p-1);
        this->k = n - m;
        this->m = m;
        generate_matrices();
    };

    Matrix<Fp<p> > get_H() const{
        return H;
    };
    Matrix<Fp<p> > get_G() const{
        return G;
    };

private:
    size_t n;
    size_t k;
    size_t m;
    Matrix<Fp<p> > H;
    Matrix<Fp<p> > G;

    vector<Fp<p> > convertToP(int num, int m) {
        vector<Fp<p> > result(m, 0);
        for(int i = 0; i < m; ++i){
            result[i] = Fp<p>(num % p);
            num /= p;
        }
        reverse(result.begin(), result.end());
        return result;
    }

    vector<Fp<p> > mulVector(vector<Fp<p> > v, int num){
        vector<Fp<p> > result(v.size(), 0);
        for(size_t i = 0; i < v.size(); ++i){
            result[i] = v[i] * num;
        }
        return result;
    }

    void generate_matrices(){
        Matrix<Fp<p> > eye = Matrix<Fp<p> >::eye(m);
        Matrix<Fp<p> > A(m, k);
        int counter = 0;

        vector<Fp<p> > v = vector<Fp<p> >(m, 0);
        int limit = (int)pow(p, m) - 1;
        int flag = 0;
        for(size_t i = 1; i <= limit; ++i){
            v = convertToP(i, m);
            for(size_t j = 1; j < p; ++j){
                for(size_t l = 0; l < eye.get_cols(); ++l){
                    vector<Fp<p> > v1 = eye.get_col(l);
                    v1 = mulVector(v1, j);
                    if(v == v1){
                        flag = 1;
                        break;
                    }
                }
                if(flag)
                    break;
                for(size_t l = 0; l < A.get_cols(); ++l){
                    vector<Fp<p> > v1 = A.get_col(l);
                    v1 = mulVector(v1, j);
                    if(v == v1){
                        flag = 1;
                        break;
                    }
                }
                if(flag)
                    break;
            }
            if(flag){
                flag = 0;
                continue;
            }
            for(size_t j = 0; j < m; ++j){
                A(j, counter) = v[j];
            }
            counter += 1;
        }
        this->H = A.horizontal_concatenate(eye);
        Matrix<Fp<p> > At = A.transpose();
        At = At * Fp<p>(-1);
        this->G = Matrix<Fp<p> >::eye(k).horizontal_concatenate(At);
    };
};