#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "row.hpp"
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
    row_t<double> r{std::begin(vec), std::end(vec)};
    r -= 2;
    std::vector<double> ref = {0,2,4,6};
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
