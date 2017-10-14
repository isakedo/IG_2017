//
// Isak Edo Vivancos - 682405
//

#ifndef IG_2017_MATRIZ_H
#define IG_2017_MATRIZ_H

#include "Punto.h"

class Matriz {

protected:
    //Vectores verticales columnas 1, 2 y 3
    Vector eje_x = Vector(), eje_y = Vector(), eje_z = Vector();
    Punto punto = Punto(); //Vectores verticales columna 4

public:

    //Constructor
    Matriz() = default;
    Matriz (Vector _eje_x, Vector _eje_y, Vector _eje_z, Punto _punto) {
        eje_x = _eje_x; eje_y = _eje_y; eje_z = _eje_z; punto = _punto;
    }

};


#endif //IG_2017_MATRIZ_H
