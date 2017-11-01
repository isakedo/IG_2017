//
// Isak Edo Vivancos
// Tupla de colores RGB con color rojo, verde y azul, entre 0 y 255
//

#ifndef IG_2017_RGB_H
#define IG_2017_RGB_H


#include "Geometria/Tupla.h"

class RGB : Tupla {

public:

    //Constructor, por defecto
    RGB() : Tupla(0,0,0) {}

    //Getters
    float getR() const {
        return x;
    }

    float getG() const {
        return y;
    }

    float getB() const {
        return z;
    }

    //Setters
    void setR(float x) {
        Tupla::x = x;
    }

    void setG(float y) {
        Tupla::y = y;
    }

    void setB(float z) {
        Tupla::z = z;
    }

};

#endif //IG_2017_RGB_H
