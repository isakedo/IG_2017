#include <iostream>
#include "Punto_Superficie.h"

int main() {
    std::cout << "Test: Esfera en el punto (1,1,1) con radio 1" << std::endl;
    Esfera esfera = Esfera(Punto(1,1,1),Punto(2,1,1),Vector(0,0,2));
    Punto_Superficie p2 = Punto_Superficie(esfera,M_PI/4,M_PI/4);

    return 0;
}