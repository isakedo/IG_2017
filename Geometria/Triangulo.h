//
// Isak Edo Vivancos - 682405
// Geometría de la esfera con un centro, punto de referencia y un vector axis
//

#pragma once

class Triangulo : public Geometria {

private:

    Punto v1 = Punto(), v2 = Punto(),v3 = Punto();

public:

    //Constructor
    Triangulo() = default;
    Triangulo (const Punto& _v1, const Punto& _v2, const Punto& _v3,
            const RGB& _color) : v1(_v1), v2(_v2), v3(_v3), Geometria(_color) {}

    //https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_
    // intersection_algorithm
    float interseccion(const Vector& dir, const Punto& origen) {

        const float error = 0.0000001;
        Vector lado1, lado2, h, s, q;
        float a,f,u,v;
        lado1 = v2 - v1;
        lado2 = v3 - v1;
        h = dir % lado2;
        a = lado1 * h;
        if (a > -error && a < error)
            return -1;
        f = 1/a;
        s = origen - v1;
        u = s * h * f;
        if (u < 0.0 || u > 1.0)
            return -1;
        q = s % lado1;
        v = dir * q * f;
        if (v < 0.0 || u + v > 1.0)
            return -1;
        float t = lado2 * q * f;
        if (t > 0)
        {
            return t;
        }
        else
            return -1;
    }


};
