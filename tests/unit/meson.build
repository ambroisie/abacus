gtest = dependency(
  'gtest',
  main: true,
  required: false,
)

if gtest.found()
  unit_test_sources = files(
    'base.cc',
  )

  unit_tests = executable(
    'unit_tests',
    sources: unit_test_sources,
    dependencies: [
      gtest,
    ],
  )

  test(
    'unit tests',
    unit_tests,
    protocol: 'gtest',
  )
endif
