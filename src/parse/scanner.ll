%{
#include <sstream>

#include "parser-driver.hh"
#include "parser.hh"
%}
/* Avoid warnings because of unused functions */
%option noinput
%option nounput

/* Enable scan tracing */
%option debug

/* Assume single file, do no implement `yywrap` */
%option noyywrap

/* Let Flex track the line numbers */
%option yylineno

%{
    // Run at each match
    #define YY_USER_ACTION loc.columns(yyleng);
%}

blank [ \t\r]
int [0-9]+

%%

%{
    // Run each time `yylex` is called
    auto& loc = drv.location();
    loc.step();
%}

{blank}+    loc.step();
\n+         loc.lines(yyleng); loc.step();

"+"         return yy::parser::make_PLUS(loc);
"-"         return yy::parser::make_MINUS(loc);
"*"         return yy::parser::make_TIMES(loc);
"/"         return yy::parser::make_DIVIDE(loc);
"("         return yy::parser::make_LPAREN(loc);
")"         return yy::parser::make_RPAREN(loc);

{int}       {
    abacus::bignum::BigNum num;
    std::stringstream(yytext) >> num;
    return yy::parser::make_NUM(num, loc);
}

.           {
    using namespace yy;
    using namespace std::string_literals;
    throw parser::syntax_error(loc, "invalid character: "s + yytext);
}

<<EOF>>     return yy::parser::make_EOF(loc);

%%

namespace abacus::parse {

void ParserDriver::scan_open() {
    yy_flex_debug = scan_trace_p_;

    if (filename_.empty() || filename_ == "-") {
        yyin = stdin;
    } else if ((yyin = fopen(filename_.c_str(), "r")) == nullptr) {
      std::cerr << "cannot open " << filename_ << ": " << strerror(errno) << '\n';
      exit(EXIT_FAILURE);
    }
}

void ParserDriver::scan_close() {
    fclose(yyin);
}

} // namespace abacus::parse
