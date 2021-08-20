#include <sstream>

#include <gtest/gtest.h>

#include "bignum.hh"

using namespace abacus::bignum;

TEST(BigNum, dump) {
    auto const zero = BigNum(0);
    auto const one = BigNum(1);
    auto const minus_one = BigNum(-1);
    auto const forty_two = BigNum(42);

    auto const to_str = [](auto num) {
        std::stringstream str;
        str << num;
        return str.str();
    };

    EXPECT_EQ(to_str(zero), "0");
    EXPECT_EQ(to_str(one), "1");
    EXPECT_EQ(to_str(minus_one), "-1");
    EXPECT_EQ(to_str(forty_two), "42");
}

TEST(BigNum, equality) {
    auto const zero = BigNum(0);
    auto const one = BigNum(1);

    EXPECT_EQ(zero, zero);
    EXPECT_EQ(one, one);
    EXPECT_NE(zero, one);
}

TEST(BigNum, comparisons) {
    auto const zero = BigNum(0);
    auto const one = BigNum(1);

    EXPECT_LT(zero, one);
    EXPECT_LE(zero, one);
    EXPECT_LE(zero, zero);

    EXPECT_GT(one, zero);
    EXPECT_GE(one, zero);
    EXPECT_GE(one, one);
}

TEST(BigNum, unary) {
    auto const zero = BigNum(0);
    auto const one = BigNum(1);

    EXPECT_EQ(zero, -zero);
    EXPECT_NE(one, -one);

    auto const minus_one = BigNum(-1);
    EXPECT_EQ(minus_one, -one);
}
