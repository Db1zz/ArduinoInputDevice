cmake_minimum_required(VERSION 3.12)
project(Input)

add_library(Transmitter STATIC Transmitter.cpp Transmitter.h)
set_target_properties(
    Transmitter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)                                       