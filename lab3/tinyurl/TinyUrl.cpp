//
// Created by sebastian on 18.03.18.
//

#include "TinyUrl.h"

std::unique_ptr<tinyurl::TinyUrlCodec> tinyurl::Init() {
    std::unique_ptr<tinyurl::TinyUrlCodec> newPointer = std::make_unique<tinyurl::TinyUrlCodec>();
    return newPointer;
}

void tinyurl::NextHash(std::array<char, 6> *state) {

    int surplus = 1;

    for (int i = state->size() - 1; i >= 0 && surplus > 0; i--, surplus--) {
        if ((*state)[i] == '9') {
            (*state)[i] = 'A';
        } else if ((*state)[i] == 'Z') {
            (*state)[i] = 'a';
        } else if ((*state)[i] == 'z') {
            (*state)[i] = '0';
            surplus += 1;
        } else {
            (*state)[i] += 1;
        }
    }
}

std::string tinyurl::Encode(const std::string &url, std::unique_ptr<TinyUrlCodec> *codec) {
    std::string tinyurl = "https://goo.gl/";;

    (*codec)->fullUrl = url;

    for(char character: (*codec)->shortUrl)
        tinyurl += character;

    return tinyurl;
}

std::string tinyurl::Decode(const std::unique_ptr<TinyUrlCodec> &codec, const std::string &hash) {
    return codec->fullUrl;
}