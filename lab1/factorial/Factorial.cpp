//
// Created by mwypych on 02.02.17.
//
#include "Factorial.h"

bool ArgumentInRange(int value);

int Factorial(int value) {

    int result = 1;

    if (ArgumentInRange(value)) {
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

bool ArgumentInRange(int value) { return value >= 13 || value <= -13; }
