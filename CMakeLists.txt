cmake_minimum_required(VERSION 2.8)
project(randamu)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type provided, default to RELEASE.")
  set(CMAKE_BUILD_TYPE "RELEASE")
endif ()

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
install(DIRECTORY include/randamu DESTINATION include)

################################################################
# TESTS ########################################################

set(all_tests "")

# Macro for adding tests:
macro(add_librandamu_test NAME)
  list(APPEND all_tests ${NAME})
  add_executable(${NAME} tests/${NAME}.c)
  target_link_libraries(${NAME} ${MATH_LIBS} randamu)
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

