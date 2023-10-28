cmake_minimum_required(VERSION 3.12)
project(InputDevice)

add_library(Transmitter STATIC Transmitter.cpp Transmitter.h)
set_target_properties(Transmitter PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED ON
)                                       