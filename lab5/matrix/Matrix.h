//
// Created by sebastian on 08.04.18.
//

#ifndef JIMP_EXERCISES_MATRIX_H
#define JIMP_EXERCISES_MATRIX_H

#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <complex>

using std::string;
using std::vector;

typedef std::complex<double> complex;
namespace algebra {

    class Matrix {

    public:
        Matrix();

        ~Matrix();

        Matrix(size_t rows, size_t columns);

        Matrix(std::initializer_list<vector<complex>>);

        Matrix(const Matrix &other);

        Matrix & operator=(const Matrix &other);

        string Print() const;

        Matrix Add(Matrix other) const;

        Matrix Sub(Matrix other) const;

        Matrix Mul(Matrix other) const;

        Matrix Pow(int exponent) const;

        std::pair<size_t , size_t > Size() const;

    private:

        complex** m_values;
        size_t m_rows_num;
        size_t m_columns_num;
    };
}

#endif //JIMP_EXERCISES_MATRIX_H
