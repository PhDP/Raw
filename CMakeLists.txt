cmake_minimum_required(VERSION 2.8)
project(randomu)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)

enable_testing()

include_directories(include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -std=c99")

add_library(randomu STATIC
  src/rng.c
)

target_link_libraries(randomu m)

set(all_tests "")

macro(add_librandomu_test NAME)
  list(APPEND all_tests ${NAME})
  add_executable(${NAME} tests/${NAME}.c)
  target_link_libraries(${NAME} m)
  add_test(NAME ${NAME} COMMAND ${NAME})
  install(TARGETS ${NAME} RUNTIME DESTINATION tests)
endmacro(add_librandomu_test)

#  Transport tests.
add_librandomu_test(test_rng_seq)
add_librandomu_test(test_rng_double)
add_librandomu_test(test_rng_init)
add_librandomu_test(test_rng_normal)
add_librandomu_test(test_sort)
add_librandomu_test(test_numbers)

