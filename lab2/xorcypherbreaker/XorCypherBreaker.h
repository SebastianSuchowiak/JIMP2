//
// Created by sebastian on 13.03.18.
//

#ifndef JIMP_EXERCISES_XORCYPHERBREAKER_H
#define JIMP_EXERCISES_XORCYPHERBREAKER_H

#include <string>
#include <vector>
#include <algorithm>
using std::find;
using std::vector;
using std::string;

std::string XorCypherBreaker(const std::vector<char> &cryptogram,
                             int key_length,
                             const std::vector<string> &dictionary);
bool isInDict(std::string word, const std::vector<string> &dictionary);


#endif //JIMP_EXERCISES_XORCYPHERBREAKER_H
