cmake_minimum_required(VERSION 3.5)
project(InputDevice)

add_library(InputDevice STATIC InputDevice.cpp InputDevice.h)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC InputDevice)