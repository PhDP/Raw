include_directories(.)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(test_cc
  run_all.cc
#  fset_spec.cc
  grammar_spec.cc
  str_spec.cc
  codons_spec.cc
  cmp_spec.cc
)

source_group("Test Source" FILES ${test_cc})
add_executable(randamu_test ${test_cc})
target_link_libraries(randamu_test ${RANDAMU_TO_LINK} ${RANDAMU_LIB_NAME})
add_test(NAME ctest COMMAND randamu_test)
