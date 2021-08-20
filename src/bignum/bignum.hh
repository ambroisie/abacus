#pragma once

#include <vector>

#include <cstdint>

namespace abacus::bignum {

class BigNum {
public:
    explicit BigNum(std::int64_t number);

    friend BigNum operator+(BigNum const& rhs) {
        return rhs;
    }

    friend BigNum operator-(BigNum const& rhs) {
        auto ret = rhs;
        ret.flip_sign();
        return ret;
    }

    friend bool operator==(BigNum const& lhs, BigNum const& rhs) {
        return lhs.equal(rhs);
    }

    friend bool operator!=(BigNum const& lhs, BigNum const& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(BigNum const& lhs, BigNum const& rhs) {
        return lhs.less_than(rhs);
    }

    friend bool operator>(BigNum const& lhs, BigNum const& rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(BigNum const& lhs, BigNum const& rhs) {
        return !(lhs > rhs);
    }

    friend bool operator>=(BigNum const& lhs, BigNum const& rhs) {
        return !(lhs < rhs);
    }

private:
    void flip_sign();

    bool equal(BigNum const& rhs) const;
    bool less_than(BigNum const& rhs) const;

    void canonicalize();
    bool is_canonicalized() const;

    std::vector<std::uint8_t> digits_{};
    int sign_ = 0;
};

} // namespace abacus::bignum
