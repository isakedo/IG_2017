//
// Isak Edo Vivancos - 682405
// Pixel de el plano de proyección con su posición en coordenadas globales y
// el color correspondiente
//

#ifndef IG_2017_PIXEL_H
#define IG_2017_PIXEL_H


#include "RGB.h"
#include "Geometria/Punto.h"

class Pixel {

private:
    RGB color = RGB();
    Punto posicion = Punto();

public:

    //Constructor
    Pixel(Punto _posicion) : posicion(_posicion) {}

};


#endif //IG_2017_PIXEL_H
