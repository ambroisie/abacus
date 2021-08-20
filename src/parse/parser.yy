// At least 3.2 to get rid of `stack.hh`
%require "3.2"
// Let's be modern
%language "C++"

// LALR is fine for our purposes
%skeleton "lalr1.cc"

// Write a header with our parser-related declarations
%defines

// Safer than unions... 
%define api.value.type variant
// Define constructors for each token
%define api.token.constructor

// Ambiguity is forbidden
%expect 0

// Prefix all the tokens with TOK_ to avoid colisions.
%define api.token.prefix {TOK_}
// Track locations
%locations

// Enable parse tracing
%define parse.trace
// Give detailled error messages
%define parse.error detailed
// Correct look-ahead to avoid erroneous error messages
%define parse.lac full

// Code that should be in the header
%code requires {
// Forward declare our driver
namespace abacus::parser {
class ParserDriver;
} // namespace abacus::parser
}

%code provides {
    // Forward ParserDriver to scanner
    #define YY_DECL \
        yy::parser::symbol_type yylex(::abacus::parser::ParserDriver& drv)
    YY_DECL;
}

// Only include the actual ParserDriver class declaration in source code
%code {
#include "parser-driver.hh"
}

// Use the driver to carry context back-and-forth
%param { abacus::parser::ParserDriver& drv }

%token EOF 0 "end-of-file"

// FIXME:will become BigNum
%token <int> NUM "number"

// Use `<<` to print everything
%printer { yyo << $$; } <*>;

%token
    PLUS "+"
    MINUS "-"
    TIMES "*"
    DIVIDE "/"
    LPAREN "("
    RPAREN ")"

// Let's define the usual PEMDAS rules
%left PLUS MINUS
%left TIMES DIVIDE
%precedence UNARY

// FIXME: will become BigNum
%type <int> input exp

%%

input:
    exp EOF
  ;

exp:
    NUM { $$ = $1; }
  | exp PLUS exp { $$ = $1 + $3; }
  | exp MINUS exp { $$ = $1 - $3; }
  | exp TIMES exp { $$ = $1 * $3; }
  | exp DIVIDE exp { $$ = $1 / $3; }
  | PLUS exp %prec UNARY { $$ = $2; }
  | MINUS exp %prec UNARY { $$ = -$2; }
  | LPAREN exp RPAREN { $$ = $2; }
  ;

%%

void yy::parser::error(location_type const& l, std::string const& m) {
  std::cerr << l << ": " << m << '\n';
}