#pragma once
#include <iostream>


class Subject {
public:
    int f1() {
        std::cout << "f1" << std::endl;
        return 0;
    }

    int f2(int arg1, int arg2) {
        std::cout << "f2: " << arg1 << ", " << arg2 << std::endl;
        return arg1 + arg2;
    }

    int f3(int arg1, int arg2, int arg3) {
        std::cout << "f3: " << arg1 << ", " << arg2 << ", " << arg3 << std::endl;
        return arg1 + arg2 + arg3;
    }
};