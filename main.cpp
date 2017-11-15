#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include "Geometria/Tupla.h"
#include "Geometria/Vector.h"
#include "Geometria/Punto.h"
#include "Geometria/Matriz_transformacion.h"
#include "RGB.h"
#include "Geometria/Geometria.h"
#include "Geometria/Plano.h"
#include "Geometria/Esfera.h"
#include "Geometria/Triangulo.h"
#include "Malla_geometrias.h"
#include "Plano_proyeccion.h"
#include "Camara.h"
#include "Ray_tracer.h"

/*TODO:
    Jerarquía Bounding boxes
    Texturas
*/

int main() {

    //Configuracion de la escena
    //Archivo de guardado
    std::string path="/home/isak/CLionProjects/IG_2017/output.ppm";
    std::string path_ply="/home/isak/CLionProjects/IG_2017/ply/cow.ply";

    // Vectores de la camara explicitamente tienen que estar hacia la izquierda,
    // arriba y delante para la ceración del plano de proyección.
    const Vector camara_left = Vector(-320,0,0);
    const Vector camara_up = Vector(0,0,240);
    const Vector camara_forward = Vector(0,90,0);
    const Punto camara_pos = Punto(0,-150,0);
    const float tmax = 1000;

    //Geometrias
    const Esfera _esferas[num_esferas] = {
        //Esfera(Punto(0,150,0),Punto(0,200,0),Vector(0,0,100),RGB(163,228,215))
    };

    const Plano _planos[num_planos] = {
        /*Plano(320,Vector(1,0,0),RGB(255,0,0)),
        Plano(320,Vector(-1,0,0),RGB(255,0,0)),
        Plano(240,Vector(0,0,-1),RGB(0,255,0)),
        Plano(240,Vector(0,0,1),RGB(0,255,0)),
        Plano(300,Vector(0,-1,0),RGB(0,0,255))*/
    };

    //Preparacion del trazador de rayos
    Camara camara = Camara(camara_left, camara_up, camara_forward, camara_pos);
   //Aqui se puede rotar la camara y el plano
    Malla_geometrias malla = Malla_geometrias();
    malla.cargar_geometrias(_esferas,_planos);
    malla.cargar_triangulos_ply(path_ply);
    malla.escalar_figura(50,50,50);
    malla.rotar_x_figura(M_PI/2);
    Ray_tracer ray = Ray_tracer(camara, malla, tmax);
    //Generacion de la imagen
    ray.renderizar();
    ray.guardar_imagen(path);
    return 0;
}