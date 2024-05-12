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
        int inv = mod(mod_inverse(other.value));
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
        Fp<p> inv(mod_inverse(other.value));
        this->value = mod(this->value*inv.value);
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

    long long mod(long long x){
        return ((x%p)+p)%p;
    }

    long long binpow(long long a, long long n) {
        if (n == 0)
            return 1;
        if (n % 2 == 1)
            return mod(binpow(a, n - 1) * a);
        else {
            long long b = mod(binpow(a, n / 2));
            return mod(b * b);
        }
    }

    long long mod_inverse(long long x){
        return binpow(x, p - 2);
    }
};

template <int Tstream>
std::ostream &operator<<(std::ostream &out, const Fp<Tstream>& el) {
    out << el.val();
    return out;
}