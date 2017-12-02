//
// Isak Edo Vivancos - 682405
// Plano de proyección sobre el que se lanzan los rayos para formar la imagen,
//

#pragma once

class Plano_proyeccion {

private:

    vector<vector<RGB>> pantalla;

public:

    //Constructor
    Plano_proyeccion() = default;
    Plano_proyeccion(const __uint16_t& _num_pixeles_ejex,
                     const __uint16_t& _num_pixeles_ejey) {
        for(auto j = 0; j < _num_pixeles_ejey; j++) {
            vector<RGB> aux;
            for(auto i = 0; i < _num_pixeles_ejex; i++) {
                aux.push_back(RGB());
            }
            pantalla.push_back(aux);
        }
    }

    const RGB &getColor(const int& x, const int& y) const {
        return pantalla[y][x];
    }

    void setColor(const int& x, const int& y, const RGB& color) {
        pantalla[y][x] = color;
    }

};
