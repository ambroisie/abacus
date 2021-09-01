add_executable(abacus abacus.cc)
target_link_libraries(abacus PRIVATE common_options)

add_subdirectory(bignum)
add_subdirectory(parse)

target_link_libraries(abacus PRIVATE
  bignum
  parse
)

install(TARGETS abacus)
