add_library(bignum STATIC
  bignum.cc
  bignum.hh
)
target_link_libraries(bignum PRIVATE common_options)

target_include_directories(bignum PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
