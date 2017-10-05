//
// Isak Edo Vivancos - 682405
//

#ifndef IG_2017_PUNTO_H
#define IG_2017_PUNTO_H

#include "Vector.h"

class Punto : public Tupla{

public:

    //Constructor
    Punto() {}
    Punto (float _x, float _y, float _z) : Tupla(_x,_y,_z) {}

    //Operadores
    //Resta de puntos
    Vector operator- (const Punto& pun) {
        Vector resultado = Vector (pun.x - this->x, pun.y - this->y,
                                   pun.z - this->z);
        return resultado;
    }

    //Punto mas dirección
    Punto operator+ (const Vector& vec) {
        Punto resultado = Punto (this->x + vec.x, this->y + vec.y,
                                   this->z + vec.z);
        return resultado;
    }

};

#endif //IF_2017_PUNTO_H
