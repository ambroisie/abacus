#pragma once

#include <vector>

#include <cstdint>

namespace abacus::bignum {

class BigNum {
public:
    explicit BigNum(std::int64_t number);

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
    bool equal(BigNum const& rhs) const;
    bool less_than(BigNum const& rhs) const;

    void canonicalize();
    bool is_canonicalized() const;

    std::vector<std::uint8_t> digits_{};
    int sign_ = 0;
};

} // namespace abacus::bignum
