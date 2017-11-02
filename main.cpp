#include "Geometria/Tupla.h"
#include "Geometria/Vector.h"
#include "Geometria/Punto.h"
#include "RGB.h"
#include "Pixel.h"
#include "Geometria/Geometria.h"
#include "Geometria/Esfera.h"
#include "Geometria/Malla_geometrias.h"
#include "Camara.h"
#include "Plano_proyeccion.h"
#include "Ray_tracing.h"

int main() {

    //Configuracion de la escena

    // Vectores de la camara explicitamente tienen que estar hacia la izquierda,
    // arriba y delante para la ceración del plano de proyección.
    const Vector camara_left = Vector(-150,0,0);
    const Vector camara_up = Vector(0,0,150);
    const Vector camara_forward = Vector(0,50,0);
    const Punto camara_pos = Punto(0,0,0);

    //Geometrias
    const Esfera _esferas[num_esferas] = {
        Esfera(Punto(100,0,0),Punto(150,0,0),Vector(0,0,100),RGB(163,228,215))
    };

    //Preparacion del trazador de rayos
    Camara camara = Camara(camara_left, camara_up, camara_forward, camara_pos);
    Plano_proyeccion plano = Plano_proyeccion(camara);
   //Aqui se puede rotar la camara y el plano
    Malla_geometrias malla = Malla_geometrias();
    malla.cargar_geometrias(_esferas);
    Ray_tracing ray = Ray_tracing(camara, plano, malla);
    //Generacion de la imagen
    ray.renderizar();
    ray.guardar_imagen();
    return 0;
}