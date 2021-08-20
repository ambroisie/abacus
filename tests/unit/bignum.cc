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

    ASSERT_EQ(to_str(zero), "0");
    ASSERT_EQ(to_str(one), "1");
    ASSERT_EQ(to_str(minus_one), "-1");
    ASSERT_EQ(to_str(forty_two), "42");
}

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
