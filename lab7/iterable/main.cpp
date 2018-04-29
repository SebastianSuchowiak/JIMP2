//
// Created by sebastian on 28.04.18.
//

#include <string>
#include <vector>
#include <memory>
#include <Iterable.h>
#include <iostream>

using namespace utility;
using ::std::vector;
using ::std::string;

int main() {
    vector<string> vs {"4", "9991", "adfskld"};
    Enumerate x = Enumerate(vs);
    IterableIteratorWrapper m = x.cbegin();
    IterableIteratorWrapper e = x.cend();
    std::cout << m.operator*().first << "  " << m.operator*().second << "\n";
    ++m;
    bool t = m.operator!=(e);
    std::cout << m.operator*().first << "  " << m.operator*().second << "\n";
    ++m;
    std::cout << m.operator*().first << "  " << m.operator*().second << "\n";
    ++m;
    std::cout << m.operator*().first << "  " << m.operator*().second << "\n";
}