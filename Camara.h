//
// Isak Edo Vivancos - 682405
// Camara pinhole para capturar la imagen
//

#ifndef IG_2017_CAMARA_H
#define IG_2017_CAMARA_H

#include "Geometria/Vector.h"
#include "Geometria/Punto.h"

class Camara {

private:
    Vector up = Vector(), left = Vector(), forward = Vector();
    Punto posicion = Punto();

public:

    //Constructor
    Camara(Vector _left, Vector _up, Vector _forward, Punto _posicion) :
            left(_left), up(_up), forward(_forward), posicion(_posicion) {}

    const Vector &getUp() const {
        return up;
    }

    const Vector &getLeft() const {
        return left;
    }

    const Vector &getForward() const {
        return forward;
    }

    const Punto &getPosicion() const {
        return posicion;
    }

    //Faltará rotar la camara

};


#endif //IG_2017_CAMARA_H
