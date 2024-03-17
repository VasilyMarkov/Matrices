#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "matrices.hpp"
#include "utils.hpp"

using namespace testing;
using namespace matrices;

TEST(Row, constructor) {
    std::vector<int> vec = {1,2,3,4};
    row_t<int> row(std::begin(vec), std::end(vec));
    EXPECT_EQ(row[0], 1);
    EXPECT_EQ(row[1], 2);
    EXPECT_EQ(row[2], 3);
    EXPECT_EQ(row[3], 4);
}

TEST(Row, eyeConstructor) {
    auto row = row_t<double>::eye(2);
    EXPECT_EQ(row[0], 1);
    EXPECT_EQ(row[1], 1);
}

TEST(Row, copyConstructor) {
    std::vector<int> vec = {1,2,3,4};
    row_t<int> row(std::begin(vec), std::end(vec));
    row_t<int> c_row(row);
    EXPECT_EQ(c_row[0], 1);
    EXPECT_EQ(c_row[1], 2);
    EXPECT_EQ(c_row[2], 3);
    EXPECT_EQ(c_row[3], 4);
}

TEST(Row, moveConstructor) {
    std::vector<int> vec = {1,2,3,4};
    row_t<int> row(std::begin(vec), std::end(vec));
    row_t<int> m_row(std::move(row));
    EXPECT_EQ(m_row[0], 1);
    EXPECT_EQ(m_row[1], 2);
    EXPECT_EQ(m_row[2], 3);
    EXPECT_EQ(m_row[3], 4);
}

TEST(Row, copyConstructorToAnotherType) {
    std::vector<int> vec = {1,2,3,4};
    row_t<int> row(std::begin(vec), std::end(vec));
    row_t<double> c_row(row);
    EXPECT_EQ(c_row[0], 1);
    EXPECT_EQ(c_row[1], 2);
    EXPECT_EQ(c_row[2], 3);
    EXPECT_EQ(c_row[3], 4);
}

TEST(Row, equalOperator) {
    std::vector<double> ref = {2,4,1,5,2,1,2,3,4};
    row_t<double> r_ref{std::begin(ref), std::end(ref)};

    row_t<double> r_vec{std::begin(ref), std::end(ref)};
    EXPECT_TRUE(r_vec == r_ref);

    std::vector<double> ref_eps = {2+eps,4,1,5,2-eps,1,2,3,4};
    row_t<double> r_ref_eps{std::begin(ref_eps), std::end(ref_eps)};
    EXPECT_FALSE(r_ref_eps == r_ref);
}

TEST(Row, equalOperatorInt) {
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

TEST(Row, swap) {
    std::vector<int> vec1 = {6,7,8,9};
    row_t<int> row1{std::begin(vec1), std::end(vec1)};

    std::vector<int> vec2 = {1,2,3,4};
    row_t<int> row2{std::begin(vec2), std::end(vec2)};

    swap(row1, row2);

    EXPECT_EQ(row1[0], 1);
    EXPECT_EQ(row1[1], 2);
    EXPECT_EQ(row1[2], 3);
    EXPECT_EQ(row1[3], 4);

    EXPECT_EQ(row2[0], 6);
    EXPECT_EQ(row2[1], 7);
    EXPECT_EQ(row2[2], 8);
    EXPECT_EQ(row2[3], 9);
}

TEST(Matrix, eyeConstructor) {
    auto matr = matr_t<double>::eye(4);
    EXPECT_EQ(matr[0][0], 1);
    EXPECT_EQ(matr[0][1], 1);
    EXPECT_EQ(matr[1][0], 1);
    EXPECT_EQ(matr[1][1], 1);
}

TEST(Matrix, Constructor) {
    std::vector<int> vec = {1,2,3,4};
    matr_t<int> matr(2, std::begin(vec), std::end(vec));
    EXPECT_EQ(matr[0][0], 1);
    EXPECT_EQ(matr[0][1], 2);
    EXPECT_EQ(matr[1][0], 3);
    EXPECT_EQ(matr[1][1], 4);
}

TEST(Matrix, copyConstructor) {
    std::vector<double> vec = {1,2,3,4};
    matr_t<double> matr(2, std::begin(vec), std::end(vec));
    matr_t<double> c_matr(matr);
    EXPECT_EQ(c_matr[0][0], 1);
    EXPECT_EQ(c_matr[0][1], 2);
    EXPECT_EQ(c_matr[1][0], 3);
    EXPECT_EQ(c_matr[1][1], 4);
}

TEST(Matrix, moveConstructor) {
    std::vector<double> vec = {1,2,3,4};
    matr_t<double> matr(2, std::begin(vec), std::end(vec));
    matr_t<double> m_matr(std::move(matr));
    EXPECT_EQ(m_matr[0][0], 1);
    EXPECT_EQ(m_matr[0][1], 2);
    EXPECT_EQ(m_matr[1][0], 3);
    EXPECT_EQ(m_matr[1][1], 4);
}

TEST(Matrix, copyConstructorToAnotherType) {
    std::vector<int> vec = {1,2,3,4};
    matr_t<int> matr(2, std::begin(vec), std::end(vec));
    matr_t<double> c_matr(matr);
    EXPECT_EQ(c_matr[0][0], 1);
    EXPECT_EQ(c_matr[0][1], 2);
    EXPECT_EQ(c_matr[1][0], 3);
    EXPECT_EQ(c_matr[1][1], 4);
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

TEST(Matrix, determinant) {
    std::vector<double> vec = {2,4,1,5,2,1,2,3,4};
    matr_t<double> m{3, std::begin(vec), std::end(vec)};
    EXPECT_THAT(m.det(), -51);
}

TEST(Matrix, intDeterminant) {
    std::vector<int> vec = {2,4,1,5,2,1,2,3,4};
    matr_t<int> m{3, std::begin(vec), std::end(vec)};
    EXPECT_THAT(m.det(), -51);
}

TEST(Matrix, permutations) {
    std::vector<std::vector<double>> data = 
    {
        {
            1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            0,0,0,1
        },
        {
            0,1,0,0,
            1,0,0,0,
            0,0,1,0,
            0,0,0,1
        },
        {
            0,0,0,1,
            0,1,0,0,
            0,0,1,0,
            1,0,0,0
        },
        {
            0,0,0,1,
            0,0,1,0,
            0,1,0,0,
            1,0,0,0
        },
        {
            1,0,0,0,
            0,0,1,0,
            0,1,0,0,
            0,0,0,1
        }
    };
    std::vector<double> ans = {1, -1, -1, 1, -1};

    for(auto i = 0; i < ans.size(); ++i) {
        matr_t<double> m {4, std::begin(data[i]), std::end(data[i])};
        EXPECT_THAT(m.det(), ans[i]);
    }
}

TEST(Matrix, checkSignDet) {
    std::vector<double> vec = {2,4,1,5,2,1,2,3,4};
    matr_t<double> m{3, std::begin(vec), std::end(vec)};
    std::vector<double> perm_vec = {5,2,1,2,4,1,2,3,4};
    matr_t<double> perm_m{3, std::begin(perm_vec), std::end(perm_vec)};
    EXPECT_THAT(m.det(), -51);
    EXPECT_THAT(perm_m.det(), 51);
}

TEST(Matrix, doubleCallDet) {
    std::vector<double> vec = {2,4,1,5,2,1,2,3,4};
    matr_t<double> m{3, std::begin(vec), std::end(vec)};
    double ans = -51;
    EXPECT_THAT(m.det(), ans);
    EXPECT_THAT(m.det(), ans); 
}

TEST(Matrix, degenerateMatrix) {
    std::vector<double> vec = {1,2,3,2,4,6,1,3,4};
    matr_t<double> m{3, std::begin(vec), std::end(vec)};
    EXPECT_THAT(m.det(), 0);
}

TEST(Matrix, nonSquareMatrix) {
    std::vector<double> vec = {2,4,1,5,2,1,2,3,4,1,3,4};
    EXPECT_THROW(matr_t<double> m(3, std::begin(vec), std::end(vec)), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
