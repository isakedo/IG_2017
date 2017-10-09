//
// Isak Edo Vivancos - 682405
//

#ifndef IG_2017_PUNTO_H
#define IG_2017_PUNTO_H

#include "Vector.h"

class Punto : public Tupla{

public:

    //Constructor
    Punto() = default;
    Punto (float _x, float _y, float _z) : Tupla(_x,_y,_z, 1) {}

    //Operadores
    //Resta de puntos
    Vector operator- (const Punto& pun) const {
        Vector resultado = Vector (this->x - pun.x, this->y - pun.y,
                                   this->z - pun.z);
        return resultado;
    }

    //Punto mas dirección
    Punto operator+ (const Vector& vec) const {
        Punto resultado = Punto (this->x + vec.getX(), this->y + vec.getY(),
                                   this->z + vec.getZ());
        return resultado;
    }

};

#endif //IF_2017_PUNTO_H
