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
    BoundingVolumeHierarchy bvh = BoundingVolumeHierarchy();
    Geometria *ultima_interseccion;

public:

    //Constructor
    Malla_geometrias() = default;

    void cargar_geometrias(vector<Esfera>& _esferas, vector<Plano> _planos,
            vector<Triangulo> _triangulos, const BoundingVolumeHierarchy& _bvh)
    {
        esferas = _esferas;
        planos = _planos;
        triangulos = _triangulos;
        bvh = _bvh;
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

        float t = bvh.interseccion(dir,origen,tmax);
        if(t > 0) {
            if (t < t_proximo) {
                ultima_interseccion = bvh.getUltimaInterseccion();
                t_proximo = t;
            }
        }

        return t_proximo;
    }

    Geometria* geometria_intersectada() {
        return ultima_interseccion;
    }

};
