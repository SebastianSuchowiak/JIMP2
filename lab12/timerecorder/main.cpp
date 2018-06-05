//
// Created by sebastian on 01.06.18.
//

#include <TimeRecorder.h>
#include <iostream>

int test_int() {
    return 5;
}

class TestObj {

public:
    std::string operator()() {
        return "5";
    }
};

using namespace profiling;

int main() {

    TestObj testObj;
    std::cout << Void(test_int);
    std::cout << TimeRecorder([]() {
        return 5;
    }).first;
}