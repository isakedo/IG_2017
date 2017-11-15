//
// Isak Edo Vivancos - 682405
// Geometría del plano con una distancia y una normal
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

    float interseccion(const Vector& dir, const Punto& origen) {
        return -(origen * normal + distancia) / (dir * normal);
    }

    void escalar(float factor_x, float factor_y, float factor_z) {}
    void trasladar(float factor_x, float factor_y, float factor_z) {}
    void rotar_x(float angulo) {}
    void rotar_y(float angulo) {}
    void rotar_z(float angulo) {}

};
