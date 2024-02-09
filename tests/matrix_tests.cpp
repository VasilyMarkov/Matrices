#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "matrices.hpp"
#include <iostream>

using namespace testing;
using namespace matrices;

TEST(Row, equalOperator) {
    std::vector<double> ref = {2,4,1,5,2,1,2,3,4};
    row_t<double> r_ref{std::begin(ref), std::end(ref)};

    row_t<double> r_vec{std::begin(ref), std::end(ref)};
    EXPECT_TRUE(r_vec == r_ref);

    std::vector<double> ref_eps = {2+eps,4,1,5,2-eps,1,2,3,4};
    row_t<double> r_ref_eps{std::begin(ref_eps), std::end(ref_eps)};
    EXPECT_FALSE(r_ref_eps == r_ref);
}

TEST(Row, subtractionAssignmentOperator) {
    std::vector<double> vec = {2,4,6,8};
    std::vector<double> sub = {0,2,4,6};
    row_t<double> r{std::begin(vec), std::end(vec)};
    row_t<double> r_sub{std::begin(sub), std::end(sub)};
    r -=r_sub;
    std::vector<double> ref = {2,2,2,2};
    row_t<double> r_ref{std::begin(ref), std::end(ref)};
    EXPECT_TRUE(r == r_ref);
}

TEST(Row, divisionAssignmentOperator) {
    std::vector<double> vec = {2,4,6,8};
    row_t<double> m{std::begin(vec), std::end(vec)};
    m /= 2;
    std::vector<double> ref = {1,2,3,4};
    row_t<double> m_ref{std::begin(ref), std::end(ref)};
    EXPECT_TRUE(m == m_ref);

}

TEST(Matrix, equalOperator) {
    std::vector<double> ref = {2,4,1,5,2,1,2,3,4};
    matr_t<double> m_ref{3, std::begin(ref), std::end(ref)};

    matr_t<double> m_vec{3, std::begin(ref), std::end(ref)};
    EXPECT_TRUE(m_vec == m_ref);

    std::vector<double> ref_eps = {2+eps,4,1,5,2-eps,1,2,3,4};
    matr_t<double> m_ref_eps{3, std::begin(ref_eps), std::end(ref_eps)};
    EXPECT_FALSE(m_vec == m_ref_eps);
}

TEST(Matrix, subtractionAssignmentOperator) {
    std::vector<double> vec = {2,4,6,8};
    matr_t<double> m{2, std::begin(vec), std::end(vec)};
    m -= 2;
    std::vector<double> ref = {0,2,4,6};
    matr_t<double> m_ref{2, std::begin(ref), std::end(ref)};
    EXPECT_TRUE(m == m_ref);
}

TEST(Matrix, divisionAssignmentOperator) {
    std::vector<double> vec = {2,4,6,8};
    matr_t<double> m{2, std::begin(vec), std::end(vec)};
    m /= 2;
    std::vector<double> ref = {1,2,3,4};
    matr_t<double> m_ref{2, std::begin(ref), std::end(ref)};
    EXPECT_TRUE(m == m_ref);

    std::vector<double> vec1 = {1,1,1,1};
    matr_t<double> m1{2, std::begin(vec1), std::end(vec1)};
    m1 /= 3;
    std::vector<double> ref1 = {0.33333,0.33333,0.33333,0.33333};
    matr_t<double> m_ref1{2, std::begin(ref1), std::end(ref1)};
    EXPECT_TRUE(m1 == m_ref1);
}

TEST(Matrix, gauss) {
    std::vector<double> vec = {2,4,1,5,2,1,2,3,4};
    matr_t<double> m{3, std::begin(vec), std::end(vec)};
    std::cout << m << std::endl;
    // m.gaussJordan();
    std::cout << m;
}

TEST(Matrix, determinant) {
    std::vector<double> vec = {2,4,1,5,2,1,2,3,4};
    matr_t<double> m{3, std::begin(vec), std::end(vec)};
    EXPECT_THAT(m.det(), -51);
}

TEST(Matrix, inValidMatrix) {
    std::vector<double> vec = {0,4,1,5,2,1,2,3,4};
    matr_t<double> m{3, std::begin(vec), std::end(vec)};
    // std::cout << m << std::endl;
    m.det();
    // std::cout << m;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
