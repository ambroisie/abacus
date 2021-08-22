flex_binary = find_program('flex', required: true)
lexer_sources = custom_target(
  'lexer_sources',
  input: 'scanner.ll',
  output: 'scanner.cc',
  command: [
    flex_binary,
    '-o',
    '@OUTPUT@',
    '@INPUT@',
  ],
)

bison_binary = find_program('bison', required: true)
parser_sources = custom_target(
  'parser_sources',
  input: 'parser.yy',
  output: [
    'parser.cc',
    'parser.hh',
  ],
  command: [
    bison_binary,
    '@INPUT@',
    '--output=@OUTPUT0@',
    '--defines=@OUTPUT1@',
    '--graph',
    # FIXME: html output in bison 3.7.90
  ],
)

parse_inc = include_directories('.')

parse_lib = library(
  'parser',
  'parser-driver.cc',
  'parser-driver.hh',
  lexer_sources,
  parser_sources,
  dependencies: [
    bignum,
  ],
)

parse = declare_dependency(
  link_with: parse_lib,
  include_directories: parse_inc,
)
