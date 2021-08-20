#include "bignum.hh"

#include <algorithm>

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
}

void BigNum::canonicalize() {
    auto const it = std::find_if(digits_.rbegin(), digits_.rend(),
                                 [](auto v) { return v != 0; });
    digits_.erase(it.base(), digits_.end());

    if (digits_.size() == 0) {
        sign_ = 0;
    }
}

} // namespace abacus::bignum
