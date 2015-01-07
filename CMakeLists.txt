cmake_minimum_required(VERSION 2.8)
project(randamu)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)

enable_testing()

include_directories(include)

################################################################
# BUILD LIBRARY ################################################

if(NOT MSVC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -std=c99")
endif(NOT MSVC)

add_library(randamu STATIC
  src/compar.c
  src/hash.c
  src/numbers.c
  src/rng.c
  src/sort.c
)

# Link to the math library
if(NOT MSVC)
  target_link_libraries(randamu m)
endif(NOT MSVC)

################################################################
# INSTALLATION #################################################

install(TARGETS randamu DESTINATION lib)
install(FILES include/bloom.h DESTINATION include/randamu)
install(FILES include/compar.h DESTINATION include/randamu)
install(FILES include/hash.h DESTINATION include/randamu)
install(FILES include/numbers.h DESTINATION include/randamu)
install(FILES include/rng.h DESTINATION include/randamu)
install(FILES include/sort.h DESTINATION include/randamu)

################################################################
# TESTS ########################################################

set(all_tests "")

# Macro for adding tests:
macro(add_librandamu_test NAME)
  list(APPEND all_tests ${NAME})
  add_executable(${NAME} tests/${NAME}.c)
  if(NOT MSVC)
    target_link_libraries(${NAME} m)
  endif(NOT MSVC)
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

