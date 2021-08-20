#include "bignum.hh"

#include <algorithm>

#include <cassert>
#include <cmath>

namespace abacus::bignum {

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

bool BigNum::equal(BigNum const& rhs) const {
    assert(is_canonicalized());
    assert(rhs.is_canonicalized());

    if (sign_ != rhs.sign_) {
        return false;
    }

    return digits_ == rhs.digits_;
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
