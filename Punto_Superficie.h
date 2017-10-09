//
// Isak Edo Vivancos - 682405
//

#ifndef IG_2017_PUNTO_SUPERFICIE_H
#define IG_2017_PUNTO_SUPERFICIE_H


#include "Esfera.h"
#include "Cambio_Base.h"

class Punto_Superficie {

private:
    Esfera esfera = Esfera();
    float inclinacion, acimut;
    Punto posicion = Punto();
    Vector normal = Vector(), latitud = Vector(), longitud = Vector();

    void calcular_punto() {
        Vector ref = esfera.getReferencia() - esfera.getCentro();
        float mod = ref.mod(); // radio de la esfera

        Vector aux_z = esfera.getAxis() / 2;
        aux_z = aux_z / aux_z.mod(); // normalizar
        Vector aux_y = aux_z % ref;
        aux_y = aux_y / aux_y.mod(); // normalizar
        Vector aux_x = aux_y % aux_z;
        aux_x = aux_x / aux_x.mod(); // normalizar
        Cambio_Base base_esfera = Cambio_Base (aux_x, aux_y, aux_z,
                                               esfera.getCentro());
        Punto test = Punto (mod * sinf(inclinacion) * sinf(acimut),
              mod * sinf(inclinacion) * cosf(acimut), mod * cosf(inclinacion));
        Punto test2 = base_esfera * test;
    }

    void calcular_coordenas() {
        //
    }

public:

    //Constructor
    Punto_Superficie(Esfera _esfera, float _inclinacion, float _acimut) {
        float pi = (float)M_PI;
        if(_inclinacion >= 0 && _inclinacion <= pi &&
                _acimut >= -pi && _acimut <= pi) {
            esfera = _esfera; inclinacion = _inclinacion; acimut = _acimut;
            calcular_punto();
        }
    }


};

#endif //IG_2017_PUNTO_SUPERFICIE_H
