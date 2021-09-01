find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

bison_target(parser_sources parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cc DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hh)
flex_target(scanner_sources scanner.ll  ${CMAKE_CURRENT_BINARY_DIR}/scanner.cc)
add_flex_bison_dependency(scanner_sources parser_sources)

add_library(parse STATIC
  parser-driver.cc
  parser-driver.hh
  ${BISON_parser_sources_OUTPUTS}
  ${FLEX_scanner_sources_OUTPUTS}
)
target_link_libraries(parse PRIVATE common_options)

target_link_libraries(parse PRIVATE
  bignum
)

target_include_directories(parse PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
