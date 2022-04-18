#include "gtest/gtest.h"

#include <algorithm>
#include <iostream>

TEST(TestMyLib, TestInit) {
    std::cout << "hello tests" << std::endl;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
