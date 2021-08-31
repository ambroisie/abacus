abacus_sources = files(
  'abacus.cc',
)

subdir('bignum')
subdir('parse')

abacus = executable(
  'abacus',
  sources: abacus_sources,
  dependencies: [
    bignum,
    parse,
  ],
  install: true,
)
