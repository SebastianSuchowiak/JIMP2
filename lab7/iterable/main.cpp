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
    vector<int> vi{4, 77, -91};
    vector<string> vs{"4", "9991", "adfskld"};
    Zipper z = Zipper(vi, vs);
    IterableIteratorWrapper t = IterableIteratorWrapper(
            (std::make_unique<ZipperIterator>(ZipperIterator(vi.begin(), vs.begin(), vi.end(), vs.end()))));
    ZipperIterator *d = z.m_dx;
    std::cout << (d->m_current_right);
}