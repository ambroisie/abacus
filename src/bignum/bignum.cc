#include "bignum.hh"

#include <algorithm>
#include <iostream>
#include <iterator>

#include <cassert>
#include <cmath>

namespace abacus::bignum {

using digits_type = std::vector<std::uint8_t>;

namespace {

bool do_less_than(digits_type const& lhs, digits_type const& rhs) {
    return std::lexicographical_compare(lhs.rbegin(), lhs.rend(), rhs.rbegin(),
                                        rhs.rend());
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
        digits_.push_back(abs % 10);
        abs /= 10;
    } while (abs);

    assert(is_canonicalized());
}

std::ostream& BigNum::dump(std::ostream& out) const {
    if (sign_ == 0) {
        return out << '0';
    }

    if (sign_ < 0) {
        out << '-';
    }
    std::copy(digits_.rbegin(), digits_.rend(),
              std::ostream_iterator<int>(out));

    return out;
}

void BigNum::flip_sign() {
    assert(is_canonicalized());

    sign_ *= -1;
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
                                       [](auto v) { return v >= 10; });
    if (overflow != digits_.end()) {
        return false;
    }

    return true;
}

} // namespace abacus::bignum
