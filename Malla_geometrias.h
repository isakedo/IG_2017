//
// Isak Edo Vivancos - 682405
// Malla de geometria de la escena a dibujar.
//

#pragma once

using namespace std;

class Malla_geometrias {

private:

    vector<Esfera> esferas;
    vector<Plano> planos;
    vector<Triangulo> triangulos;
    Geometria *ultima_interseccion;

public:

    //Constructor
    Malla_geometrias() = default;

    void cargar_geometrias(vector<Esfera>& _esferas, vector<Plano> _planos,
            vector<Triangulo> _triangulos) {
        esferas = _esferas;
        planos = _planos;
        triangulos = _triangulos;
    }

    void cargar_triangulos_ply(const std::string& _path) {

        ifstream fe;
        char trash[64];
        int num_vertices, num_triangulos;
        vector<Punto> vertices;

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
            triangulos.push_back(Triangulo(vertices[x],vertices[y],vertices[z],
                                    RGB(163,228,215),BRDF_phong(RGB(),RGB(),0.3)));
        }

        fe.close();
    }

    RGB inter_rayo(const Vector& dir, const Punto& origen, const float tmax){
        float t_proximo = tmax;
        RGB color_proximo = RGB();

        for(auto i = 0; i < esferas.size(); i++) {
            float t = esferas[i].interseccion(dir,origen);
            if(t > 0) {
                if (t < t_proximo) {
                    color_proximo = esferas[i].getColor();
                    t_proximo = t;
                }
            }
        }

        for(auto i = 0; i < planos.size(); i++) {
            float t = planos[i].interseccion(dir,origen);
            if(t > 0) {
                if (t < t_proximo) {
                    color_proximo = planos[i].getColor();
                    t_proximo = t;
                }
            }
        }

        for(auto i = 0; i < triangulos.size(); i++) {
            float t = triangulos[i].interseccion(dir,origen);
            if(t > 0) {
                if (t < t_proximo) {
                    color_proximo = triangulos[i].getColor();
                    t_proximo = t;
                }
            }
        }

        return color_proximo;
    }

    float inter_path(const Vector& dir, const Punto& origen, const float tmax){
        float t_proximo = tmax;

        for(auto i = 0; i < esferas.size(); i++) {
            float t = esferas[i].interseccion(dir,origen);
            if(t > 0) {
                if (t < t_proximo) {
                    ultima_interseccion = &esferas[i];
                    t_proximo = t;
                }
            }
        }

        for(auto i = 0; i < planos.size(); i++) {
            float t = planos[i].interseccion(dir,origen);
            if(t > 0) {
                if (t < t_proximo) {
                    t_proximo = t;
                    ultima_interseccion = &planos[i];
                }
            }
        }

        for(auto i = 0; i < triangulos.size(); i++) {
            float t = triangulos[i].interseccion(dir,origen);
            if(t > 0) {
                if (t < t_proximo) {
                    ultima_interseccion = &triangulos[i];
                    t_proximo = t;
                }
            }
        }

        return t_proximo;
    }

    Geometria* geometria_intersectada() {
        return ultima_interseccion;
    }

    //Conversión de figuras completas hechas con triangulos
    void escalar_figura(float factor_x, float factor_y, float factor_z) {
        for(auto i = 0; i < triangulos.size(); i++) {
            triangulos[i].escalar(factor_x,factor_y,factor_z);
        }
    }

    void trasladar_figura(float factor_x, float factor_y, float factor_z) {
        for(auto i = 0; i < triangulos.size(); i++) {
            triangulos[i].trasladar(factor_x,factor_y,factor_z);
        }
    }

    void rotar_x_figura(float angulo) {
        for(auto i = 0; i < triangulos.size(); i++) {
            triangulos[i].rotar_x(angulo);
        }
    }

    void rotar_y_figura(float angulo) {
        for(auto i = 0; i < triangulos.size(); i++) {
            triangulos[i].rotar_y(angulo);
        }
    }

    void rotar_z_figura(float angulo) {
        for(auto i = 0; i < triangulos.size(); i++) {
            triangulos[i].rotar_z(angulo);
        }
    }

};
