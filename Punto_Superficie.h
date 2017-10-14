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
    Punto posicion = Punto();
    Vector normal = Vector(), latitud = Vector(), longitud = Vector();

    void calcular_punto(float inclinacion, float acimut) {
        Vector ref = esfera.getReferencia() - esfera.getCentro();
        float mod = ref.mod(); // radio de la esfera

        Vector aux_z = esfera.getAxis() / 2;
        aux_z = aux_z / aux_z.mod(); // normalizar
        Vector aux_y = aux_z % ref;
        aux_y = aux_y / aux_y.mod(); // normalizar
        Vector aux_x = aux_y % aux_z;
        aux_x = aux_x / aux_x.mod(); // normalizar
        aux_z = aux_z * mod; aux_y = aux_y * mod; aux_x = aux_x * mod;
        Cambio_Base base_esfera = Cambio_Base (aux_x, aux_y, aux_z,
                                               esfera.getCentro());
        Punto posicion_locales = Punto (sinf(inclinacion) * cosf(acimut),
         sinf(inclinacion) * sinf(acimut), cosf(inclinacion));
        posicion = base_esfera * posicion_locales;
    }

    void calcular_coordenas() {
        Vector aux = posicion - esfera.getCentro();
        latitud = esfera.getAxis() % aux;
        latitud = latitud / latitud.mod(); // normalizar
        longitud = aux % latitud;
        longitud = longitud / longitud.mod(); // normalizar
        normal = latitud % longitud;
        normal = normal / normal.mod(); // normalizar
    }

public:

    //Constructor
    Punto_Superficie() = default;
    Punto_Superficie(Esfera _esfera, float inclinacion, float acimut) {
        auto pi = (float)M_PI;
        if(inclinacion > 0 && inclinacion < pi &&
                acimut > -pi && acimut <= pi) {
            esfera = _esfera;
            calcular_punto(inclinacion, acimut);
            calcular_coordenas();
        }
    }

    //Getters
    const Punto &getPosicion() const {
        return posicion;
    }

    const Vector &getNormal() const {
        return normal;
    }

    const Vector &getLatitud() const {
        return latitud;
    }

    const Vector &getLongitud() const {
        return longitud;
    }

};

#endif //IG_2017_PUNTO_SUPERFICIE_H
