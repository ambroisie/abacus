flex_binary = find_program('flex', required: true)
flex = generator(
  flex_binary,
  output: '@BASENAME@.cc',
  arguments: [
    '-o',
    '@OUTPUT@',
    '@INPUT@',
  ],
)

bison_binary = find_program('bison', required: true)
bison = generator(
  bison_binary,
  output: [
    '@BASENAME@.cc',
    '@BASENAME@.hh',
  ],
  arguments: [
    '@INPUT@',
    '--output=@OUTPUT0@',
    '--defines=@OUTPUT1@',
    '--graph',
    # FIXME: html output in bison 3.7.90
  ],
)

parser = library(
  'parser',
  'parser-driver.cc',
  'parser-driver.hh',
  flex.process('scanner.ll'),
  bison.process('parser.yy'),
  dependencies: [
    bignum,
  ],
)
