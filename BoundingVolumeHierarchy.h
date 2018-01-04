//
// Isak Edo Vivancos - 682405
// Bounding Volume Hierarchy
//


#pragma once

using namespace std;

class BoundingVolumeHierarchy {

private:

    int num_figuras = 0;
    vector<vector<Triangulo>> figuras;
    vector<Esfera> bounding;
    Geometria *ultima_interseccion;

public:

    BoundingVolumeHierarchy() = default;

    void cargar_triangulos_ply(const std::string& _path, const RGB& rgb,
                               const BRDF_phong& brdf) {

        ifstream fe;
        char trash[64];
        int num_vertices, num_triangulos;
        vector<Punto> vertices;
        vector<Triangulo> tmp;

        fe.open(_path);
        fe.getline(trash,64);
        fe.getline(trash,64);
        fe.getline(trash,64);
        sscanf(trash, "element vertex %d", &num_vertices);
        fe.getline(trash,64);
        fe.getline(trash,64);
        fe.getline(trash,64);
        fe.getline(trash,64);
        sscanf(trash, "element face %d", &num_triangulos);
        fe.getline(trash,64);
        fe.getline(trash,64);


        for(int it = 0; it < num_vertices; it++) {
            float x, y, z;
            fe >> x >> y >> z;
            fe.getline(trash,64);
            vertices.push_back(Punto(x,y,z));
        }

        for(int it = 0; it < num_triangulos; it++) {
            int _num, x, y, z;
            fe >> _num >> x >> y >> z;
            fe.getline(trash,64);
            tmp.push_back(Triangulo(vertices[x],vertices[y],vertices[z],
                               rgb,brdf));
        }

        figuras.push_back(tmp);
        num_figuras++;

        float max_distancia = 0;
        Punto max_v1 = Punto(), max_v2 = Punto();
        for(int i = 0; i < vertices.size(); i++) {
            for(int j = i; j < vertices.size(); j++ ) {
                float distancia = fabsf((vertices[i] - vertices[j]).mod());
                if(distancia > max_distancia) {
                    max_v1 = vertices[i]; max_v2 = vertices[j];
                    max_distancia = distancia;
                }
            }
        }

        Punto centro = max_v1 + ((max_v2 - max_v1) / 2);
        bounding.push_back(Esfera(centro,max_v1,Vector(0,0,max_distancia),RGB(),
                                  BRDF_phong()));

        fe.close();
    }

    //Conversión de figuras completas hechas con triangulos
    void escalar_figura(int num, float factor_x, float factor_y, float factor_z)
    {
        for(auto i = 0; i < figuras[num].size(); i++) {
            figuras[num][i].escalar(factor_x,factor_y,factor_z);
        }
        bounding[num].escalar(factor_x,factor_y,factor_z);
    }

    void trasladar_figura(int num, float factor_x, float factor_y,
                          float factor_z) {
        for(auto i = 0; i < figuras[num].size(); i++) {
            figuras[num][i].trasladar(factor_x,factor_y,factor_z);
        }
        bounding[num].trasladar(factor_x,factor_y,factor_z);
    }

    void rotar_x_figura(int num, float angulo) {
        for(auto i = 0; i < figuras[num].size(); i++) {
            figuras[num][i].rotar_x(angulo);
        }
    }

    void rotar_y_figura(int num, float angulo) {
        for(auto i = 0; i < figuras[num].size(); i++) {
            figuras[num][i].rotar_y(angulo);
        }
    }

    void rotar_z_figura(int num, float angulo) {
        for(auto i = 0; i < figuras[num].size(); i++) {
            figuras[num][i].rotar_z(angulo);
        }
    }

    float interseccion(const Vector& dir, const Punto& origen, const float tmax)
    {
        float t_proximo = tmax;

        for(auto i = 0; i < figuras.size(); i++) {
            float t = bounding[i].interseccion(dir, origen);
            if(t > 0) {
                for (auto j = 0; j < figuras[i].size(); j++) {
                    float t = figuras[i][j].interseccion(dir, origen);
                    if (t > 0) {
                        if (t < t_proximo) {
                            ultima_interseccion = &figuras[i][j];
                            t_proximo = t;
                        }
                    }
                }
            }
        }

        return t_proximo;
    }

    Geometria* getUltimaInterseccion() {
        return ultima_interseccion;
    }

};

