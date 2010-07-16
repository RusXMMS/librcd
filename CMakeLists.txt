cmake_minimum_required(VERSION 2.6.3)
project(librcd)

set(CMAKE_BUILD_TYPE RELEASE)

if (NOT WIN32)
    message(FATAL_ERROR "Windows only, use autotools to build under POSIX-capable systems")
endif(NOT WIN32)

add_subdirectory(src)

