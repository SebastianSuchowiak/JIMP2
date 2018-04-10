//
// Created by sebastian on 08.04.18.
//

#include <cstring>
#include "TextPool.h"

namespace pool {

    TextPool::TextPool() = default;

    TextPool::TextPool(TextPool &&other) {

        char* tmp;

        for(auto str_to_swap:other.m_strings){
            tmp = new char[strlen(str_to_swap)];
            strcpy(tmp,str_to_swap);
            this->m_strings.insert(tmp);
            other.m_strings.erase(str_to_swap);
            delete [] str_to_swap;
        }
    };

    TextPool::~TextPool() {
        for (auto str: m_strings) {
            delete [] str;
        };
    };

    TextPool& TextPool::operator=(TextPool &&other) {

        if (this == &other) {
            return *this;
        }

        char* tmp;

        for(auto str_to_swap:other.m_strings){
            tmp = new char[strlen(str_to_swap)];
            strcpy(tmp,str_to_swap);
            this->m_strings.insert(tmp);
            other.m_strings.erase(str_to_swap);
            delete [] str_to_swap;
        }

    };

    TextPool::TextPool(const std::initializer_list<std::string> &elements) {

        bool contains = false;
        char *char_array_to_add;

        for (const std::string &elem: elements) {

            for (const std::string &str: m_strings) {
                if (str == elem) {
                    contains = true;
                    break;
                }
            }

            if (!contains) {
                char_array_to_add = new char[elem.length() + 1];
                strcpy(char_array_to_add, elem.c_str());
                m_strings.insert(char_array_to_add);
            }
            contains = false;
        }
    }

    std::experimental::string_view TextPool::Intern(const std::string &str_to_add) {

        char *new_string;

        for (char *const &str: m_strings) {
            if (str == str_to_add) {
                return str;
            }
        }

        new_string = new char[str_to_add.length() + 1];
        strcpy(new_string, str_to_add.c_str());
        m_strings.insert(new_string);
        return new_string;
    };

    size_t TextPool::StoredStringCount() const {
        return m_strings.size();
    };
}


