cmake_minimum_required(VERSION 3.26)
project(u32BitPtr-tests)

add_executable(
        Untyped_u32BitPtr_tests
        tests/tests.cpp tests/new_tests.cpp
        src/u32_bit_ptr.cpp src/new_u32_bit_ptr.cpp
)

add_executable(
        Typed_u32BitPtr_tests
        tests/tests.cpp tests/new_tests.cpp
        src/u32_bit_ptr.cpp src/new_u32_bit_ptr.cpp
)