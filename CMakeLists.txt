cmake_minimum_required(VERSION 3.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

# delete cmake cache folder before changing a build setting/option
set(BUILD_SFML OFF CACHE BOOL "Build with SFML support")
set(BUILD_SDL1 OFF CACHE BOOL "Build with SDL1 support (software, osmesa) support")
set(BUILD_SDL1_GL OFF CACHE BOOL "Build with SDL1 support (hardware rendering, fast, needs BUILD_SDL1=ON)")
set(BUILD_SDL2 OFF CACHE BOOL "Build with SDL2 (software) support")
set(BUILD_SDL2_GL OFF CACHE BOOL "Build with SDL2 support (hardware rendering, fast, needs BUILD_SDL2=ON)")
set(BUILD_PSP2 OFF CACHE BOOL "Build with PSP2 support")
set(BUILD_PS3 OFF CACHE BOOL "Build with PS3 support")
set(BUILD_3DS OFF CACHE BOOL "Build with 3DS support")
set(BUILD_NX OFF CACHE BOOL "Build with NX (SWITCH) support")

# add libcross2d/libcross2dui library. If you want to port pfba to another platform,
# you should (may) only need to port libcross2d library.
add_subdirectory(libcross2d)

# required for cmake toolchain setup
project(cross2d-examples)

# font example
add_subdirectory(examples/font)

# texture example
add_subdirectory(examples/texture)