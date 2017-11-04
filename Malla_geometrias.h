//
// Isak Edo Vivancos - 682405
// Malla de geometria de la escena a dibujar. Se utilizan vectores estáticos
// para evitar punteros y memoria dinámica.
//

const __uint8_t num_esferas = 1;
const __uint8_t num_planos = 5;

#pragma once

class Malla_geometrias {

private:

    Esfera esferas[num_esferas];
    Plano planos[num_planos];

public:

    //Constructor
    Malla_geometrias() = default;

    void cargar_geometrias(const Esfera _esferas[], const Plano _planos[]) {
        for(auto i = 0; i < num_esferas; i++)
            esferas[i] = _esferas[i];
        for(auto i = 0; i < num_planos; i++)
            planos[i] = _planos[i];
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

        return color_proximo;
    }

};
