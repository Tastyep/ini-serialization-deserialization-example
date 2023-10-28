cmake_minimum_required(VERSION 3.24)

set(BOOST_INCLUDE_LIBRARIES describe)
set(FETCHCONTENT_QUIET FALSE)

include(FetchContent)
FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.83.0
  GIT_PROGRESS TRUE
  FIND_PACKAGE_ARGS NAMES describe)
FetchContent_MakeAvailable(Boost)
