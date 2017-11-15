//
// Isak Edo Vivancos - 682405
// Trazador de rayos
//

#pragma once

using namespace std;

class Ray_tracer {

private:

    float tmax;
    Camara camara = Camara();
    Malla_geometrias escena = Malla_geometrias();

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

    Ray_tracer(const Camara& _camara, const Malla_geometrias& _escena,
               const float& _tmax) : camara(_camara), escena(_escena),
                                     tmax(_tmax){}

    void renderizar() {

        float contador = 0;
        struct timespec start, finish;
        clock_gettime(CLOCK_MONOTONIC, &start);

        cout << "Renderizando..." << endl << endl;
        for(auto j = 0; j < num_pixeles_ejey; j++) {
            #pragma omp parallel for num_threads(4) schedule(dynamic)
            for(auto i = 0; i < num_pixeles_ejex; i++) {
                //Ray tracing
                Vector rayo = camara.getRayo(i,j);
                rayo = rayo / rayo.mod();
                RGB color = escena.interseccion(rayo,camara.getPosicion(),tmax);
                camara.setColor(i,j,color);
            }

            //Progreso
            contador += num_pixeles_ejex;
            clock_gettime(CLOCK_MONOTONIC, &finish);
            double time = (finish.tv_sec - start.tv_sec);
            progreso((int)(contador * 100) /
                     (num_pixeles_ejey * num_pixeles_ejex),50,(int)time);

        }
    }

    void guardar_imagen(const std::string& path) {

        ofstream fs(path);
        fs << "P3" << endl << "# " << path << endl;
        fs << num_pixeles_ejex << " " << num_pixeles_ejey << endl;
        fs << "255" << endl;

        for(auto j = 0; j < num_pixeles_ejey; j++) {
            for (auto i = 0; i < num_pixeles_ejex; i++) {
                RGB color = camara.getColor(i, j);
                fs << color.getR() << " " << color.getG() << " "
                   << color.getB() << " ";
            }
            fs << endl;
        }

        fs.close();
    }

};
