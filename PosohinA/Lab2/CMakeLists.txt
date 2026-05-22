cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(The_Polynomial_Calculator)

include(cmake/function.cmake)

add_subdirectory(main)
add_subdirectory(lib_list)
add_subdirectory(lib_polynomial)
add_subdirectory(lib_interface)
add_subdirectory(lib_table)

option(BTEST "build test?" ON)

if(BTEST)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory("third_party/gtest" EXCLUDE_FROM_ALL)
    enable_testing()
    add_subdirectory(tests)
endif()


