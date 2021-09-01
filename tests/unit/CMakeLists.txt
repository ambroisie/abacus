find_package(GTest)

if (${GTest_FOUND})
include(GoogleTest)

add_executable(bignum_test bignum.cc)
target_link_libraries(bignum_test PRIVATE common_options)

target_link_libraries(bignum_test PRIVATE
  bignum
  GTest::gtest
  GTest::gtest_main
)

gtest_discover_tests(bignum_test)
endif (${GTest_FOUND})
