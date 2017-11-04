//
// Isak Edo Vivancos - 682405
// Camara pinhole para capturar la imagen
//

#pragma once

class Camara {

private:
    Vector up = Vector(), left = Vector(), forward = Vector();
    Punto posicion = Punto();

public:

    //Constructor
    Camara() = default;
    Camara(const Vector& _left, const Vector& _up, const Vector& _forward,
           const Punto& _posicion) :
            left(_left), up(_up), forward(_forward), posicion(_posicion) {}

    const Vector &getUp() const {
        return up;
    }

    const Vector &getLeft() const {
        return left;
    }

    const Vector &getForward() const {
        return forward;
    }

    const Punto &getPosicion() const {
        return posicion;
    }

    //Faltará rotar la camara

};
