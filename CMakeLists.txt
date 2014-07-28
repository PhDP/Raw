cmake_minimum_required(VERSION 2.8)
project(randamu)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)

enable_testing()

include_directories(include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -std=c99")

add_library(randamu STATIC
  src/rng.c
)

target_link_libraries(randamu m)

install(TARGETS randamu DESTINATION lib)
install(FILES include/rng.h DESTINATION include/randamu)

set(all_tests "")

macro(add_librandamu_test NAME)
  list(APPEND all_tests ${NAME})
  add_executable(${NAME} tests/${NAME}.c)
  target_link_libraries(${NAME} m)
  add_test(NAME ${NAME} COMMAND ${NAME})
endmacro(add_librandamu_test)

#  Transport tests.
add_librandamu_test(test_rng_seq)
add_librandamu_test(test_rng_double)
add_librandamu_test(test_rng_init)
add_librandamu_test(test_rng_normal)
add_librandamu_test(test_sort)
add_librandamu_test(test_numbers)

