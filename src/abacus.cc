#include "parse/parser-driver.hh"

int main() {
    abacus::parse::ParserDriver driver{};

    driver.parse("-");

    std::cout << driver.result();
}
