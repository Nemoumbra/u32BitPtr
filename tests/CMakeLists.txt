cmake_minimum_required(VERSION 3.26)
project(u32BitPtr-tests)

# enable_testing()

# 1st version
add_executable(
        Untyped_u32BitPtr_tests
        tests.cpp
)
target_link_libraries(
        Untyped_u32BitPtr_tests
        UntypedU32BitPtr_static
)
target_include_directories(
        Untyped_u32BitPtr_tests PRIVATE
        ${UntypedU32BitPtr_static_INCLUDE_DIRS}
)
add_test(
        NAME UntypedTest
        COMMAND Untyped_u32BitPtr_tests
)

# 2nd version
add_executable(
        Typed_u32BitPtr_tests
        new_tests.cpp
)
target_link_libraries(
        Typed_u32BitPtr_tests
        TypedU32BitPtr_static
)
target_include_directories(
        Typed_u32BitPtr_tests PRIVATE
        ${TypedU32BitPtr_static_INCLUDE_DIRS}
)
add_test(
        NAME TypedTest
        COMMAND Typed_u32BitPtr_tests
)
