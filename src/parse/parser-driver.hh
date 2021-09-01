#pragma once

#include <string>

#include "parser.hh"

#include "bignum/bignum.hh"

namespace abacus::parse {

class ParserDriver {
public:
    using numeric_type = abacus::bignum::BigNum;

    ParserDriver();

    int parse(std::string filename);

    void scan_open();
    void scan_close();

    yy::location& location();
    yy::location const& location() const;

    numeric_type& result();
    numeric_type const& result() const;

private:
    numeric_type result_{0};
    std::string filename_{};
    yy::location current_location_{};
    bool parse_trace_p_;
    bool scan_trace_p_;
};

} // namespace abacus::parse
