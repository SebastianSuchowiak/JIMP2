//
// Created by sebastian on 08.04.18.
//

#ifndef JIMP_EXERCISES_TEXTPOOL_H
#define JIMP_EXERCISES_TEXTPOOL_H

#include <initializer_list>
#include <string>
#include <experimental/string_view>
#include <set>

namespace pool {
    class TextPool {

    public:

        TextPool();
        TextPool(TextPool&& other);
        TextPool(const std::initializer_list<std::string> &elements);
        ~TextPool();
        TextPool& operator=(TextPool&& other);

        std::experimental::string_view Intern(const std::string &str);
        size_t StoredStringCount() const;

    public:

        std::set<char*> m_strings;

    };
}



#endif //JIMP_EXERCISES_TEXTPOOL_H
