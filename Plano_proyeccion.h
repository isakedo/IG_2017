//
// Isak Edo Vivancos - 682405
// Plano de proyección sobre el que se lanzan los rayos para formar la imagen,
// se calcula el tamaño y posición con la camara.
//

#pragma once

const __uint16_t  num_pixeles_ejex = 350;
const __uint16_t  num_pixeles_ejey = 300;

class Plano_proyeccion {

private:
    //Matriz de pixeles
    //Probar con la clase array
    Pixel plano[num_pixeles_ejey][num_pixeles_ejex];
    __uint16_t it_y = 0, it_x = 0;

public:

    //Constructor
    Plano_proyeccion() = default;
    Plano_proyeccion(Camara camara) {
        Punto it = camara.getPosicion() + camara.getForward() +
                camara.getUp() + camara.getLeft();

        float inicio_x = it.getX();
        for (auto y = 0; y < num_pixeles_ejey; y++) {
            for (auto x = 0; x < num_pixeles_ejex; x++) {
                plano[y][x] = Pixel(it);
                it = Punto(it.getX() + 1, it.getY(), it.getZ());
            }
            it = Punto(inicio_x, it.getY(), it.getZ() - 1);
        }
    }

    //Iterador
    void begin() { it_y = 0; it_x = 0; }
    const Pixel &getPixel() const { return plano[it_y][it_x]; }
    const RGB &getColor() const { return plano[it_y][it_x].getColor(); }
    void setColor(const RGB &color) { plano[it_y][it_x].setColor(color); }
    bool siguiente_x() {
        it_x++;
        return it_x == num_pixeles_ejex ? false : true;
    }
    bool siguiente_y() {
        it_x = 0;
        it_y++;
        return it_y == num_pixeles_ejey ? false : true;
    }

};
