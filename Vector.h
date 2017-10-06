//
// Isak Edo Vivancos - 682405
//

#ifndef IG_2017_VECTOR_H
#define IG_2017_VECTOR_H

#include <cmath>
#include "Tupla.h"

class Vector : public Tupla {

public:

    //Constructor
    Vector() {}
    Vector (float _x, float _y, float _z) : Tupla(_x,_y,_z) {}

    //Operadores
    //Suma de vectores
    Vector operator+ (const Vector& vec) {
        Vector resultado = Vector (this->x + vec.x, this->y + vec.y,
                                   this->z + vec.z);
        return resultado;
    }

    //Resta de vectores
    Vector operator- (const Vector& vec) {
        Vector resultado = Vector (this->x - vec.x, this->y - vec.y,
                                   this->z - vec.z);
        return resultado;
    }

    //Producto por escalar
    Vector operator* (float es) {
        Vector resultado = Vector (this->x * es, this->y * es, this->z * es);
        return resultado;
    }

    //Division por escalar
    Vector operator/ (float es) {
        Vector resultado = Vector (this->x / es, this->y / es, this->z / es);
        return resultado;
    }

    //Producto escalar
    float operator * (const Vector& vec) {
        return this->x * vec.x + this->y * vec.y + this->z * vec.z;
    }

    //Producto vectorial
    Vector operator % (const Vector& vec) {
        Vector resultado = Vector (this->y * vec.z - this->z * vec.y,
                                   this->z * vec.x - this->x * vec.z,
                                   this->x * vec.y - this->y * vec.x);
        return resultado;
    }

    //Metodos
    //Modulo
    float mod () {
        float resultado = this->x * this->x + this->y * this->y +
                          this->z * this->z;
        resultado = sqrtf(resultado);
        return resultado;
    }
};

#endif //INFORMATICAGRAFICA_VECTOR_H