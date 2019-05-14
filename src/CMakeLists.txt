set(randamu_src
  codons.c
  cmp.c
  parsing_err.c
  grammar.c
  matrix.c
  str.c
)

# Compile the library
add_library(${RANDAMU_LIB_NAME} ${RANDAMU_LIB_TYPE} ${randamu_src})

add_library(sfmt_static STATIC SFMT.c)

if(RANDAMU_PI)
  set_property(TARGET ${RANDAMU_LIB_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

if(RANDAMU_NATIVE)
  target_compile_options(${RANDAMU_LIB_NAME} PRIVATE -march=native)
  target_compile_options(sfmt_static PRIVATE -march=native)
endif()

if(RANDAMU_SANITIZE)
  target_compile_options(${RANDAMU_LIB_NAME} PRIVATE -fsanitize=address)
  target_compile_options(${RANDAMU_LIB_NAME} PRIVATE -fsanitize=undefined)
endif()

target_link_libraries(${RANDAMU_LIB_NAME} ${RANDAMU_TO_LINK} sfmt_static)

install(TARGETS ${RANDAMU_LIB_NAME} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(TARGETS sfmt_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(DIRECTORY ../include/ DESTINATION include)
