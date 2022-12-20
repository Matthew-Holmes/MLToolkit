#include <iostream>
#include "gtest/gtest.h"

int main(int argc, char** argv) {
    std::cout << "running main in test directory" << std::endl;
    std::cout << "remember to add test sources to CMakeLists.txt" << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}