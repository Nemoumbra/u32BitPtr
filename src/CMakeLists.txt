cmake_minimum_required(VERSION 3.26)
project(u32BitPtr-lib)

# Let's make both!

add_library(
        lib_UntypedU32BitPtr_shared SHARED
        u32_bit_ptr.cpp
)
add_library(
        lib_UntypedU32BitPtr_static STATIC
        u32_bit_ptr.cpp
)

add_library(
        lib_TypedU32BitPtr_shared SHARED
        new_u32_bit_ptr.cpp
)
add_library(
        lib_TypedU32BitPtr_static STATIC
        new_u32_bit_ptr.cpp
)

#target_include_directories(lib_UntypedU32BitPtr )