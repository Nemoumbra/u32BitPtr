cmake_minimum_required(VERSION 3.26)
project(u32BitPtr-lib)

# CMAKE_INCLUDE_CURRENT_DIR doesn't propagate!


add_library(
        UntypedU32BitPtr_shared SHARED
        u32_bit_ptr.cpp
)
target_include_directories(
        UntypedU32BitPtr_shared PUBLIC
        .
)

add_library(
        UntypedU32BitPtr_static STATIC
        u32_bit_ptr.cpp
)
target_include_directories(
        UntypedU32BitPtr_static PUBLIC
        .
)

add_library(
        TypedU32BitPtr_shared SHARED
        new_u32_bit_ptr.cpp
)
target_include_directories(
        TypedU32BitPtr_shared PUBLIC
        .
)

add_library(
        TypedU32BitPtr_static STATIC
        new_u32_bit_ptr.cpp
)
target_include_directories(
        TypedU32BitPtr_static PUBLIC
        .
)
