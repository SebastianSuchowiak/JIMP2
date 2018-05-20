//
// Created by sebastian on 15.05.18.
//

#include <Algo.h>
#include <iostream>

int main() {
    std::vector<std::tuple<int, int, int>> v {{5, 3, 0}, {1, 4, -1}, {5, 2, 5}};
    algo::SortByThirdInPlace(&v);
    std::cout << std::get<2>(v[0]);
}