#include <iostream>
#include "Punto_Superficie.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Vector v1 = Vector(1,5,0);
    Vector v2 = Vector(-3,0,2);
    Vector v3 = v1 + v2;
    Vector v4 = v1 - v2;
    Vector v5 = v1 * 3;
    Vector v6 = v1 / 3;
    float v7 = v1.mod();
    float v8 = v1 * v2;
    Vector v9 = v1 % v2;
    Punto_Superficie p1 = Punto_Superficie(Esfera(),0.0f,0.0f);

    return 0;
}