#include <iostream>
#include "Punto_Superficie.h"
#include "Conexion.h"

int main() {
    std::cout << "Test: Esfera en el punto (1,1,1) con radio 1" << std::endl;
    Esfera esfera = Esfera(Punto(2,2,2),Punto(4,2,2),Vector(0,0,4));
    Punto_Superficie origen = Punto_Superficie(esfera,M_PI/2,M_PI/2);
    Esfera esfera2 = Esfera(Punto(8,8,8),Punto(6,8,8), Vector(0,0,4));
    Punto_Superficie destino = Punto_Superficie(esfera2,M_PI/2,M_PI/2);
    Conexion con = Conexion(origen,destino);
    return 0;
}