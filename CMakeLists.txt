cmake_minimum_required(VERSION 3.11)

project(IniSerDeser LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTS "Build test executables" OFF)

set(DEPS_BOOST_LIBRARIES core describe mp11)
include(cmake/FetchBoost.cmake)
find_package(Boost REQUIRED COMPONENTS ${DEPS_BOOST_LIBRARIES})

set(${PROJECT_NAME}_SOURCES
    conversion.h
    example.h
    file.h
    filefactory.h
    ini.cpp
    ini.h
    stdfile.h
    stdfile.cpp
    stdfilefactory.h
    stdfilefactory.cpp
    string.h
    transformini.h
    transformini.cpp)
list(TRANSFORM ${PROJECT_NAME}_SOURCES PREPEND ${CMAKE_SOURCE_DIR}/src/)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp ${${PROJECT_NAME}_SOURCES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::describe Boost::core)

if(BUILD_TESTS)
  message(STATUS "Configuring Tests")
  add_subdirectory(test)
endif()

file(CREATE_LINK "${CMAKE_BINARY_DIR}/compile_commands.json"
     "${CMAKE_SOURCE_DIR}/compile_commands.json" SYMBOLIC)
