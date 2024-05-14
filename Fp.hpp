#pragma once
#include <iostream>
#include <math.h>

template<int p>
class Fp {
public:
    Fp(int x = 0){
        this->value = mod(x);
    };

    int val() const{
        return value;
    };

    Fp<p>& operator=(int x){
        this->value = mod(x);
        return *this;
    };

    Fp<p> operator+(const Fp<p>& other) const{
        Fp<p> Space(this->value + other.value);
        return Space;
    };
    Fp<p> operator-(const Fp<p>& other) const{
        Fp<p> Space(this->value - other.value);
        return Space;
    };
    Fp<p> operator*(const Fp<p>& other) const{
        Fp<p> Space(this->value * other.value);
        return Space;
    };
    Fp<p> operator/(const Fp<p>& other) const{
        int inv = mod_inverse(other.value);
        if (inv == 0)
            throw invalid_argument("This element has no inverse element in this field!");
        Fp<p> Space(this->value * inv);
        return Space;
    };
    Fp<p> operator-() const{
        Fp<p> Space;
        Space = mod(this->value * (-1));
        return Space;
    };

    Fp<p>& operator+=(const Fp<p>& other){
        this->value = mod(this->value+other.value);
        return *this;
    };
    Fp<p>& operator-=(const Fp<p>& other){
        this->value = mod(this->value - other.value);
        return *this;
    };
    Fp<p>& operator*=(const Fp<p>& other){
        this->value = mod(this->value * other.value);
        return *this;
    };
    Fp<p>& operator/=(const Fp<p>& other){
        int inv = mod_inverse(other.value);
        if (inv == 0)
            throw invalid_argument("This element has no inverse element in this field!");
        this->value = mod(this->value*inv);
        return *this;
    };

    bool operator==(const Fp<p>& other) const{
        return this->value == other.value;
    };
    bool operator!=(const Fp<p>& other) const{
        return this->value != other.value;
    };

    template <int Tstream>
    friend std::ostream &operator<<(std::ostream &out, const Fp<Tstream>& el);
private:
    int value;

    int mod(int x) const{
        return ((x%p)+p)%p;
    }

    int mod_inverse(int x) const{
        for(int i = 0; i < p; ++i){
            if(mod(x*i) == 1)
                return i;
        }
        return 0;
    }
};

template <int Tstream>
std::ostream &operator<<(std::ostream &out, const Fp<Tstream>& el) {
    out << el.val();
    return out;
}