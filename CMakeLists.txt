cmake_minimum_required(VERSION 3.0)
project(randamu)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Set build type to RELEASE by default:
if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type provided, default to RELEASE.")
  set(CMAKE_BUILD_TYPE "RELEASE")
endif()

# Options

option(RANDAMU_STATIC       "Builds a static library instead of a shared one." OFF)
option(RANDAMU_TEST         "Adds target for tests." OFF)
option(RANDAMU_BENCH        "Adds target for benchmarks." OFF)
option(RANDAMU_EXAMPLES     "Builds examples." OFF)
option(RANDAMU_CUDA         "Adds support for CUDA." OFF)
option(RANDAMU_NATIVE       "Adds -march=native flag." OFF)
option(RANDAMU_SANITIZE     "Adds -fsanitize=address -fsanitize=undefined flags." OFF)
option(RANDAMU_PI           "Builds a position-independent library." OFF)

# Define a few stuff

if(RANDAMU_STATIC)
  set(RANDAMU_LIB_TYPE STATIC)
  set(RANDAMU_LIB_NAME "randamu_static")
  add_definitions(-DRANDAMU_STATIC_LIBRARY)
else()
  set(RANDAMU_LIB_TYPE SHARED)
  set(RANDAMU_LIB_NAME "randamu")
  add_definitions(-DRANDAMU_SHARED_LIBRARY)
endif()

add_definitions(-DSFMT_MEXP=19937)

# Find packages

find_package(Threads REQUIRED)
find_package(Math)

# Flags

set(RANDAMU_TO_LINK ${CMAKE_THREAD_LIBS_INIT} ${MATH_LIBRARIES})

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON) # Fingers crossed that it compiles on Windows...

# Subdirectories

include_directories(include include/SFMT src)
add_subdirectory(src)

if(RANDAMU_EXAMPLES)
  add_subdirectory(examples)
endif()

if(RANDAMU_TEST)
  enable_testing()
  add_subdirectory(test)
endif()

if(RANDAMU_BENCH)
  add_subdirectory(bench)
endif()

# Summary

message(STATUS "")
message(STATUS "RANDAMU BUILD SUMMARY")
message(STATUS "  CMAKE_GENERATOR               : ${CMAKE_GENERATOR}")
message(STATUS "  Build type                    : ${CMAKE_BUILD_TYPE}")
message(STATUS "  Compiler ID                   : ${CMAKE_C_COMPILER_ID}")
message(STATUS "  Library name                  : ${RANDAMU_LIB_NAME}")
message(STATUS "  Library type                  : ${RANDAMU_LIB_TYPE}")
message(STATUS "  Build tests                   : ${RANDAMU_TEST}")
message(STATUS "  Build benchmarks              : ${RANDAMU_BENCH}")
message(STATUS "  Build examples                : ${RANDAMU_EXAMPLES}")
message(STATUS "  Position-independent library  : ${RANDAMU_PI}")
message(STATUS "")
