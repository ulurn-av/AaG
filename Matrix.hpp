//
// Created by Andrey Voronin on 23.03.2024.
//

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

template<typename T>
class Matrix {
public:
    // Конструктор пустой матрицы
    Matrix(){
        this->rows = 0;
        this->cols = 0;
    };

    // Конструктор матрицы заданных размеров
    Matrix(size_t rows, size_t cols){
        vector<vector<T> > matrix(rows, vector<T>(cols, 0));
        this->data = matrix;
        this->rows = rows;
        this->cols = cols;
    };

    // Конструктор матрицы из вектора векторов
    Matrix(const vector<vector<T> >& v){
        this->data = v;
        this->rows = v.size();
        this->cols = v[0].size();
    };

    // Конструктор копирования
    Matrix(const Matrix<int> &other){
        this->data = other.data;
        this->cols = other.cols;
        this->rows = other.rows;
    };

    // Оператор присваивания
    Matrix<T>& operator=(const Matrix<T>& other){
        this->cols = other.cols;
        this->rows = other.rows;
        this->data = other.data;
        return *this;
    };

    // Доступ к элементу (i, j)
    T& operator()(size_t i, size_t j){
        if(i >= rows || j >= cols)
            throw out_of_range("Index out of the range");
        return data[i][j];
    };

    // Доступ к элементу (i, j) для константной матрицы
    const T& operator()(size_t i, size_t j) const {
        if(i >= rows || j >= cols)
            throw out_of_range("Index out of the range");
        return data[i][j];
    };

    // Получение количества строк
    size_t get_rows() const{
        return data.size();
    };

    // Получение количества столбцов
    size_t get_cols() const{
        return data[0].size();
    };

    // Сравнение матриц
    bool operator==(const Matrix<T>& other) const{
        return (other.rows == this->rows && other.cols == this->cols && other.data == this->data);
    };

    // Сравнение матриц
    bool operator!=(const Matrix<T>& other) const{
        return !(other.rows == this->rows && other.cols == this->cols && other.data == this->data);
    };

    // Умножение матрицы на элемент
    Matrix<T> operator*(const T& x) const{
        Matrix<T> res = Matrix(this->data);
        for(size_t i = 0; i < rows; ++i){
            for(size_t j = 0; j < cols; ++j){
                res(i, j) *= x;
            }
        }
        return res;
    };

    // Сложение матриц
    Matrix<T> operator+(const Matrix<T>& other) const{
        if(other.rows != rows || other.cols != cols)
            throw invalid_argument("Matrices have different dimensions");
        Matrix<T> res = Matrix(this->data);
        for(size_t i = 0; i < rows; ++i){
            for(size_t j = 0; j < cols; ++j){
                res(i, j) += other(i, j);
            }
        }
        return res;
    };

    // Вычитание матриц
    Matrix<T> operator-(const Matrix<T>& other) const{
        if(other.rows != rows || other.cols != cols)
            throw invalid_argument("Matrices have different dimensions");
        Matrix<T> res = Matrix(this->data);
        for(size_t i = 0; i < rows; ++i){
            for(size_t j = 0; j < cols; ++j){
                res(i, j) -= other(i, j);
            }
        }
        return res;
    };

    // Отрицание матрицы
    Matrix<T> operator-() const{
        Matrix<T> res = Matrix(this->data);
        for(size_t i = 0; i < rows; ++i){
            for(size_t j = 0; j < cols; ++j){
                res(i,j) = -res(i,j);
            }
        }
        return res;
    };

    // Умножение матриц
    Matrix<T> operator*(const Matrix<T>& other) const{
        if(cols != other.rows)
            throw invalid_argument("The number of columns of the first matrix must match the number of rows of the second matrix");
        Matrix<T> res(this->rows, other.cols);
        for(int i = 0; i < this->rows; ++i){
            for(int j = 0; j < other.cols; ++j){
                for(int k = 0; k < this->cols; ++k){
                    res(i,j) += this->data[i][k]* other(k, j);
                }
            }
        }
        return res;
    };

    // Транспонирование матрицы
    Matrix<T> transpose() const{
        Matrix<T> res = Matrix(rows, cols);
        for(size_t i = 0; i < rows; ++i){
            for(size_t j = 0; j < cols; ++j){
                res.data[i][j] = this->data[j][i];
            }
        }
        return res;
    };

    // Получение подматрицы, начиная с позиции (row, col) и размерами (rows, cols)
    Matrix<T> submatrix(size_t row, size_t col, size_t rows, size_t cols) const{
        if(row >= this->rows || row+rows >= this->rows || col >= this->cols || col+cols >= this->cols)
            throw out_of_range("Index out of the range");

        Matrix<T> res = Matrix(rows, cols);
        for(size_t i = 0; i < rows; ++i){
            for(size_t j = 0; j < cols; ++j){
                res(i, j) = data[i+row][j+col];
            }
        }
        return res;
    };

    // Создание единичной матрицы
    static Matrix<T> eye(size_t n){
        Matrix<T> res = Matrix(n, n);
        for(size_t i = 0; i < n; ++i)
            res(i, i) = 1;
        return res;
    };

    // Создание нулевой матрицы
    static Matrix<T> zeros(size_t rows, size_t cols){
        return Matrix(rows, cols);
    };

    // Конкатенация матриц по горизонтали
    Matrix<T> horizontal_concatenate(const Matrix<T>& other) const{
        if(rows != other.rows)
            throw invalid_argument("The number of rows of the first matrix must match the number of rows of the second matrix");
        Matrix<T> res = Matrix(rows, cols+other.cols);
        for(size_t i = 0; i < rows; ++i){
            for(size_t j = 0; j < cols; ++j){
                res(i, j) = data[i][j];
            }
        }
        for(size_t i = 0; i < rows; ++i){
            for(size_t j = cols; j < cols+other.cols; ++j){
                res(i, j) = other.data[i][j-cols];
            }
        }
        return res;
    };

    // Конкатенация матриц по вертикали
    Matrix<T> vertical_concatenate(const Matrix<T>& other) const{
        if(cols != other.cols)
            throw invalid_argument("The number of cols of the first matrix must match the number of cols of the second matrix");
        Matrix<T> res = Matrix(rows+other.rows, cols);
        for(size_t i = 0; i < rows; ++i){
            for(size_t j = 0; j < cols; ++j){
                res(i, j) = data[i][j];
            }
        }
        for(size_t i = rows; i < rows+other.rows; ++i){
            for(size_t j = 0; j < cols; ++j){
                res(i, j) = other.data[i-rows][j];
            }
        }
        return res;
    };

    // «Красивый» вывод матрицы
    template <typename Tstream>
    friend ostream &operator<<(ostream &out, const Matrix<Tstream>& m);

private:
    size_t rows;                      // количество строк
    size_t cols;                      // количество столбцов
    vector<vector<T> > data; // данные матрицы
};

template <typename Tstream>
ostream &operator<<(ostream &out, const Matrix<Tstream>& m) {
    const int MAX_NUM_DIGITS = 5;
    out << endl;
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            out << setw(MAX_NUM_DIGITS) << m(i, j) << " ";
        }
        out << endl;
    }
    return out;
}