#include "parser-driver.hh"

namespace abacus::parse {

ParserDriver::ParserDriver()
    : parse_trace_p_(std::getenv("PARSE")), scan_trace_p_(std::getenv("SCAN")) {
}

int ParserDriver::parse(std::string filename) {
    filename_ = std::move(filename);

    current_location_.initialize(&filename_);

    scan_open();

    yy::parser parser(*this);
    parser.set_debug_level(parse_trace_p_);
    int res = parser.parse();

    scan_close();

    return res;
}

yy::location& ParserDriver::location() {
    return current_location_;
}

yy::location const& ParserDriver::location() const {
    return current_location_;
}

ParserDriver::numeric_type& ParserDriver::result() {
    return result_;
}

ParserDriver::numeric_type const& ParserDriver::result() const {
    return result_;
}

} // namespace abacus::parse
