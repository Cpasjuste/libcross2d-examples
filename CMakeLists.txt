cmake_minimum_required(VERSION 3.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

# delete cmake cache folder before changing a build setting/option
set(BUILD_SFML OFF CACHE BOOL "Build with SFML support")
set(BUILD_SDL1 OFF CACHE BOOL "Build with SDL1 support")
set(BUILD_SDL1_GL OFF CACHE BOOL "Build with SDL1 support (hardware rendering, fast, needs BUILD_SDL1=ON)")
set(BUILD_SDL2 ON CACHE BOOL "Build with SDL2 support")
set(BUILD_SDL2_SOFT OFF CACHE BOOL "Build with SDL2 support (software rendering, needs BUILD_SDL2=ON)")
set(BUILD_VITA OFF CACHE BOOL "Build with Ps Vita support")
set(BUILD_PS3 OFF CACHE BOOL "Build with PS3 support")
set(BUILD_3DS OFF CACHE BOOL "Build with 3DS support")
set(BUILD_SWITCH OFF CACHE BOOL "Build with Nintendo Switch support")

# add libcross2d library
add_subdirectory(libcross2d)

# required for cmake toolchain setup
project(cross2d-examples)

# font example
add_subdirectory(examples/font)

# texture example
add_subdirectory(examples/texture)

# input example
add_subdirectory(examples/input)

# fps example
add_subdirectory(examples/fps)

# crazy example ?
add_subdirectory(examples/crazy)