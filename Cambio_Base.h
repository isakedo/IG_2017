//
// Created by isak on 9/10/17.
//

#ifndef IG_2017_CAMBIO_BASE_H
#define IG_2017_CAMBIO_BASE_H

#include "Matriz.h"

class Cambio_Base : public Matriz{

public:

    //Constructor
    Cambio_Base (Vector _eje_x, Vector _eje_y, Vector _eje_z, Punto _punto) :
        Matriz(_eje_x, _eje_y, _eje_z, _punto) {}

    //Operaciones
    //Matriz por vector cambio de base
    Vector operator* (const Vector& vec) const {
        Vector resultado = Vector (
                eje_x.getX() * vec.getX() + eje_y.getX() * vec.getY() +
                eje_z.getX() * vec.getZ(),
                eje_x.getY() * vec.getX() + eje_y.getY() * vec.getY() +
                eje_z.getY() * vec.getZ(),
                eje_x.getZ() * vec.getX() + eje_y.getZ() * vec.getY() +
                eje_z.getZ() * vec.getZ());
        return resultado;
    }

    //Matriz por punto cambio de base
    Punto operator* (const Punto& pun) const {
        Punto resultado = Punto (
                eje_x.getX() * pun.getX() + eje_y.getX() * pun.getY() +
                eje_z.getX() * pun.getZ() + punto.getX() * pun.getBit(),
                eje_x.getY() * pun.getX() + eje_y.getY() * pun.getY() +
                eje_z.getY() * pun.getZ() + punto.getY() * pun.getBit(),
                eje_x.getZ() * pun.getX() + eje_y.getZ() * pun.getY() +
                eje_z.getZ() * pun.getZ() + punto.getZ() * pun.getBit());
        return resultado;
    }

};


#endif //IG_2017_CAMBIO_BASE_H
