#include <iostream>
#include "gtest/gtest.h"

int main(int argc, char** argv) {
    std::cout << "running main in test directory" << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}