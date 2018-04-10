//
// Created by sebastian on 08.04.18.
//

#include "Matrix.h"

namespace algebra {
    Matrix::Matrix() {
        m_columns_num = 0;
        m_rows_num = 0;
    }

    Matrix::Matrix(size_t rows, size_t columns) {

        m_rows_num = (size_t) rows;
        m_columns_num = (size_t) columns;
        m_values = new complex *[m_rows_num];

        for (int row_index = 0; row_index < m_rows_num; ++row_index) {
            m_values[row_index] = new complex[m_columns_num];
        }
    }

    Matrix::Matrix(std::initializer_list<vector<complex>> init_list) {

        int current_row = 0;
        m_rows_num = init_list.size();
        m_values = new complex *[m_rows_num];

        for (auto row: init_list) {
            m_columns_num = row.size();
            m_values[current_row] = new complex[m_columns_num];
            for (int current_column = 0; current_column < m_columns_num; current_column++) {
                m_values[current_row][current_column] = row[current_column];
            }
            current_row++;
        }
    }

    Matrix &Matrix::operator=(const Matrix &other) {

        if (this->m_values == other.m_values) {
            return *this;
        }

        for (int current_row = 0; current_row < m_rows_num; ++current_row) {
            delete [] m_values[current_row];
        }
        delete [] m_values;

        m_rows_num = other.m_rows_num;
        m_columns_num = other.m_columns_num;
        m_values = new complex *[m_rows_num];

        for (int current_row = 0; current_row < m_rows_num; ++current_row) {
            m_values[current_row] = new complex[m_columns_num];
            std::copy(other.m_values[current_row],other.m_values[current_row] + m_columns_num, m_values[current_row]);
        }
    }

    Matrix::Matrix(const Matrix &other) {

        m_rows_num = other.m_rows_num;
        m_columns_num = other.m_columns_num;
        m_values = new complex *[m_rows_num];

        for (int current_row = 0; current_row < m_rows_num; ++current_row) {
            m_values[current_row] = new complex[m_columns_num];
            std::copy(other.m_values[current_row],other.m_values[current_row] +m_columns_num, m_values[current_row]);
        }

    }

    Matrix::~Matrix() {
        for (int current_row = 0; current_row < m_rows_num; ++current_row) {
            delete [] m_values[current_row];
        }
        delete [] m_values;
    }

    std::pair<size_t, size_t> Matrix::Size() const {
        return {m_columns_num, m_rows_num};
    }

    string Matrix::Print() const {

        string parsed_matrix = "[";
        std::stringstream ss;

        for (int current_row = 0; current_row < m_rows_num; ++current_row) {
            for (int current_column = 0; current_column < m_columns_num; ++current_column) {

                ss << m_values[current_row][current_column].real() << "i" << m_values[current_row][current_column].imag();

                if (current_row != m_rows_num - 1 && current_column == m_columns_num - 1) {
                    ss << "; ";
                } else if (current_row != m_rows_num - 1 || current_column != m_columns_num - 1) {
                    ss << ", ";
                }
            }
        }
        parsed_matrix += ss.str();

        return parsed_matrix + "]";
    }


    Matrix Matrix::Sub(Matrix other) const {

        if (this->Size() != other.Size()) {
            return Matrix(0,0);
        }

        Matrix new_matrix;
        new_matrix.m_columns_num = m_columns_num;
        new_matrix.m_rows_num = m_rows_num;
        new_matrix.m_values = new complex*[m_columns_num];

        for (int current_row = 0; current_row < m_columns_num; ++current_row) {
            new_matrix.m_values[current_row] = new complex[m_rows_num];
            for (int current_column = 0; current_column < m_rows_num; ++current_column) {
                new_matrix.m_values[current_row][current_column] = m_values[current_row][current_column] - other.m_values[current_row][current_column];
            }
        }

        return new_matrix;
    }

    Matrix Matrix::Pow(int exponent) const {

        if (m_columns_num != m_rows_num) {
            return Matrix(0, 0);
        }

        Matrix new_matrix(m_columns_num, m_rows_num);

        if (exponent == 0) {
            for (int current_row = 0; current_row < m_rows_num; ++current_row) {
                for (int current_column = 0; current_column < m_columns_num; ++current_column) {
                    if (current_column == current_row) {
                        new_matrix.m_values[current_row][current_column] = 1.;
                    } else {
                        new_matrix.m_values[current_row][current_column] = 0.;
                    }
                }
            }
        } else if (exponent == 1) {
            new_matrix = *this;
        } else {
            new_matrix = *this;
            for (int i = 0; i < exponent - 1; ++i) {
                new_matrix = new_matrix.Mul(*this);
            }
        }

        return new_matrix;
    }

    Matrix Matrix::Mul(Matrix other) const {

        if (m_columns_num != other.m_rows_num) {
            return  Matrix(0, 0);
        }

        Matrix new_matrix(m_rows_num, other.m_columns_num);
        complex new_value = 0.;

        for (int current_row = 0; current_row < new_matrix.m_rows_num; ++current_row) {
            for (int current_column = 0; current_column < new_matrix.m_columns_num; ++current_column) {
                for (int k = 0; k < m_columns_num; ++k) {
                    new_value += m_values[current_row][k] * other.m_values[k][current_column];
                }
                new_matrix.m_values[current_row][current_column] = new_value;
                new_value = 0.;
            }
        }

        return new_matrix;
    }

    Matrix Matrix::Add(Matrix other) const {

        if (this->Size() != other.Size()) {
            return Matrix(0,0);
        }

        Matrix new_matrix;
        new_matrix.m_columns_num = m_columns_num;
        new_matrix.m_rows_num = m_rows_num;
        new_matrix.m_values = new complex*[m_columns_num];

        for (int current_row = 0; current_row < m_columns_num; ++current_row) {
            new_matrix.m_values[current_row] = new complex[m_rows_num];
            for (int current_column = 0; current_column < m_rows_num; ++current_column) {
                new_matrix.m_values[current_row][current_column] = m_values[current_row][current_column] + other.m_values[current_row][current_column];
            }
        }

        return new_matrix;
    }
}
