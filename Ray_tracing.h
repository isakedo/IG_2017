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

    std::string path;
    float tmax;
    Camara camara = Camara();
    Plano_proyeccion plano = Plano_proyeccion();
    Malla_geometrias escena = Malla_geometrias();
    ofstream fs;

    //Guardar imagen
    void cabecera() {
        fs << "P3" << endl << "# " << path << endl;
        fs << num_pixeles_ejex << " " << num_pixeles_ejey << endl;
        fs << "255" << endl;
    }

    void pintar_pixel(const RGB &color) {
        fs << color.getR() << " " << color.getG() << " " << color.getB() << " ";
    }

public:

    Ray_tracing(const Camara& _camara, const Plano_proyeccion& _plano,
                const Malla_geometrias& _escena, const std::string& _path,
            const float& _tmax) : camara(_camara), plano(_plano), escena(_escena)
            , path(_path), tmax(_tmax){
        fs.open(path);
    }

    void renderizar() {
        cout << "Renderizar" << endl;
        cabecera();
        plano.begin();
        do {
            do {
                Punto pixel = plano.getPunto(); //Punto del plano
                Vector rayo = pixel - camara.getPosicion(); //Rayo
                rayo = rayo / rayo.mod();
                RGB color = escena.interseccion(rayo,camara.getPosicion(),tmax);
                pintar_pixel(color);
            } while (plano.siguiente_x());
            fs << endl;
        } while (plano.siguiente_y());
        fs.close();
    }

};
