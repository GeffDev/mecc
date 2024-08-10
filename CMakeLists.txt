cmake_minimum_required(VERSION 3.5)

project(mecc C)

# FIXME: Don't use glob, list all files
file(GLOB SRCS ${CMAKE_SOURCE_DIR}/src/*.c)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} ${SRCS})

# Compiler flags
if (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    # WHAT
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /Z7 /W4 /wd4146 /wd4245 /RTCcsu")
else()
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g3 -Wnull-dereference -Wwrite-strings -Wformat=2 -Wcast-align -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion -fsanitize=undefined -fsanitize-trap")
endif()
