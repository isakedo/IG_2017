//
// Isak Edo Vivancos - 682405
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
    Esfera() {}
    Esfera (Punto _centro, Punto _referencia, Vector _axis) {
        float radio_rc = (_referencia - _centro).mod();
        float radio_ax = _axis.mod() / 2;
        if((radio_ax - 0.000001) > radio_rc && (radio_ax + 0.000001) < radio_rc)
        { centro = _centro; referencia  = _referencia; axis = _axis; }
    }

};


#endif //IG_2017_ESFERA_H