cmake_minimum_required(VERSION 3.5)

project(matrices)

# if (NOT CMAKE_CXX_STANDARD AND NOT CMAKE_CXX_COMPILER)
#         set(CMAKE_CXX_STANDARD 20)
# endif()
set(CMAKE_CXX_STANDARD 20)
option(MATRICES "Building main programm without tests" ON)
option(TESTS "Building main programm with tests" OFF)

message("CMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}")
message("CMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}")

if (TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(TESTS)

add_subdirectory(src)

 