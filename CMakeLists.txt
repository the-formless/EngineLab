cmake_minimum_required(VERSION 3.16)
project(EngineLab)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(engine_lab
    src/main.cpp
    tests/math_tests.cpp
)

target_include_directories(engine_lab PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(engine_lab PRIVATE -Wall -Wextra -Wpedantic)
endif()