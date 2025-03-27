cmake_minimum_required(VERSION 3.26)
project(u32BitPtr)


# Options
option(u32BitPtr_BUILD_TESTING "Enable testing for u32BitPtr" ON)


# General settings
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

if (u32BitPtr_BUILD_TESTING)
    message(STATUS "Tests are enabled...")
    add_subdirectory(tests)
endif()
