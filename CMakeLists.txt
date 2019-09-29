cmake_minimum_required(VERSION 3.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

####################
# TARGET PLATFORM
####################
set(PLATFORM_LINUX OFF CACHE BOOL "Linux platform target")
set(PLATFORM_WINDOWS OFF CACHE BOOL "Windows platform target (msys/mingw64)")
set(PLATFORM_RPI3 OFF CACHE BOOL "RIP3 platform target")
set(PLATFORM_SWITCH OFF CACHE BOOL "Nintendo Switch platform target")
set(PLATFORM_3DS OFF CACHE BOOL "Nintendo 3DS platform target")
set(PLATFORM_VITA OFF CACHE BOOL "Sony PS Vita platform target")

####################
# BUILD OPTIONS
####################
set(OPTION_SDL1 OFF CACHE BOOL "SDL1 support (software, slow, unsupported)")
set(OPTION_SDL2_GL OFF CACHE BOOL "SDL2 support (OpenGL 3.3)")
set(OPTION_SDL2_GLES2 OFF CACHE BOOL "SDL2 support (OpenGLES 2.0)")
set(OPTION_SDL2_SOFT OFF CACHE BOOL "SDL2 support (software, slow)")
set(OPTION_BUILTIN_LIBCONFIG OFF CACHE BOOL "Build libconfig from sources")
set(OPTION_FREEPLAY OFF CACHE BOOL "Build with FreePlay (CM3/ZERO) support")
set(OPTION_RECALBOX_BUILDROOT OFF CACHE BOOL "Build from recalbox buildroot")
set(OPTION_SCREEN_WIDTH 1280 CACHE STRING "Custom screen width")
set(OPTION_SCREEN_HEIGHT 720 CACHE STRING "Custom screen height")
####################
# BUILD OPTIONS
####################

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
