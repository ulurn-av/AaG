//
// Created by Andrey Voronin on 23.03.2024.
//

#include "Matrix.hpp"

int main(){
    Matrix<int> A(5, 5);
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            A(i, j) = i+j;
        }
    }

    // Checking access to elements
    cout << "Checking access to elements\n";
    cout << A << "\n";
    cout << "cols: " << A.get_cols() << endl;
    cout << "rows: " << A.get_rows() << endl;

    // Checking the copy
    cout << "Checking the copy\n";
    Matrix<int> B(6, 6);
    Matrix<int> C(B);
    cout << "Is it equal:" << (B==C) << "\n";
    B(0, 0) = 10;
    cout << "Is it equal:" << (B==C) << "\n";

    // Checking Assignment
    cout << "Checking Assignment" << "\n";
    B = A;
    cout << B << endl;
    cout << "Is it equal:" << (B==A) << "\n";
    B(0, 0) = -1;
    cout << "Is it equal:" << (B==A) << "\n";

    // Transpose
    int cnt = 0;
    for(int i = 0; i < A.get_rows(); ++i){
        for(int j = 0; j< A.get_cols(); ++j){
            A(i, j) = cnt;
            cnt += 1;
        }
    }
    cout << A << "\n";
    cout << A.transpose() << "\n";

    // SubMatrix
    cout << A << endl;
    cout << A.sub_matrix(1, 1, 3, 3) << endl;

    // eye and zeros
    cout << A << endl;
    A = Matrix<int>::eye(A.get_cols());
    cout << A << endl;
    A = Matrix<int>::zeros(A.get_rows(), A.get_cols());
    cout << A << endl;

    // Concatenation Horizontal
    Matrix<int> D(2, 3);
    Matrix <int> E(2, 2);
    cnt = 0;
    for(int i = 0; i < D.get_rows(); ++i){
        for(int j = 0; j < D.get_cols(); ++j){
            D(i, j) = cnt;
            cnt += 1;
        }
    }
    cnt = 0;
    for(int i = 0; i < E.get_rows(); ++i){
        for(int j = 0; j < E.get_cols(); ++j){
            E(i, j) = cnt;
            cnt += 1;
        }
    }
    cout << D << "\n";
    cout << E << "\n";
    cout << D.horizontal_concatenate(E) << endl;

    // Concatenation Vertical
    Matrix<int> F(4, 2);
    Matrix <int> G(2, 2);
    cnt = 0;
    for(int i = 0; i < F.get_rows(); ++i){
        for(int j = 0; j < F.get_cols(); ++j){
            F(i, j) = cnt;
            cnt += 1;
        }
    }
    cnt = 0;
    for(int i = 0; i < G.get_rows(); ++i){
        for(int j = 0; j < G.get_cols(); ++j){
            G(i, j) = cnt;
            cnt += 1;
        }
    }
    cout << F << endl;
    cout << G << endl;
    cout << F.vertical_concatenate(G) << endl;

    // Arithmetic operations
    Matrix<int> A1 = Matrix<int>::eye(3);
    A1 = A1*3;
    cout << A1 << endl;
    Matrix<int> A2(3, 3);
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            A2(i, j) = 1;
        }
    }
    cout << (A1 + A2) << endl;
    cout << (A1 - A2) << endl;
    cout << -A1 << endl;
    cout << A1 << endl << A2 << endl;
    cout << A1*A2 << endl;
    Matrix<int> A3(3, 1);
    A3(0, 0) = 1;
    A3(1, 0) = 2;
    A3(2, 0) = 3;
    cout << A3 << endl;
    cout << A1*A3 << endl;
    return 0;
}