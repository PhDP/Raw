cmake_minimum_required(VERSION 2.8)
project(randamu)

option(BuildTests "BuildTests" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type provided, default to RELEASE.")
  set(CMAKE_BUILD_TYPE "RELEASE")
endif ()

find_package(MATH)

################################################################
# FILES ########################################################

include_directories(include)

set(randamu_headers
  include/randamu/common.h
  include/randamu/compar.h
  include/randamu/hash.h
  include/randamu/numbers.h
  include/randamu/sort.h
  include/randamu/stats.h
  include/randamu/well1024.h
  include/randamu/splitmix64.h
  include/randamu/xorshift128.h
  include/randamu/xorshift1024.h
)

source_group("Randamu Headers" FILES ${randamu_headers})

set(randamu_src
  src/compar.c
  src/hash.c
  src/numbers.c
  src/sort.c
  src/splitmix64.c
  src/well1024.c
  src/xorshift128.c
  src/xorshift1024.c
)

source_group("Randamu Source" FILES ${randamu_src})

################################################################
# BUILD LIBRARY ################################################

add_library(randamu STATIC ${randamu_src})

target_link_libraries(randamu ${MATH_LIBS})

################################################################
# INSTALLATION #################################################

install(TARGETS randamu DESTINATION lib)
install(DIRECTORY include/randamu DESTINATION include)

################################################################
# TESTS ########################################################

if (BuildTests)
  enable_testing()
  add_subdirectory(tests)
endif ()

################################################################
# SUMMARY ######################################################

message(STATUS "")
message(STATUS "BUILD SUMMARY")
message(STATUS "  CMAKE_GENERATOR      : ${CMAKE_GENERATOR}")
message(STATUS "  Build tests          : ${BuildTests}")
message(STATUS "  Compiler ID          : ${CMAKE_C_COMPILER_ID}")
message(STATUS "  Build type           : ${CMAKE_BUILD_TYPE}")
message(STATUS "  C_FLAGS              : ${CMAKE_C_FLAGS}")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "RELEASE")
  message(STATUS "  C_FLAGS_RELEASE      : ${CMAKE_C_FLAGS_RELEASE}")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
  message(STATUS "  C_FLAGS_DEBUG        : ${CMAKE_C_FLAGS_DEBUG}")
endif ()
message(STATUS "")
