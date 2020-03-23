set(raw_src
  codons.c
  cmp.c
  parsing_err.c
  grammar.c
  grammatical_evolution.c
  matrix.c
  str.c
)

# Compile the library
add_library(${RAW_LIB_NAME} ${RAW_LIB_TYPE} ${raw_src})

add_library(sfmt_static STATIC SFMT.c)

if(RAW_PI)
  set_property(TARGET ${RAW_LIB_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

if(RAW_NATIVE)
  target_compile_options(${RAW_LIB_NAME} PRIVATE -march=native)
  target_compile_options(sfmt_static PRIVATE -march=native)
endif()

if(RAW_SANITIZE)
  target_compile_options(${RAW_LIB_NAME} PRIVATE -fsanitize=address)
  target_compile_options(${RAW_LIB_NAME} PRIVATE -fsanitize=undefined)
endif()

target_link_libraries(${RAW_LIB_NAME} ${RAW_TO_LINK} sfmt_static)

install(TARGETS ${RAW_LIB_NAME} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(TARGETS sfmt_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(DIRECTORY ../include/ DESTINATION include)
