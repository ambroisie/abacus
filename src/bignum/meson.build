bignum_sources = files(
  'bignum.cc',
  'bignum.hh',
)

bignum_inc = include_directories('.')

bignum_lib = static_library(
  'bignum',
  sources: bignum_sources,
)

bignum = declare_dependency(
  link_with: bignum_lib,
  include_directories: bignum_inc,
)
