#pragma once

#include <iosfwd>
#include <vector>

#include <cstdint>

namespace abacus::bignum {

class BigNum {
public:
    explicit BigNum(std::int64_t number = 0);

    friend std::ostream& operator<<(std::ostream& out, BigNum const& num) {
        return num.dump(out);
    }

    friend std::istream& operator>>(std::istream& in, BigNum& num) {
        return num.read(in);
    }

    friend BigNum operator+(BigNum const& rhs) {
        return rhs;
    }

    friend BigNum operator-(BigNum const& rhs) {
        auto ret = rhs;
        ret.flip_sign();
        return ret;
    }

    friend BigNum& operator+=(BigNum& lhs, BigNum const& rhs) {
        lhs.add(rhs);
        return lhs;
    }

    friend BigNum operator+(BigNum const& lhs, BigNum const& rhs) {
        auto ret = lhs;
        ret += rhs;
        return ret;
    }

    friend BigNum& operator-=(BigNum& lhs, BigNum const& rhs) {
        lhs.substract(rhs);
        return lhs;
    }

    friend BigNum operator-(BigNum const& lhs, BigNum const& rhs) {
        auto ret = lhs;
        ret -= rhs;
        return ret;
    }

    friend BigNum& operator*=(BigNum& lhs, BigNum const& rhs) {
        lhs.multiply(rhs);
        return lhs;
    }

    friend BigNum operator*(BigNum const& lhs, BigNum const& rhs) {
        auto ret = lhs;
        ret *= rhs;
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

    bool is_zero() const;
    bool is_positive() const;
    bool is_negative() const;

private:
    std::ostream& dump(std::ostream& out) const;
    std::istream& read(std::istream& in);

    void flip_sign();
    void add(BigNum const& rhs);
    void substract(BigNum const& rhs);
    void multiply(BigNum const& rhs);

    bool equal(BigNum const& rhs) const;
    bool less_than(BigNum const& rhs) const;

    void canonicalize();
    bool is_canonicalized() const;

    std::vector<std::uint8_t> digits_{};
    int sign_ = 0;
};

} // namespace abacus::bignum
