cmake_minimum_required(VERSION 3.21)

set(PARENT_PROJECT ${PROJECT_NAME})
project(IniSerDeserTest LANGUAGES CXX)

if (PROJECT_IS_TOP_LEVEL)
  enable_testing()
endif()

include(${CMAKE_SOURCE_DIR}/cmake/FetchCatch2.cmake)
find_package(Catch2 REQUIRED)

set(${PROJECT_NAME}_SOURCES ini.cpp)
list(TRANSFORM ${PROJECT_NAME}_SOURCES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

message(STATUS "SRCS2: ${${PARENT_PROJECT}_SOURCES}")

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${${PARENT_PROJECT}_SOURCES} ${${PROJECT_NAME}_SOURCES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_test(NAME test COMMAND ${PROJECT_NAME})
set_tests_properties(test PROPERTIES WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})


