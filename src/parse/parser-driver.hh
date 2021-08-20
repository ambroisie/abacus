#pragma once

#include <string>

#include "parser.hh"

namespace abacus::parser {

class ParserDriver {
public:
    ParserDriver();

    int parse(std::string filename);

    void scan_open();
    void scan_close();

    yy::location& location();
    yy::location const& location() const;

private:
    // FIXME: will become BigNum
    int result_ = 0;
    std::string filename_{};
    yy::location current_location_{};
    bool parse_trace_p_ = false;
    bool scan_trace_p_ = false;
};

} // namespace abacus::parser
