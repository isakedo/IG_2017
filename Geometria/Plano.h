//
// Isak Edo Vivancos - 682405
// Geometría de la esfera con un centro, punto de referencia y un vector axis
//

#pragma once

class Plano : public Geometria {

private:
    float distancia;
    Vector normal = Vector();

public:

    //Constructor
    Plano() = default;
    Plano (const float& _distancia, const Vector& _normal, const RGB& _color) :
            distancia(_distancia), normal(_normal / _normal.mod()),
            Geometria(_color) {}

    const float &getDistancia() const {
        return distancia;
    }

    const Vector &getNormal() const {
        return normal;
    }

    float interseccion(const Vector& dir, const Punto& origen) {
        return -(origen * normal + distancia) / (dir * normal);
    }

};
