cmake_minimum_required(VERSION 3.12)
project(OCR_Project C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_executable(OCR_Project
        Backprop.c
        Backprop.h
        Layer.c
        Layer.h
        main.c
        Network.c
        Network.h
        Node.c
        Node.h
        SaveAndLoad.c
        SaveAndLoad.h

        Trainer.c
        Trainer.h
        Transition.c
        Transition.h UI.c UI.h)


target_link_libraries(OCR_Project ${GTK3_LIBRARIES} -lm)