//
// Isak Edo Vivancos - 682405
// Trazador de rayos
//

#pragma once

#include <ctime>

using namespace std;

class Ray_tracer {

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

    void progreso(int porcentaje,int longitud, int time){
        printf("\r[");
        for(int i=0;i<longitud;i++){
            if(porcentaje * longitud / 100 < i)
                putchar('_');
            else
                putchar('#');
        }
        printf("] %d%% Completado %02d:%02d:%02d",porcentaje,time/3600,
               time % 3600 / 60, time % 60);
        fflush(stdout);
    }

public:

    Ray_tracer(const Camara& _camara, const Plano_proyeccion& _plano,
               const Malla_geometrias& _escena, const std::string& _path,
               const float& _tmax) : camara(_camara), plano(_plano), escena(_escena)
            , path(_path), tmax(_tmax){
        fs.open(path);
    }

    void renderizar() {

        float contador = 0;
        clock_t inicio, timestamp;
        inicio = clock();

        cout << "Renderizando..." << endl << endl;
        cabecera();
        plano.begin();
        do {
            do {
                //Ray tracing
                Punto pixel = plano.getPunto(); //Punto del plano
                Vector rayo = pixel - camara.getPosicion(); //Rayo
                rayo = rayo / rayo.mod();
                RGB color = escena.interseccion(rayo,camara.getPosicion(),tmax);
                pintar_pixel(color);

                //Progreso
                contador++;
                timestamp = clock();
                double time = (double(timestamp-inicio)/CLOCKS_PER_SEC);
                progreso((int)(contador * 100) /
                         (num_pixeles_ejey * num_pixeles_ejex),50,(int)time);

            } while (plano.siguiente_x());
            fs << endl;
        } while (plano.siguiente_y());
        fs.close();
    }

};
