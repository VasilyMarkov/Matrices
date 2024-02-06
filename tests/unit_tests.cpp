#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "matrices.hpp"
#include <iostream>

using namespace testing;
using namespace matrices;

TEST(Unit, equalOperator) {
    // auto size = 2;
    // std::vector<double> elements = {1, 2, 3, 4};
    // Matrix mat{std::move(elements), size};
    // std::cout << mat << std::endl;
    // EXPECT_EQ(i, 5);
}

TEST(Unit, ctorFromContainer) {
    // auto size = 2;
    // std::vector<double> elements = {1, 2, 3, 4};
    // Matrix mat{std::move(elements), size};
    // std::cout << mat << std::endl;
    // EXPECT_EQ(i, 5);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
