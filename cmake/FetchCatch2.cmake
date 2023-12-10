cmake_minimum_required(VERSION 3.24)

set(FETCHCONTENT_QUIET FALSE)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
  FIND_PACKAGE_ARGS NAMES Catch2
)

FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

