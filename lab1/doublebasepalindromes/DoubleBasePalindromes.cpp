//
// Created by sebastian on 05.03.18.
//

#include "DoubleBasePalindromes.h"

uint64_t DoubleBasePalindromes(int max_value_exclusive) {

    uint64_t palindromes_sum = 0;
    int num = 1;
    std::string str;

    for (int i = 1; num < max_value_exclusive; ++i) {
        num = makeDecimalPalindrome(i, true);
        str = std::to_string(num);
        if (is_palindrome(str) && num < max_value_exclusive) {
            palindromes_sum += num;
        }

    }

    num = 1;

    for (int i = 1; num < max_value_exclusive; ++i) {
        num = makeDecimalPalindrome(i, false);
        str = std::to_string(num);
        if (is_palindrome(str) && num < max_value_exclusive) {
            palindromes_sum += num;
        }
    }

    return palindromes_sum;
}

int makeDecimalPalindrome(int n, bool oddLength) {

    int res = n;

    if (oddLength) {
        n /= 2;
    }

    while (n > 0) {
        res = res * 2 + n % 2;
        n /= 2;
    }

    return res;
}

bool is_palindrome(std::string str) {

    size_t size = str.size();

    for (int i = 0; i < size / 2; ++i) {
        if (str[i] != str[size - 1 - i]) {
            return false;
        }
    }
    return true;
}
