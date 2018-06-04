//
// Created by sebastian on 22.05.18.
//

#include <FactoryMethod.h>
#include <iostream>
#include <memory>

using namespace factoryMethod;

int main() {
    Repository<int> r{1, 2, 3};
    std::cout << r[2];
}