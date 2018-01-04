#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <random>

#include "Geometria/Tupla.h"
#include "Geometria/Vector.h"
#include "Geometria/Punto.h"
#include "Geometria/Matriz_transformacion.h"
#include "RGB.h"
#include "BRDF_phong.h"
#include "Luz.h"
#include "Geometria/Geometria.h"
#include "Geometria/Plano.h"
#include "Geometria/Esfera.h"
#include "Geometria/Triangulo.h"
#include "BoundingVolumeHierarchy.h"
#include "Malla_geometrias.h"
#include "Plano_proyeccion.h"
#include "Camara.h"
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
    time_t t = time(0);
    struct tm * now = localtime(&t);
    char buffer[80];
    strftime(buffer,sizeof(buffer),"_%d-%m-%Y_%I:%M:%S",now);
    std::string time(buffer);
    std::string path = argv[4] + time + ".ppm";
    std::string path_ply="/home/isak/CLionProjects/IG_2017/ply/big_spider.ply";

    //Random
    std::random_device rd;
    std::mt19937 mt(rd());

    // Vectores de la camara explicitamente tienen que estar hacia la izquierda,
    // arriba y delante para la ceración del plano de proyección.
    const Vector camara_left = Vector(-32,0,0);
    const Vector camara_up = Vector(0,0,24);
    const Vector camara_forward = Vector(0,20,0);
    const Punto camara_pos = Punto(0,0,-8);
    const float tmax = 400;

    //Geometrias
    vector<Esfera> _esferas = {
    //    Esfera(Punto(11,40,-14),Punto(11,50,-14),Vector(0,0,20),RGB(163,228,215),
    //           BRDF_phong(RGB(.15,.015,.15),RGB(0.7,0.07,0.7),5)),
    //    Esfera(Punto(-10,45,-14),Punto(-10,55,-14),Vector(0,0,20),RGB(163,228,0),
    //           BRDF_phong(RGB(.15,.015,.15),RGB(0.7,0.07,0.7),5)),
    };

    vector<Triangulo> _triangulos = {
    //    Triangulo(Punto(-20,22,23.9),Punto(20,22,23.9),Punto(-20,34,23.9),RGB(255,255,255),BRDF_phong(),true),
    //    Triangulo(Punto(20,34,23.9),Punto(20,22,23.9),Punto(-20,34,23.9),RGB(255,255,255),BRDF_phong(),true)
    };

    vector<Plano> _planos = {
        Plano(32,Vector(1,0,0),RGB(255,51,51),BRDF_phong(RGB(.85,.085,.085),RGB(),0)),
        Plano(32,Vector(-1,0,0),RGB(128,255,0),BRDF_phong(RGB(.085,.85,.085),RGB(),0)),
        Plano(24,Vector(0,0,-1),RGB(255,255,255),BRDF_phong(RGB(.85,.85,.85),RGB(),0),true),
        Plano(24,Vector(0,0,1),RGB(15,15,15),BRDF_phong(RGB(.85,.85,.85),RGB(),0)),
        Plano(50,Vector(0,-1,0),RGB(220,220,220),BRDF_phong(RGB(.85,.85,.85),RGB(),0)),
        Plano(5,Vector(0,1,0),RGB(220,220,220),BRDF_phong(RGB(.85,.85,.85),RGB(),0))
    };

    vector<Luz> _luz = {
    //        Luz(Punto(0,30,20),RGB(2000,2000,2000))
    };

    //Preparacion del trazador de rayos
    Camara camara = Camara(camara_left, camara_up, camara_forward, camara_pos,
        num_pixeles_ejex,num_pixeles_ejey,mt);
   //Aqui se puede rotar la camara y el plano
    BoundingVolumeHierarchy bvh = BoundingVolumeHierarchy();
    bvh.cargar_triangulos_ply(path_ply,RGB(),BRDF_phong(RGB(.41,.41,.41), RGB(),
                                                        0));
    bvh.cargar_triangulos_ply(path_ply,RGB(),BRDF_phong(RGB(.41,.41,.41), RGB(),
                                                        0));
    bvh.cargar_triangulos_ply(path_ply,RGB(),BRDF_phong(RGB(.41,.41,.41), RGB(),
                                                        0));
    bvh.cargar_triangulos_ply(path_ply,RGB(),BRDF_phong(RGB(.41,.41,.41), RGB(),
                                                        0));
    bvh.cargar_triangulos_ply(path_ply,RGB(),BRDF_phong(RGB(.41,.41,.41), RGB(),
                                                        0));
    bvh.cargar_triangulos_ply(path_ply,RGB(),BRDF_phong(RGB(.41,.41,.41), RGB(),
                                                        0));
    bvh.trasladar_figura(0,0,22,-24);
    bvh.trasladar_figura(1,15,21,-24);
    bvh.trasladar_figura(2,9,34,-24);
    bvh.trasladar_figura(3,-10,24,-24);
    bvh.trasladar_figura(4,-20,25,-24);
    bvh.trasladar_figura(5,-1,32,-24);
    Malla_geometrias malla = Malla_geometrias();
    malla.cargar_geometrias(_esferas,_planos,_triangulos, bvh);


    Path_tracer pth = Path_tracer(camara, malla,_luz,tmax, num_path_pixel,mt);
    pth.renderizar();
    pth.guardar_imagen(path);
    return 0;
}