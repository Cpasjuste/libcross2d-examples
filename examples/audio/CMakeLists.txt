cmake_minimum_required(VERSION 3.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

project(audio)

set(PROJECT_AUTHOR "Cpasjuste")
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
# ps vita
set(TITLE_ID "CROSS0001")

#############
# code
#############
set(INCLUDES source include)
file(GLOB SOURCES source/*.cpp)
set(CUSTOM_CFLAGS
        -DVERSION_MAJOR="${VERSION_MAJOR}"
        -DVERSION_MINOR="${VERSION_MINOR}")
set(CUSTOM_LDFLAGS)

#############
# executable
#############
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})
target_compile_options(${PROJECT_NAME} PRIVATE ${CUSTOM_CFLAGS})
target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-std=c++14 -fexceptions>)
target_link_libraries(${PROJECT_NAME} cross2d ${CUSTOM_LDFLAGS})

#############
# targets
#############
include(${CMAKE_SOURCE_DIR}/libcross2d/cmake/targets.cmake)
