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

TEST(Matrix, subtractionAssignmentOperator) {
    std::vector<double> vec = {2,4,6,8};
    matr_t<double> m{std::begin(vec), std::end(vec)};
    m -= 2;
    std::vector<double> ref = {0,2,4,6};
    matr_t<double> m_ref{std::begin(ref), std::end(ref)};
    EXPECT_TRUE(m == m_ref);
}

TEST(Matrix, divisionAssignmentOperator) {
    std::vector<double> vec = {2,4,6,8};
    matr_t<double> m{std::begin(vec), std::end(vec)};
    m /= 2;
    std::vector<double> ref = {1,2,3,4};
    matr_t<double> m_ref{std::begin(ref), std::end(ref)};
    EXPECT_TRUE(m == m_ref);

    std::vector<double> vec1 = {1,1,1,1};
    matr_t<double> m1{std::begin(vec1), std::end(vec1)};
    m1 /= 3;
    std::vector<double> ref1 = {0.33333,0.33333,0.33333,0.33333};
    matr_t<double> m_ref1{std::begin(ref1), std::end(ref1)};
    EXPECT_TRUE(m1 == m_ref1);
}

TEST(Matrix, gauss) {
    std::vector<double> vec = {2,4,1,5,2,1,2,3,4};
    matr_t<double> m{std::begin(vec), std::end(vec)};
    std::cout << m << std::endl;
    m.gauss();
    std::cout << m;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
