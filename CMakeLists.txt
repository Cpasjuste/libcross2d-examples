cmake_minimum_required(VERSION 3.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

# add libcross2d library
add_subdirectory(libcross2d)

# required for cmake toolchain setup
project(cross2d-examples)

# examples
add_subdirectory(examples/font)
add_subdirectory(examples/texture)
add_subdirectory(examples/sprite)
add_subdirectory(examples/gradient_rectangle)
add_subdirectory(examples/input)
add_subdirectory(examples/fps)
add_subdirectory(examples/config)
add_subdirectory(examples/configbox)
add_subdirectory(examples/filer)
add_subdirectory(examples/crazy)
