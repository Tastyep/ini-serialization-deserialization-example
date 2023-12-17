cmake_minimum_required(VERSION 3.21)

project(unit LANGUAGES CXX)

if (PROJECT_IS_TOP_LEVEL)
  enable_testing()
endif()

include(${CMAKE_SOURCE_DIR}/cmake/FetchCatch2.cmake)
find_package(Catch2 REQUIRED)

set(${PROJECT_NAME}_SOURCES 
  ini.cpp
  fakefile.h
  fakefile.cpp)
list(TRANSFORM ${PROJECT_NAME}_SOURCES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_SOURCES} ${${PARENT_PROJECT}_SOURCES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain Boost::describe Boost::core)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

add_test(NAME test COMMAND ${PROJECT_NAME})
set_tests_properties(test PROPERTIES WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})


