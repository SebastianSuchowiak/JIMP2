//
// Created by sebastian on 16.04.18.
//

#include <Kula.h>
#include <iostream>

int main() {
    auto *k_1 = new Kula(0, 0, 0, 10);
    std::cout << "Pole powierchni kuli: " << k_1->Pole() << "\n" <<
            "Pole przekroju kuli: " << k_1->Kolo::Pole();
}