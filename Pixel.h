//
// Isak Edo Vivancos - 682405
// Pixel de el plano de proyección con su posición en coordenadas globales y
// el color correspondiente
//

#pragma once

class Pixel {

private:
    RGB color = RGB();
    Punto posicion = Punto();

public:

    //Constructor
    Pixel() = default;
    explicit Pixel(Punto _posicion) : posicion(_posicion) {}

    const RGB &getColor() const {
        return color;
    }

    const Punto &getPosicion() const {
        return posicion;
    }

    void setColor(const RGB &color) {
        Pixel::color = color;
    }

};