//
// Isak Edo Vivancos - 682405
// Geometría de la esfera con un centro, punto de referencia y un vector axis
//

#ifndef IG_2017_ESFERA_H
#define IG_2017_ESFERA_H

#include "Punto.h"

class Esfera {

private:
    Punto centro = Punto(), referencia = Punto(); //Globales
    Vector axis = Vector();

public:

    //Constructor
    Esfera() = default;
    Esfera (Punto _centro, Punto _referencia, Vector _axis) {
        float radio_rc = (_referencia - _centro).mod();
        float radio_ax = _axis.mod() / 2;
        if((radio_ax - 0.000001) < radio_rc && (radio_ax + 0.000001) > radio_rc)
        { centro = _centro; referencia  = _referencia; axis = _axis; }
    }

    const Punto &getCentro() const {
        return centro;
    }

    const Punto &getReferencia() const {
        return referencia;
    }

    const Vector &getAxis() const {
        return axis;
    }

};


#endif //IG_2017_ESFERA_H
