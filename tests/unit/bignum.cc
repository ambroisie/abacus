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

TEST(BigNum, read) {
    auto const from_str = [](auto num) -> BigNum {
        std::stringstream str(num);
        BigNum res;
        EXPECT_TRUE(str >> res);
        return res;
    };

    EXPECT_EQ(from_str("0"), BigNum(0));
    EXPECT_EQ(from_str("1"), BigNum(1));
    EXPECT_EQ(from_str("-1"), BigNum(-1));
    EXPECT_EQ(from_str("42"), BigNum(42));
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

TEST(BigNum, addition_carry) {
    auto const one = BigNum(1);
    auto const nine = BigNum(9);
    auto const ten = BigNum(10);

    EXPECT_EQ(one + nine, ten);
    EXPECT_EQ(nine + one, ten);
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

TEST(BigNum, multiplication_zero) {
    auto const zero = BigNum(0);
    auto const one = BigNum(1);
    auto const minus_one = BigNum(-1);

    EXPECT_EQ(zero * zero, zero);
    EXPECT_EQ(zero * one, zero);
    EXPECT_EQ(one * zero, zero);
    EXPECT_EQ(zero * minus_one, zero);
    EXPECT_EQ(minus_one * zero, zero);
}

TEST(BigNum, multiplication_positive) {
    auto const one = BigNum(1);
    auto const two = BigNum(2);
    auto const four = BigNum(4);

    EXPECT_EQ(one * one, one);
    EXPECT_EQ(two * one, two);
    EXPECT_EQ(one * two, two);
    EXPECT_EQ(two * two, four);
}

TEST(BigNum, multiplication_mixed_signs) {
    auto const minus_one = BigNum(-1);
    auto const one = BigNum(1);
    auto const minus_two = BigNum(-2);
    auto const two = BigNum(2);
    auto const minus_four = BigNum(-4);
    auto const four = BigNum(4);

    EXPECT_EQ(one * minus_one, minus_one);
    EXPECT_EQ(minus_one * one, minus_one);
    EXPECT_EQ(minus_one * minus_one, one);
    EXPECT_EQ(two * minus_one, minus_two);
    EXPECT_EQ(minus_one * two, minus_two);
    EXPECT_EQ(two * minus_two, minus_four);
    EXPECT_EQ(minus_two * two, minus_four);
    EXPECT_EQ(minus_two * minus_two, four);
}

TEST(BigNum, division) {
    auto const zero = BigNum(0);
    auto const one = BigNum(1);
    auto const two = BigNum(2);

    EXPECT_EQ(one / one, one);
    EXPECT_EQ(one / two, zero);
    EXPECT_EQ(two / one, two);
}

TEST(BigNum, division_negative) {
    auto const zero = BigNum(0);
    auto const one = BigNum(1);
    auto const minus_one = BigNum(-1);
    auto const two = BigNum(2);
    auto const minus_two = BigNum(-2);

    EXPECT_EQ(one / minus_one, minus_one);
    EXPECT_EQ(minus_one / one, minus_one);
    EXPECT_EQ(minus_one / minus_one, one);
    EXPECT_EQ(two / minus_two, minus_one);
    EXPECT_EQ(minus_two / two, minus_one);
    EXPECT_EQ(minus_two / minus_two, one);

    EXPECT_EQ(one / minus_two, zero);
    EXPECT_EQ(minus_one / two, zero);
    EXPECT_EQ(one / minus_two, zero);
    EXPECT_EQ(minus_one / minus_two, zero);
    EXPECT_EQ(two / minus_one, minus_two);
    EXPECT_EQ(minus_two / minus_one, two);
    EXPECT_EQ(minus_two / one, minus_two);
}

TEST(BigNum, division_truncate) {
    auto const one = BigNum(1);
    auto const minus_one = BigNum(-1);
    auto const three = BigNum(3);
    auto const minus_three = BigNum(-3);
    auto const five = BigNum(5);
    auto const minus_five = BigNum(-5);

    EXPECT_EQ(five / three, one);
    EXPECT_EQ(five / minus_three, minus_one);
    EXPECT_EQ(minus_five / three, minus_one);
    EXPECT_EQ(minus_five / minus_three, one);
}

TEST(BigNum, div_mod_identity) {
    auto const three = BigNum(3);
    auto const minus_three = BigNum(-3);
    auto const five = BigNum(5);
    auto const minus_five = BigNum(-5);

    EXPECT_EQ((five / three) * three + (five % three), five);
    EXPECT_EQ((five / minus_three) * minus_three + (five % minus_three), five);
    EXPECT_EQ((minus_five / three) * three + (minus_five % three), minus_five);
    EXPECT_EQ((minus_five / minus_three) * minus_three
                  + (minus_five % minus_three),
              minus_five);
}
