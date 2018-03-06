//
// Created by sebastian on 06.03.18.
//

#include "Array2D.h"

bool ArgumentsInRange(int n_rows, int n_columns);

int **Array2D(int n_rows, int n_columns) {

    if (ArgumentsInRange(n_rows, n_columns)) {
        return nullptr;
    }

    int **array = new int*[n_rows];

    for (int i = 0; i < n_rows; ++i) {
        array[i] = new int[n_columns];
        for (int j = 0; j < n_columns; ++j) {
            array[i][j] = i * n_columns + j + 1;
        }
    }

    return array;
}

bool ArgumentsInRange(int n_rows, int n_columns) { return n_columns <= 0 || n_rows <= 0; }

int** NewArray2D(int n_rows, int n_columns) {

    if (ArgumentsInRange(n_rows, n_columns)) {
        return nullptr;
    }

    int **array = new int*[n_rows];

    for (int i = 0; i < n_rows; ++i) {
        array[i] = new int[n_columns];
    }

    return array;
}

void FillArray2D(int n_rows, int n_columns, int** array) {

    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_columns; ++j) {
            array[i][j] = i * n_columns + j + 1;
        }
    }
}

void DeleteArray2D(int **array, int n_rows, int n_columns) {

    for (int i = 0; i < n_rows; ++i) {
        delete [] array[i];
    }

    delete [] array;
}