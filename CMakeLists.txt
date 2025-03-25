cmake_minimum_required(VERSION 3.26)
project(u32BitPtr)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        u32BitPtr
        main.cpp
        tests/tests.cpp tests/new_tests.cpp
        u32_bit_ptr.cpp new_u32_bit_ptr.cpp
)
