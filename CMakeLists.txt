cmake_minimum_required(VERSION 3.12)
project(OCR_Project C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(OCR_Project
        Load_Image.c
        Load_Image.h
        mainSegmentation.c
        Segmentation.c
        Segmentation.h)

target_link_libraries(OCR_Project -lm SDL_image SDL)
