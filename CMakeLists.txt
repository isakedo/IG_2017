cmake_minimum_required(VERSION 3.8)
project(IG_2017)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(SOURCE_FILES main.cpp Geometria/Punto.h Geometria/Vector.h Geometria/Tupla.h Geometria/Esfera.h Geometria/Punto_Superficie.h Geometria/Conexion.h Geometria/Cambio_Base_Inversa.h Camara.h Plano_proyeccion.h RGB.h Geometria/Matriz_transformacion.h Malla_geometrias.h Geometria/Geometria.h Geometria/Plano.h Geometria/Triangulo.h Ray_tracer.h BRDF_phong.h Path_tracer.h)
add_executable(IG_2017 ${SOURCE_FILES})
