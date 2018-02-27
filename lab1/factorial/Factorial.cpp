//
// Created by mwypych on 02.02.17.
//
#include "Factorial.h"

int factorial(int value) {

    int result = 1;

    if (value >= 13 || value <= -13) {
        return 0;
    }

    if (value > 0) {
        for (int i = 1; i <= value; i++) {
            result *= i;
        }
    } else if (value < 0) {
        for (int i = -1; i >= value; i--) {
            result *= i;
        }
    }

    return result;
}
