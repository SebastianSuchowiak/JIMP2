//
// Created by suchseba on 27.02.18.
//

#include "ReverseString.h"

std::string reverse(std::string str) {

    const char *characters = str.c_str();
    size_t size = str.size();
    std::string reversed_characters;

    if (size <= 1) {
        return str;
    }

    for (int i = 1; i < size; i++) {
        reversed_characters += characters[i];
    }

    return reverse(reversed_characters) + characters[0];
}