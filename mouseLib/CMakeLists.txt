cmake_minimum_required(VERSION 3.12)
project(Input)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../transmitterLib)

add_library(Mouse STATIC Mouse.cpp Mouse.h)

set_target_properties(
    Mouse PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_link_libraries(Mouse PRIVATE Transmitter)