//
// Isak Edo Vivancos - 682405
// Matriz de transformación de cambio de base inversa, invierte en el
// constructor teniendo en cuenta que son ortonormales los vectores
//

#ifndef IG_2017_CAMBIO_BASE_INVERSA_H
#define IG_2017_CAMBIO_BASE_INVERSA_H

#include "Matriz_transformacion.h"

class Cambio_Base_Inversa : public Matriz_transformacion {

public:

    //Constructor
    /*Solo sirve para ejes ortonormales:
     * Si A = [ M b ]
     *        [ 0 1 ]
     * inv(A) = [ inv(M) -inv(M)*b ]
     *          [  0         1     ]
     */
    Cambio_Base_Inversa (Vector _eje_x, Vector _eje_y, Vector _eje_z,
        Punto pun) {
        eje_x = Vector (_eje_x.getX(), _eje_y. getX(), _eje_z.getX());
        eje_y = Vector (_eje_x.getY(), _eje_y. getY(), _eje_z.getY());
        eje_z = Vector (_eje_x.getZ(), _eje_y. getZ(), _eje_z.getZ());
        punto = Punto (-eje_x.getX() * pun.getX() + -eje_y.getX() * pun.getY() +
                       -eje_z.getX() * pun.getZ(),
                       -eje_x.getY() * pun.getX() + -eje_y.getY() * pun.getY() +
                       -eje_z.getY() * pun.getZ(),
                       -eje_x.getZ() * pun.getX() + -eje_y.getZ() * pun.getY() +
                       -eje_z.getZ() * pun.getZ());
    }

};


#endif //IG_2017_CAMBIO_BASE_INVERSA_H
