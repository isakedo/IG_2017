//
// Isak Edo Vivancos - 682405
// Punto de luz
//

# pragma once
class Luz {

private:

    Punto posicion = Punto();
    RGB color = RGB();

public:

    Luz(Punto _posicion, RGB _color) : posicion(_posicion), color(_color) {}

    const Punto &getPosicion() const {
        return posicion;
    }

    const RGB &getIntensidad() const {
        return color;
    }
};

