set(randamu_test_src
  test_common.c
  test_numbers.c
  test_randalloc.c
  test_rng_double.c
  test_rng_init.c
  test_rng_normal.c
  test_rng_seq.c
  test_rng_uint.c
  test_sort.c
)

source_group("Randamu Tests Source" FILES ${randamu_test_src})

# Macro for adding tests:
macro(add_librandamu_test NAME)
  add_executable(${NAME} ${NAME}.c)
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
