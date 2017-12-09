//
// Isak Edo Vivancos - 682405
// Path tracer
//

#pragma once

using namespace std;

class Path_tracer {

private:

    __uint16_t num_pixeles_ejex, num_pixeles_ejey, num_path;
    float tmax;
    Camara camara = Camara();
    Malla_geometrias escena = Malla_geometrias();
    std::mt19937 mt;
    std::uniform_real_distribution<float> dist;

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

    RGB lanzar_rayo(const Vector& dir, const Punto& origen, const float tmax) {

        float t = escena.inter_path(dir,origen,tmax);
        Punto inter = origen + dir * t;

        //no intersecta con nada
        if (t < 0 || t >= tmax) return RGB();

        //Si es emisor
        Geometria* interseccion = escena.geometria_intersectada();
        if(interseccion->getEmisor())
            return interseccion->getColor();

        //Generar número aleatorio para saber si es difusa o especular
        float randnum = dist(mt);
        float randnum2 = dist(mt);
        float pKd = interseccion->getBRDF().getProb_Kd();
        float pKs = interseccion->getBRDF().getProb_Ks();

        //Ruleta rusa
        //Si se comporta como difuso
        if(randnum >= 0 && randnum < pKd) {
            BRDF_phong brdf = interseccion->getBRDF();
            float r2 = sqrtf(randnum2);
            float acimut = brdf.getAcimut_Dif(randnum);
            Vector rebote = Vector(r2 * cosf(acimut),
              r2 * sinf(acimut), sqrtf(1-randnum2));
            Matriz_transformacion base_geometria = interseccion->coordenadas_cos
                    (inter);
            rebote = base_geometria * rebote;
            rebote = rebote / rebote.mod();
            RGB color_rebote = lanzar_rayo(rebote,inter,tmax);
            float factor = brdf.getFactor_Dif();
            RGB resultado = RGB(color_rebote.getR() * factor *
                brdf.getKd().getR(), color_rebote.getG() * factor *
                brdf.getKd().getG(), color_rebote.getB() * factor *
                brdf.getKd().getB());
            return resultado;
        }
        //Si se comporta como especular
        else if(randnum >= pKd && randnum < (pKd + pKs)) {
            BRDF_phong brdf = interseccion->getBRDF();
            Vector norm = interseccion->getNormal(inter);
            Vector inv_dir = dir * -1;
            //Comprobar si la normal esta dentro o fuera
            Vector reflejo = inv_dir - (norm * (inv_dir * norm) * 2);
            if((norm * reflejo)<0)
                reflejo = reflejo * -1;
            reflejo = reflejo / reflejo.mod();
            float inclinacion = brdf.getInclinacion_Esp(randnum);
            float acimut = brdf.getAcimut_Esp(randnum2);
            Vector rebote = Vector(sinf(inclinacion) * cosf(acimut),
                                   cosf(inclinacion) * sinf(acimut),
                                   cosf(inclinacion));
            Matriz_transformacion base_geometria = interseccion->coordenadas_ref
                    (inter,reflejo);

            rebote = base_geometria * rebote;
            rebote = rebote / rebote.mod();

            if((reflejo*rebote)<0)
                rebote = rebote * -1;

            RGB color_rebote = lanzar_rayo(rebote,inter,tmax);

            float factor = brdf.getFactor_Ref(reflejo, norm, rebote);
            RGB resultado = RGB(color_rebote.getR() * factor *
                brdf.getKs().getR(), color_rebote.getG() * factor *
                brdf.getKs().getG(), color_rebote.getB() * factor *
                brdf.getKs().getB());
            return resultado;
        }
        //Si se absorbe
        else return RGB(0,0,0); //No hace nada

    }

    int clamp(float color){
        float resultado;
        if(color<0) resultado=0;
        else
            if(color>1) resultado = 1;
            else resultado = color;
        return int(pow(resultado,1/2.2)*255+.5);
    }

public:

    Path_tracer(const Camara& _camara, const Malla_geometrias& _escena,
               const float& _tmax, const __uint16_t & _num_path,
                std::mt19937 _mt) : camara(_camara), escena(_escena),
                tmax(_tmax), num_path(_num_path), mt(_mt) {
        num_pixeles_ejex = camara.getNum_pixeles_ejex();
        num_pixeles_ejey = camara.getNum_pixeles_ejey();
        dist = std::uniform_real_distribution<float>(0, 1.0f);
    }

    void renderizar() {

        float contador = 0;
        struct timespec start, finish;
        clock_gettime(CLOCK_MONOTONIC, &start);

        cout << "Renderizando..." << endl << endl;
        for(auto j = 0; j < num_pixeles_ejey; j++) {

            vector<RGB> colores_path;
            RGB color = RGB();
            //#pragma omp parallel for num_threads(4) schedule(dynamic) private(colores_path,color)
            for(auto i = 0; i < num_pixeles_ejex; i++) {

                colores_path = vector<RGB>();
                for (auto k = 0; k < num_path; k++) {
                    //Path tracing
                    Vector rayo = camara.getRayo_random(i, j);
                    rayo = rayo / rayo.mod();
                    RGB color_pixel = lanzar_rayo(rayo,camara.getPosicion(),
                                                                          tmax);
                    colores_path.push_back(color_pixel);
                }

                color = RGB();
                for (RGB color_i : colores_path) {
                    color = RGB(color.getR()+color_i.getR(),
                    color.getG()+color_i.getG(),color.getB()+color_i.getB());
                }
                color = RGB(color.getR()/num_path,color.getG()/num_path,
                            color.getB()/num_path);

                camara.setColor(i, j, color);


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
                fs << clamp(color.getR()/(float)255) << " "
                   << clamp(color.getG()/(float)255) << " "
                   << clamp(color.getB()/(float)255) << " ";
            }
            fs << endl;
        }

        fs.close();
    }

};
