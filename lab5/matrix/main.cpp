//
// Created by sebastian on 08.04.18.
//

#include <iostream>
#include <complex>
#include <vector>
#include "Matrix.h"

int main() {
    algebra::Matrix m1{{1., 0.}, {0., 1.}};
    algebra::Matrix m2{{7. + 1.0i, 12. + 1.3i, 1.5 + 3.7i, 1.0i}, {7. + 1.0i, 12. + 1.3i, 1.5 + 3.7i, 1.0i}};

    std::cout << m1.Pow(11).Print();
}