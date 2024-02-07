#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "matrices.hpp"
#include <iostream>

using namespace testing;
using namespace matrices;

TEST(Matrix, equalOperator) {
    std::vector<double> ref = {2,4,1,5,2,1,2,3,4};
    matr_t<double> m_ref{std::begin(ref), std::end(ref)};

    matr_t<double> m_vec{std::begin(ref), std::end(ref)};
    EXPECT_TRUE(m_vec == m_ref);

    std::vector<double> ref_eps = {2+eps,4,1,5,2-eps,1,2,3,4};
    matr_t<double> m_ref_eps{std::begin(ref_eps), std::end(ref_eps)};
    EXPECT_FALSE(m_vec == m_ref_eps);
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
