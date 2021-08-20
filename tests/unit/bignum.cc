#include <gtest/gtest.h>

#include "bignum.hh"

using namespace abacus::bignum;

TEST(BigNum, equality) {
    auto const zero = BigNum(0);
    auto const one = BigNum(1);

    ASSERT_EQ(zero, zero);
    ASSERT_EQ(one, one);
    ASSERT_NE(zero, one);
}

TEST(BigNum, comparisons) {
    auto const zero = BigNum(0);
    auto const one = BigNum(1);

    ASSERT_LT(zero, one);
    ASSERT_LE(zero, one);
    ASSERT_LE(zero, zero);

    ASSERT_GT(one, zero);
    ASSERT_GE(one, zero);
    ASSERT_GE(one, one);
}

TEST(BigNum, unary) {
    auto const zero = BigNum(0);
    auto const one = BigNum(1);

    ASSERT_EQ(zero, -zero);
    ASSERT_NE(one, -one);

    auto const minus_one = BigNum(-1);
    ASSERT_EQ(minus_one, -one);
}
