//
// Isak Edo Vivancos - 682405
// Malla de geometria de la escena a dibujar. Se utilizan vectores estáticos
// para evitar punteros y memoria dinámica.
//

const __uint8_t num_esferas = 1;

#pragma once

class Malla_geometrias {

private:

    Esfera esferas[num_esferas];

public:

    //Constructor
    Malla_geometrias() = default;

    void cargar_geometrias(const Esfera _esferas[]) {
        for(auto i = 0; i < num_esferas; i++)
            esferas[i] = _esferas[i];
    }

};
