cmake_minimum_required(VERSION 3.11)

project(IniSerDeser)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp src/ini.cpp src/ini.h src/string.h)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
