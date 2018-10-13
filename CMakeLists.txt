cmake_minimum_required(VERSION 3.12)
project(OCR C)

set(CMAKE_C_STANDARD 99)

add_executable(OCR main.c Node.h Network.h Layer.h Node.c Layer.c Network.c Transition.h Transition.c Backprop.c Backprop.h)

target_link_libraries(OCR m)