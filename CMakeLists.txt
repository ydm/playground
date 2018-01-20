# +--------+
# | Common |
# +--------+
cmake_minimum_required (VERSION 3.0)

project (playground VERSION 0.0.1 LANGUAGES C)
set (CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Common headers
include_directories ("src/inc")

# Compiler flags
#
# https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
# cmake/flags/gcc is up to -Wmissing-include-dirs
if (CMAKE_COMPILER_IS_GNUCC)
  file (READ ./cmake/flags/gcc _flags)
elseif (${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
  file (READ ./cmake/flags/clang _flags)
endif ()
string (REPLACE "\n" " " _xs "${_flags}")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${_xs}")


# +-------------+
# | Executables |
# +-------------+
# 1. play -- the main thing here
file (GLOB _sources "src/*.c")
add_executable (play "${_sources};exec/play.c")
# target_link_libraries (play m)

# 2. check -- (unit) tests
file (GLOB _tests "test/*.c")
add_executable (check "${_sources};${_tests};exec/check.c")
