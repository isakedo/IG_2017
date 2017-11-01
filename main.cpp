#include <iostream>
#include "Camara.h"
#include "Plano_proyeccion.h"

using namespace std;

// Vectores de la camara explicitamente tienen que estar hacia la izquierda,
// arriba y delante para la ceración del plano de proyección.
const Vector camara_left = Vector(-540,0,0);
const Vector camara_up = Vector(0,0,360);
const Vector camara_forward = Vector(0,100,0);
const Punto camara_posicion = Punto(0,0,0);

int main() {
    Camara cam = Camara(camara_left, camara_up, camara_forward,
                        camara_posicion);
    Plano_proyeccion plano = Plano_proyeccion(cam);
    return 0;
}