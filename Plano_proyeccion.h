//
// Isak Edo Vivancos - 682405
// Plano de proyección sobre el que se lanzan los rayos para formar la imagen,
// se calcula el tamaño y posición con la camara.
//

#ifndef IG_2017_PLANO_PROYECCION_H
#define IG_2017_PLANO_PROYECCION_H

#include <vector>
#include "Pixel.h"
#include "Camara.h"

using namespace std;

class Plano_proyeccion {

private:
    //Matriz de pixeles
    vector<vector<Pixel>> plano;

public:

    //Constructor
    Plano_proyeccion(Camara camara) {
        __uint16_t num_pixeles_ejex = (__uint16_t) camara.getLeft().mod() * 2;
        __uint16_t num_pixeles_ejey = (__uint16_t) camara.getUp().mod() * 2;
        Punto it = camara.getPosicion() + camara.getForward() +
                camara.getUp() + camara.getLeft();

        float inicio_x = it.getX();
        for (__uint16_t y = 0; y < num_pixeles_ejey; y++) {
            vector<Pixel> aux_x;
            for (__uint16_t x = 0; x < num_pixeles_ejex; x++) {
                aux_x.push_back(Pixel(it));
                it = Punto(it.getX() + 1, it.getY(), it.getZ());
            }
            plano.push_back(aux_x);
            it = Punto(inicio_x, it.getY(), it.getZ() - 1);
        }
        float example = -1;
        float more = example * 2;
    }


};


#endif //IG_2017_PLANO_PROYECCION_H
