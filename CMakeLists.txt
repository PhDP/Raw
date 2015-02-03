cmake_minimum_required(VERSION 2.8)
project(randamu)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

enable_testing()
include_directories(include)

find_package(MATH)

################################################################
# BUILD LIBRARY ################################################

add_library(randamu STATIC
  src/compar.c
  src/hash.c
  src/numbers.c
  src/rng.c
  src/sort.c
)

target_link_libraries(randamu ${MATH_LIBS})

################################################################
# INSTALLATION #################################################

install(TARGETS randamu DESTINATION lib)

# Macro for adding headers:
macro(add_header NAME)
  install(FILES include/${NAME} DESTINATION include/randamu)
endmacro(add_header)

install(TARGETS randamu DESTINATION lib)
add_header(bloom.h)
add_header(compar.h)
add_header(hash.h)
add_header(numbers.h)
add_header(rng.h)
add_header(sort.h)
add_header(common.h)

################################################################
# TESTS ########################################################

set(all_tests "")

# Macro for adding tests:
macro(add_librandamu_test NAME)
  list(APPEND all_tests ${NAME})
  add_executable(${NAME} tests/${NAME}.c)
  target_link_libraries(${NAME} ${MATH_LIBS})
  add_test(NAME ${NAME} COMMAND ${NAME})
endmacro(add_librandamu_test)

add_librandamu_test(test_rng_seq)
add_librandamu_test(test_rng_double)
add_librandamu_test(test_rng_uint)
add_librandamu_test(test_rng_init)
add_librandamu_test(test_rng_normal)
add_librandamu_test(test_randalloc)
add_librandamu_test(test_sort)
add_librandamu_test(test_numbers)
add_librandamu_test(test_common)

