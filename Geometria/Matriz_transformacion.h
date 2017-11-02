//
// Isak Edo Vivancos - 682405
// Matriz de transformación generica 4x4, pensada con el siguiente formato:
//  [ e e e p ]
//  [ j j j u ]
//  [ x y z n ]
//  [ 0 0 0 1 ]
//

#pragma once

class Matriz_transformacion {

protected:
    //Vectores verticales columnas 1, 2 y 3
    Vector eje_x = Vector(), eje_y = Vector(), eje_z = Vector();
    Punto punto = Punto(); //Vectores verticales columna 4

public:

    //Constructor
    Matriz_transformacion() = default;
    Matriz_transformacion (Vector _eje_x, Vector _eje_y, Vector _eje_z,
    Punto _punto) : eje_x(_eje_x), eje_y(_eje_y), eje_z(_eje_z), punto(_punto){}

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