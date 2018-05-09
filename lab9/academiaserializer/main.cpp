//
// Created by sebastian on 08.05.18.
//

#include <Serialization.h>
#include <sstream>
#include <iostream>

using namespace academia;

int main() {
    std::stringstream out;
    XmlSerializer serializer{&out};
    Room r1 {100167, "429", Room::Type::LECTURE_HALL};
    Room r2 {100168, "208", Room::Type::COMPUTER_LAB};
    Room r3 {100169, "216", Room::Type::COMPUTER_LAB};
    Building building {11, "C2", {r1, r2, r3}};
    building.Serialize(&serializer);

}