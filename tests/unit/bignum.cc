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

TEST(BigNum, addition_positive) {
    auto const zero = BigNum(0);
    auto const one = BigNum(1);
    auto const two = BigNum(2);

    EXPECT_EQ(zero + zero, zero);
    EXPECT_EQ(zero + one, one);
    EXPECT_EQ(one + zero, one);
    EXPECT_EQ(one + one, two);
}

TEST(BigNum, addition_negative) {
    auto const zero = BigNum(0);
    auto const minus_one = BigNum(-1);
    auto const minus_two = BigNum(-2);

    EXPECT_EQ(zero + zero, zero);
    EXPECT_EQ(zero + minus_one, minus_one);
    EXPECT_EQ(minus_one + zero, minus_one);
    EXPECT_EQ(minus_one + minus_one, minus_two);
}

TEST(BigNum, addition_mixed_signs) {
    auto const zero = BigNum(0);
    auto const one = BigNum(1);
    auto const minus_one = BigNum(-1);

    EXPECT_EQ(one + minus_one, zero);
    EXPECT_EQ(minus_one + one, zero);
}

TEST(BigNum, addition_flips_sign) {
    auto const one = BigNum(1);
    auto const two = BigNum(2);
    auto const minus_one = BigNum(-1);
    auto const minus_two = BigNum(-2);

    EXPECT_EQ(one + minus_two, minus_one);
    EXPECT_EQ(minus_two + one, minus_one);

    EXPECT_EQ(minus_one + two, one);
    EXPECT_EQ(two + minus_one, one);
}

TEST(BigNum, substraction_positive) {
    auto const zero = BigNum(0);
    auto const one = BigNum(1);
    auto const two = BigNum(2);

    EXPECT_EQ(zero - zero, zero);
    EXPECT_EQ(two - zero, two);
    EXPECT_EQ(two - one, one);
    EXPECT_EQ(one - one, zero);
}

TEST(BigNum, substraction_negative) {
    auto const zero = BigNum(0);
    auto const minus_one = BigNum(-1);
    auto const one = BigNum(1);

    EXPECT_EQ(zero - zero, zero);
    EXPECT_EQ(zero - minus_one, one);
    EXPECT_EQ(zero - one, minus_one);
}

TEST(BigNum, substraction_mixed_signs) {
    auto const zero = BigNum(0);
    auto const one = BigNum(1);
    auto const two = BigNum(2);
    auto const minus_one = BigNum(-1);
    auto const minus_two = BigNum(-2);

    EXPECT_EQ(one - minus_one, two);
    EXPECT_EQ(minus_one - one, minus_two);
}

TEST(BigNum, substraction_flips_sign) {
    auto const one = BigNum(1);
    auto const two = BigNum(2);
    auto const minus_one = BigNum(-1);
    auto const minus_two = BigNum(-2);

    EXPECT_EQ(one - two, minus_one);
    EXPECT_EQ(minus_one - minus_two, one);
}
