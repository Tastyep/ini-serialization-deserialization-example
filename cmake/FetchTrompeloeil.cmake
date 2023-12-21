cmake_minimum_required(VERSION 3.24)

set(FETCHCONTENT_QUIET FALSE)

include(FetchContent)
FetchContent_Declare(
  trompeloeil
  GIT_REPOSITORY https://github.com/rollbear/trompeloeil
  GIT_TAG        v46
  FIND_PACKAGE_ARGS NAMES trompeloeil
)

FetchContent_MakeAvailable(trompeloeil)

