//
// Created by sebastian on 13.03.18.
//

#include <iostream>
#include "XorCypherBreaker.h"

std::string XorCypherBreaker(const std::vector<char> &cryptogram,
                             int key_length,
                             const std::vector<string> &dictionary) {

    std::string key;
    int index = 0;
    char deciphered_letter;
    std::string deciphered_word;
    std::vector<std::string> deciphered_words;
    int counter = 0;

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            for (int k = 0; k < 26; ++k) {
                key = j + 97;11
                key += k + 97;
                key += i + 97;

                for (char letter: cryptogram) {
                    deciphered_letter = letter ^ key[index];
                    if (deciphered_letter >= 'a' && deciphered_letter <= 'z') {
                        deciphered_word += deciphered_letter;
                    } else if (!deciphered_word.empty()){
                        deciphered_words.insert(deciphered_words.begin(), deciphered_word);
                        if (isInDict(deciphered_word, dictionary)) {
                            counter++;
                        }
                        deciphered_word.clear();
                    }
                    ++index %= key_length;

                    if (deciphered_words.size() % 20 == 0) {
                        if (counter * 100.0 / deciphered_words.size() < 10.0) {
                            break;
                        }
                    }
                }

                if (counter * 100.0 / deciphered_words.size() > 25.0) {
                    return key;
                }

                counter = 0;
                deciphered_word.clear();
                deciphered_words.clear();
            }
        }

    }
}

bool isInDict(const std::string word, const std::vector<string> &dictionary) {
    return  (find(dictionary.begin(),dictionary.end(),word) != dictionary.end());
}
