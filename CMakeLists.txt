cmake_minimum_required(VERSION 3.8)
project(IG_2017)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Punto.h Vector.h Tupla.h Esfera.h Punto_Superficie.h)
add_executable(IG_2017 ${SOURCE_FILES})
