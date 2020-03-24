cmake_minimum_required(VERSION 3.0)
project(raw)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Set build type to RELEASE by default:
if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type provided, default to RELEASE.")
  set(CMAKE_BUILD_TYPE "RELEASE")
endif()

# Options

option(RAW_STATIC       "Builds a static library instead of a shared one." OFF)
option(RAW_TEST         "Adds target for tests." OFF)
option(RAW_BENCH        "Adds target for benchmarks." OFF)
option(RAW_EXAMPLES     "Builds examples." OFF)
option(RAW_CUDA         "Adds support for CUDA." OFF)
option(RAW_NATIVE       "Adds -march=native flag." OFF)
option(RAW_SANITIZE     "Adds -fsanitize=address -fsanitize=undefined flags." OFF)
option(RAW_PI           "Builds a position-independent library." ON)

# Define a few stuff

if(RAW_STATIC)
  set(RAW_LIB_TYPE STATIC)
  set(RAW_LIB_NAME "raw_static")
  set(SFMT_LIB_NAME "sfmt_static")
  add_definitions(-DRAW_STATIC_LIBRARY)
else()
  set(RAW_LIB_TYPE SHARED)
  set(RAW_LIB_NAME "raw")
  set(SFMT_LIB_NAME "sfmt")
  add_definitions(-DRAW_SHARED_LIBRARY)
endif()

add_definitions(-DSFMT_MEXP=19937)

# Find packages

find_package(Threads REQUIRED)
find_package(Math)

# Flags

set(RAW_TO_LINK ${SFMT_LIB_NAME} ${CMAKE_THREAD_LIBS_INIT} ${MATH_LIBRARIES})

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON) # Fingers crossed that it compiles on Windows...

# Subdirectories

include_directories(include include/SFMT src)
add_subdirectory(src)

if(RAW_EXAMPLES)
  add_subdirectory(examples)
endif()

if(RAW_TEST)
  enable_testing()
  add_subdirectory(test)
endif()

if(RAW_BENCH)
  add_subdirectory(bench)
endif()

# Summary

message(STATUS "")
message(STATUS "RAW BUILD SUMMARY")
message(STATUS "  CMAKE_GENERATOR               : ${CMAKE_GENERATOR}")
message(STATUS "  Build type                    : ${CMAKE_BUILD_TYPE}")
message(STATUS "  Compiler ID                   : ${CMAKE_C_COMPILER_ID}")
message(STATUS "  Library name                  : ${RAW_LIB_NAME}")
message(STATUS "  Library type                  : ${RAW_LIB_TYPE}")
message(STATUS "  Build tests                   : ${RAW_TEST}")
message(STATUS "  Build benchmarks              : ${RAW_BENCH}")
message(STATUS "  Build examples                : ${RAW_EXAMPLES}")
message(STATUS "  Position-independent library  : ${RAW_PI}")
message(STATUS "")
