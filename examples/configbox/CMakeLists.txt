cmake_minimum_required(VERSION 3.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

project(configbox)

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
add_executable(${PROJECT_NAME}.elf ${SOURCES})
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${INCLUDES})
target_compile_options(${PROJECT_NAME}.elf PRIVATE ${CUSTOM_CFLAGS})
target_compile_options(${PROJECT_NAME}.elf PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-std=c++14 -fexceptions>)
target_link_libraries(${PROJECT_NAME}.elf cross2d ${CUSTOM_LDFLAGS})


#############
# targets
#############
include(../../libcross2d/Targets.cmake)
