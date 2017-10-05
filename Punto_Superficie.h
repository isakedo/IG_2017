//
// Isak Edo Vivancos - 682405
//

#ifndef IG_2017_PUNTO_SUPERFICIE_H
#define IG_2017_PUNTO_SUPERFICIE_H


#include "Esfera.h"

class Punto_Superficie {

private:
    Esfera esfera = Esfera();
    float inclinacion, acimut;
    Punto posicion = Punto();
    Vector normal = Vector(), latitud = Vector(), longitud = Vector();

public:

    //Constructor
    Punto_Superficie(Esfera _esfera, float _inclinacion, float _acimut) {
        float pi = (float)M_PI;
        if(_inclinacion >= 0 && _inclinacion <= pi &&
                _acimut >= -pi && _acimut <= pi) {
            esfera = _esfera; inclinacion = _inclinacion; acimut = _acimut;

        }
    }


};

#endif //IG_2017_PUNTO_SUPERFICIE_H
