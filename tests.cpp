//
// Created by Andrey Voronin on 23.03.2024.
//

#include "HammingCode.hpp"

int main(){

    Fp<7> t1(1633411);
    Fp<7> t2(1633410);

    cout << (t1 / t2) << endl;

    cout << t1 << endl;
    cout << t2 << endl;

    Fp<3> a(2);
    Fp<3> b(-2);
    cout << a << " " << b << endl;
    b *= Fp<3>(-13);
    cout << b << endl;
    b /= Fp<3>(-10);
    cout << b << endl;

    HammingCode<3> H1(2);
    cout << H1.get_H() << endl;
    cout << H1.get_G() << endl;

    HammingCode<2> H2(3);
    cout << H2.get_H() << endl;
    cout << H2.get_G() << endl;

    return 0;
}