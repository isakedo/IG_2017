//
// Isak Edo Vivancos - 682405
// Plano de proyección sobre el que se lanzan los rayos para formar la imagen,
//

#pragma once

const __uint16_t  num_pixeles_ejex = 640;
const __uint16_t  num_pixeles_ejey = 480;

class Plano_proyeccion {

private:

    RGB pantalla[num_pixeles_ejex][num_pixeles_ejey];

public:

    //Constructor
    Plano_proyeccion() = default;

    const RGB &getColor(const int& x, const int& y) const {
        return pantalla[x][y];
    }

    void setColor(const int& x, const int& y, const RGB& color) {
        pantalla[x][y] = color;
    }

};
