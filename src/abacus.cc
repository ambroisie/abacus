#include "parser-driver.hh" // FIXME: I would like `parse/parser-driver.hh` path instead...

int main() {
    abacus::parse::ParserDriver driver{};

    driver.parse("-");

    std::cout << driver.result();
}
