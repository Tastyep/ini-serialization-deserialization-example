cmake_minimum_required(VERSION 3.21)

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SHARED_TEST_DIR ${TEST_DIR}/shared)

set(PARENT_PROJECT ${PROJECT_NAME})
add_subdirectory(unit)
add_subdirectory(integration)
