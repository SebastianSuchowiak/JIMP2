//
// Created by sebastian on 27.02.18.
//

#include "Palindrome.h"

bool is_palindrome(std::string str) {

    size_t size = str.size();

    for (int i = 0; i < size / 2; ++i) {
        if (str[i] != str[size - 1 - i]) {
            return false;
        }
    }
    return true;
}
