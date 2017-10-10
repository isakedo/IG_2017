#include <iostream>
#include "Punto_Superficie.h"

int main() {
    std::cout << "Test: Esfera en el punto (1,1,1) con radio 1" << std::endl;
    Esfera esfera = Esfera(Punto(2,2,2),Punto(4,2,2),Vector(0,0,4));
    Punto_Superficie p2 = Punto_Superficie(esfera,M_PI/2,-M_PI/2);

    return 0;
}