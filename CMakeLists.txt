cmake_minimum_required(VERSION 2.8) 
project(randomu) 

enable_testing()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -lm")

#add_subdirectory(src) 
add_subdirectory(tests) 

add_test(
  NAME test_random_seq
  COMMAND test_random_seq
)

set_target_properties(test_random_seq
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

