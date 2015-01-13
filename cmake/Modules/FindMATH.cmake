find_path(MATH_INCLUDE_DIR math.h)

set(MATH_NAMES ${MATH_NAMES} m)
find_library(MATH_LIBRARY NAMES ${MATH_NAMES})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MATH DEFAULT_MSG MATH_LIBRARY MATH_INCLUDE_DIR)

if(MATH_FOUND)
  set(MATH_LIBS ${MATH_LIBRARY})
endif(MATH_FOUND)

