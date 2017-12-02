#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include "Geometria/Tupla.h"
#include "Geometria/Vector.h"
#include "Geometria/Punto.h"
#include "Geometria/Matriz_transformacion.h"
#include "RGB.h"
#include "BRDF_phong.h"
#include "Geometria/Geometria.h"
#include "Geometria/Plano.h"
#include "Geometria/Esfera.h"
#include "Geometria/Triangulo.h"
#include "Malla_geometrias.h"
#include "Plano_proyeccion.h"
#include "Camara.h"
#include "Ray_tracer.h"
#include "Path_tracer.h"

int main(int argc, char **argv) {

    if(argc != 5) {
        cout << "Usage IG_2017 <num_path_pixel><width><height><output_file>"
             << endl;
        exit(-1);
    }

    auto num_path_pixel = (__uint16_t)atoi(argv[1]);
    auto num_pixeles_ejex = (__uint16_t )atoi(argv[2]);
    auto num_pixeles_ejey = (__uint16_t )atoi(argv[3]);

    //Configuracion de la escena
    //Archivo de guardado
    std::string path = argv[4];
    std::string path_ply="/home/isak/CLionProjects/IG_2017/ply/cow.ply";

    // Vectores de la camara explicitamente tienen que estar hacia la izquierda,
    // arriba y delante para la ceración del plano de proyección.
    const Vector camara_left = Vector(-320,0,0);
    const Vector camara_up = Vector(0,0,240);
    const Vector camara_forward = Vector(0,200,0);
    const Punto camara_pos = Punto(0,0,0);
    const float tmax = 1000;

    //Geometrias
    vector<Esfera> _esferas = {
        Esfera(Punto(110,300,-140),Punto(110,400,-140),Vector(0,0,200),RGB(163,228,215),
               BRDF_phong(RGB(.15,.015,.15),RGB(0.7,0.07,0.7),10)),
        Esfera(Punto(-100,350,-140),Punto(-100,450,-140),Vector(0,0,200),RGB(163,228,0),
               BRDF_phong(RGB(.15,.015,.15),RGB(0.7,0.07,0.7),10))
    };

    vector<Triangulo> _triangulos = {
    //    Triangulo(Punto(-200,220,239),Punto(200,220,239),Punto(-200,340,239),RGB(255,255,255),BRDF_phong(),true),
    //    Triangulo(Punto(200,340,239),Punto(200,220,239),Punto(-200,340,239),RGB(255,255,255),BRDF_phong(),true)
    };

    vector<Plano> _planos = {
        Plano(320,Vector(1,0,0),RGB(255,51,51),BRDF_phong(RGB(.85,.085,.085),RGB(),0)),
        Plano(320,Vector(-1,0,0),RGB(128,255,0),BRDF_phong(RGB(.085,.85,.085),RGB(),0)),
        Plano(240,Vector(0,0,-1),RGB(255,255,255),BRDF_phong(RGB(.85,.85,.85),RGB(),0),true),
        Plano(240,Vector(0,0,1),RGB(220,220,220),BRDF_phong(RGB(.85,.85,.85),RGB(),0)),
        Plano(400,Vector(0,-1,0),RGB(220,220,220),BRDF_phong(RGB(.85,.85,.85),RGB(),0)),
        Plano(5,Vector(0,1,0),RGB(220,220,200),BRDF_phong(RGB(.85,.85,.85),RGB(),0))
    };

    //Preparacion del trazador de rayos
    Camara camara = Camara(camara_left, camara_up, camara_forward, camara_pos,
        num_pixeles_ejex,num_pixeles_ejey);
   //Aqui se puede rotar la camara y el plano
    Malla_geometrias malla = Malla_geometrias();
    malla.cargar_geometrias(_esferas,_planos,_triangulos);
    //malla.cargar_triangulos_ply(path_ply);
    //malla.escalar_figura(50,50,50);
    //malla.rotar_x_figura(M_PI/2);
    //Ray_tracer ray = Ray_tracer(camara, malla, tmax);
    //Generacion de la imagen
    //ray.renderizar();
    //ray.guardar_imagen(path);


    Path_tracer pth = Path_tracer(camara, malla, tmax, num_path_pixel);
    pth.renderizar();
    pth.guardar_imagen(path);
    return 0;
}