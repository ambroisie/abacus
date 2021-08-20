#include "bignum.hh"

#include <algorithm>
#include <iostream>
#include <iterator>

#include <cassert>
#include <cmath>

namespace abacus::bignum {

using digits_type = std::vector<std::uint8_t>;

namespace {

auto static constexpr BASE = 10;

bool do_less_than(digits_type const& lhs, digits_type const& rhs) {
    return std::lexicographical_compare(lhs.rbegin(), lhs.rend(), rhs.rbegin(),
                                        rhs.rend());
}

digits_type do_addition(digits_type const& lhs, digits_type const& rhs) {
    int carry = 0;
    digits_type res;

    auto it1 = lhs.begin();
    auto it2 = rhs.begin();

    auto const end1 = lhs.end();
    auto const end2 = rhs.end();

    while (it1 != end1 && it2 != end2) {
        int addition = *it1 + *it2 + carry;
        carry = addition / BASE;
        res.push_back(addition % BASE);
        ++it1;
        ++it2;
    }

    auto it = it1;
    auto end = end1;
    if (it1 == end1) {
        it = it2;
        end = end2;
    }

    while (it != end) {
        int addition = *it + carry;
        carry = addition / BASE;
        res.push_back(addition % BASE);
        ++it;
    }

    return res;
}

digits_type do_substraction(digits_type const& lhs, digits_type const& rhs) {
    assert(!do_less_than(lhs, rhs));

    digits_type complement;
    auto const take_complement = [](auto num) { return 9 - num; };
    std::transform(lhs.begin(), lhs.end(), std::back_inserter(complement),
                   take_complement);

    complement = do_addition(complement, rhs);

    std::transform(complement.begin(), complement.end(), complement.begin(),
                   take_complement);

    return complement;
}

digits_type do_multiplication(digits_type const& lhs, digits_type const& rhs) {
    digits_type res(lhs.size() + rhs.size());

    for (std::size_t i = 0; i < lhs.size(); ++i) {
        int carry = 0;
        for (std::size_t j = 0; j < rhs.size(); ++j) {
            int multiplication = lhs[i] * rhs[j];
            res[i + j] += multiplication + carry;
            carry = res[i + j] / BASE;
            res[i + j] %= BASE;
        }
        res[i + rhs.size()] += carry;
    }

    return res;
}

} // namespace

BigNum::BigNum(std::int64_t number) {
    if (number == 0) {
        return;
    }

    if (number < 0) {
        sign_ = -1;
    } else {
        sign_ = 1;
    }

    auto abs = static_cast<std::uint64_t>(std::abs(number));
    do {
        digits_.push_back(abs % BASE);
        abs /= BASE;
    } while (abs);

    assert(is_canonicalized());
}

std::ostream& BigNum::dump(std::ostream& out) const {
    if (is_zero()) {
        return out << '0';
    }

    if (is_negative()) {
        out << '-';
    }
    std::copy(digits_.rbegin(), digits_.rend(),
              std::ostream_iterator<int>(out));

    return out;
}

std::istream& BigNum::read(std::istream& in) {
    bool parsed = false;
    bool leading = true;

    if (in.peek() == '-') {
        in.get();
        sign_ = -1;
    } else {
        sign_ = 1;
    }

    digits_type digits;
    while (std::isdigit(in.peek())) {
        parsed = true;
        int digit = in.get() - '0';
        if (digit != 0 || !leading) {
            digits.push_back(digit);
            leading = false;
        }
    }

    if (leading) {
        sign_ = 0;
    }

    if (!parsed) {
        in.setstate(std::ios::failbit);
    } else {
        std::reverse(digits.begin(), digits.end());
        digits_ = std::move(digits);
    }

    return in;
}

void BigNum::flip_sign() {
    assert(is_canonicalized());

    sign_ *= -1;
}

void BigNum::add(BigNum const& rhs) {
    assert(is_canonicalized());
    assert(rhs.is_canonicalized());

    if (rhs.is_zero()) {
        return;
    }

    if (is_zero()) {
        *this = rhs;
        return;
    }

    if (sign_ == rhs.sign_) {
        digits_ = do_addition(digits_, rhs.digits_);
    } else {
        bool flipped = do_less_than(digits_, rhs.digits_);
        if (flipped) {
            digits_ = do_substraction(rhs.digits_, digits_);
        } else {
            digits_ = do_substraction(digits_, rhs.digits_);
        }
        if (flipped) {
            flip_sign();
        }
        canonicalize();
    }

    assert(is_canonicalized());
}

void BigNum::substract(BigNum const& rhs) {
    assert(is_canonicalized());
    assert(rhs.is_canonicalized());

    flip_sign();
    add(rhs);
    flip_sign();

    assert(is_canonicalized());
}

void BigNum::multiply(BigNum const& rhs) {
    assert(is_canonicalized());
    assert(rhs.is_canonicalized());

    if (is_zero() || rhs.is_zero()) {
        *this = BigNum();
        return;
    }

    digits_ = do_multiplication(digits_, rhs.digits_);
    sign_ *= rhs.sign_;

    canonicalize();
}

bool BigNum::equal(BigNum const& rhs) const {
    assert(is_canonicalized());
    assert(rhs.is_canonicalized());

    if (sign_ != rhs.sign_) {
        return false;
    }

    return digits_ == rhs.digits_;
}

bool BigNum::less_than(BigNum const& rhs) const {
    assert(is_canonicalized());
    assert(rhs.is_canonicalized());

    if (sign_ != rhs.sign_) {
        return sign_ < rhs.sign_;
    }

    return do_less_than(digits_, rhs.digits_);
}

void BigNum::canonicalize() {
    auto const it = std::find_if(digits_.rbegin(), digits_.rend(),
                                 [](auto v) { return v != 0; });
    digits_.erase(it.base(), digits_.end());

    if (digits_.size() == 0) {
        sign_ = 0;
    }

    assert(is_canonicalized());
}

bool BigNum::is_canonicalized() const {
    if (digits_.size() == 0) {
        return sign_ == 0;
    }

    auto const leading_zeros = std::find_if(digits_.rbegin(), digits_.rend(),
                                            [](auto v) { return v != 0; });
    if (leading_zeros != digits_.rbegin()) {
        return false;
    }

    auto const overflow = std::find_if(digits_.begin(), digits_.end(),
                                       [](auto v) { return v >= BASE; });
    if (overflow != digits_.end()) {
        return false;
    }

    return true;
}

bool BigNum::is_zero() const {
    assert(is_canonicalized());
    return sign_ == 0;
}

bool BigNum::is_positive() const {
    assert(is_canonicalized());
    return sign_ >= 0;
}

bool BigNum::is_negative() const {
    assert(is_canonicalized());
    return sign_ <= 0;
}

} // namespace abacus::bignum
