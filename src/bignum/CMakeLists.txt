add_library(bignum STATIC
  bignum.cc
  bignum.hh
)
target_link_libraries(bignum PRIVATE common_options)
