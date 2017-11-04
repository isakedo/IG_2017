//
// Isak Edo Vivancos - 682405
// Plano de proyección sobre el que se lanzan los rayos para formar la imagen,
// se calcula el tamaño y posición con la camara.
//

#pragma once

const __uint16_t  num_pixeles_ejex = 640;
const __uint16_t  num_pixeles_ejey = 480;

class Plano_proyeccion {

private:
    __uint16_t it_y = 0, it_x = 0;
    Punto it = Punto();
    float inicio_x = -1.0f;

public:

    //Constructor
    Plano_proyeccion() = default;
    Plano_proyeccion(const Camara& camara) {
        it = camara.getPosicion() + camara.getForward() +
                camara.getUp() + camara.getLeft();
        inicio_x = it.getX();
    }

    //Iterador
    void begin() { it_y = 0; it_x = 0; }
    const Punto &getPunto() const { return it; }
    bool siguiente_x() {
        it_x++;
        it = Punto(it.getX() + 1, it.getY(), it.getZ());
        return it_x == num_pixeles_ejex ? false : true;
    }
    bool siguiente_y() {
        it_x = 0;
        it_y++;
        it = Punto(inicio_x, it.getY(), it.getZ() - 1);
        return it_y == num_pixeles_ejey ? false : true;
    }

};
