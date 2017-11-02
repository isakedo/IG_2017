//
// Isak Edo Vivancos - 682405
// Trazador de rayos
//

#pragma once

#include <fstream>
#include <iostream>

using namespace std;

class Ray_tracing {

private:

    std::string path="/home/isak/CLionProjects/IG_2017/output.ppm";

    Camara camara = Camara();
    Plano_proyeccion plano = Plano_proyeccion();
    Malla_geometrias escena = Malla_geometrias();

public:

    Ray_tracing(Camara _camara, Plano_proyeccion _plano,
                Malla_geometrias _escena) :
            camara(_camara), plano(_plano), escena(_escena){}

    void renderizar() {
        cout << "Renderizar" << endl;
    }

    //Cambiar a plano
    void guardar_imagen() {
        ofstream fs;
        fs.open(path);
        fs << "P3" << endl << "# " << path << endl;
        fs << num_pixeles_ejex << " " << num_pixeles_ejey << endl;
        fs << "255" << endl;
        plano.begin();
        do {
            do {
                fs << plano.getColor().getR() << " " << plano.getColor().getG()
                   << " " << plano.getColor().getB() << " ";
            } while (plano.siguiente_x());
            fs << endl;
        } while (plano.siguiente_y());

    }
};
