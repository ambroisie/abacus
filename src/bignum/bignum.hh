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

private:
    bool equal(BigNum const& rhs) const;

    void canonicalize();
    bool is_canonicalized() const;

    std::vector<std::uint8_t> digits_{};
    int sign_ = 0;
};

} // namespace abacus::bignum
