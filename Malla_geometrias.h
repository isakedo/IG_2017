//
// Isak Edo Vivancos - 682405
// Malla de geometria de la escena a dibujar. Se utilizan vectores estáticos
// para evitar punteros y memoria dinámica.
//

const __uint8_t num_esferas = 0;
const __uint8_t num_planos = 0;

#pragma once

using namespace std;

class Malla_geometrias {

private:

    int num_triangulos;

    Esfera esferas[num_esferas];
    Plano planos[num_planos];
    vector<Triangulo> triangulos;

public:

    //Constructor
    Malla_geometrias() = default;

    void cargar_geometrias(const Esfera _esferas[], const Plano _planos[]) {
        for(auto i = 0; i < num_esferas; i++)
            esferas[i] = _esferas[i];
        for(auto i = 0; i < num_planos; i++)
            planos[i] = _planos[i];
    }

    void cargar_triangulos_ply(const std::string& _path) {

        ifstream fe;
        char trash[64];
        int num_vertices;
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
                                         RGB(163,228,215)));
        }

        fe.close();
    }

    RGB interseccion(const Vector& dir, const Punto& origen, const float tmax){
        float t_proximo = tmax;
        RGB color_proximo = RGB();

        for(auto i = 0; i < num_esferas; i++) {
            float t = esferas[i].interseccion(dir,origen);
            if(t > 0) {
                if (t < t_proximo) {
                    color_proximo = esferas[i].getColor();
                    t_proximo = t;
                }
            }
        }

        for(auto i = 0; i < num_planos; i++) {
            float t = planos[i].interseccion(dir,origen);
            if(t > 0) {
                if (t < t_proximo) {
                    color_proximo = planos[i].getColor();
                    t_proximo = t;
                }
            }
        }

        for(auto i = 0; i < num_triangulos; i++) {
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

};
