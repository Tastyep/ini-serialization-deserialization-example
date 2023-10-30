cmake_minimum_required(VERSION 3.11)

project(IniSerDeser)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(DEPS_BOOST_LIBRARIES describe mp11)
include(cmake/FetchBoost.cmake)
find_package(Boost REQUIRED COMPONENTS ${DEPS_BOOST_LIBRARIES})

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp src/ini.cpp src/ini.h
                                       src/string.h src/file.h src/file.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::describe)

file(CREATE_LINK "${CMAKE_BINARY_DIR}/compile_commands.json"
     "${CMAKE_SOURCE_DIR}/compile_commands.json" SYMBOLIC)
