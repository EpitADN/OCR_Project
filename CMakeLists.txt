cmake_minimum_required(VERSION 3.12)
project(OCR_Project C)

set(CMAKE_C_STANDARD 99)

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})


add_executable(OCR_Project main.c)
#add_executable(OCR_Project test.c)
#add_executable(OCR_Project test2.c)
#add_executable(OCR_Project Main2.c)


target_link_libraries(OCR_Project ${GTK3_LIBRARIES})