cmake_minimum_required(VERSION 3.3)
project(zadacha2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(zadacha2_BINARY_DIR "/home/altair/ClionProjects/vichmaty/zadacha2/test/")


set(SOURCE_FILES main.cpp interpolTask.cpp interpolTask.h Point.cpp Point.h Interpolation.cpp Interpolation.h types.h Coefficient2.cpp Coefficient2.h)
add_executable(zadacha2 ${SOURCE_FILES})
