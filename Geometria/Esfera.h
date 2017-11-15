//
// Isak Edo Vivancos - 682405
// Geometría de la esfera con un centro, punto de referencia y un vector axis
//

#pragma once

class Esfera : public Geometria {

private:
    Punto centro = Punto(), referencia = Punto(); //Globales
    Vector axis = Vector();

public:

    //Constructor
    Esfera() = default;
    Esfera (const Punto& _centro, const Punto& _referencia, const Vector& _axis,
            const RGB& _color) : Geometria(_color) {
        float radio_rc = (_referencia - _centro).mod();
        float radio_ax = _axis.mod() / 2;
        if((radio_ax - 0.000001) < radio_rc && (radio_ax + 0.000001) > radio_rc)
        { centro = _centro; referencia  = _referencia; axis = _axis; }
    }

    const Punto &getCentro() const {
        return centro;
    }

    const Punto &getReferencia() const {
        return referencia;
    }

    const Vector &getAxis() const {
        return axis;
    }

    float getRadio() const {
        return axis.mod() / 2;
    }

    float interseccion(const Vector& dir, const Punto& origen) {
        float t0, t1;

        Vector L = origen - centro;
        float a = dir * dir; // Esto valdra 1 en el caso de la esfera
        float b = dir * L * 2;
        float c = L * L - getRadio() * getRadio();
        if (!ecuacionCuadratica(a, b, c, t0, t1)) return -1;

        if (t0 > t1) {
            float aux = t0;
            t0 = t1;
            t1 = aux;
        }

        if (t0 < 0) {
            t0 = t1;
            if (t0 < 0) return -1;
        }

        return t0;
    }

    void escalar(float factor_x, float factor_y, float factor_z) {
        Matriz_transformacion escalar = Matriz_transformacion(
                Vector(factor_x,0,0),Vector(0,factor_y,0),Vector(0,0,factor_z),
                Punto(0,0,0));
        centro = escalar * centro;
        referencia = escalar * referencia;
        axis = escalar * axis;
    }

    void trasladar(float factor_x, float factor_y, float factor_z) {
        Matriz_transformacion trasladar = Matriz_transformacion(
                Vector(1,0,0),Vector(0,1,0),Vector(0,0,1),
                Punto(factor_x,factor_y,factor_z));
        centro = trasladar * centro;
        referencia = trasladar * referencia;
        axis = trasladar * axis;
    }

    void rotar_x(float angulo) {
        Matriz_transformacion rotar = Matriz_transformacion(
                Vector(1,0,0),Vector(0,cosf(angulo),sinf(angulo)),
                Vector(0,-sinf(angulo),cosf(angulo)),Punto(0,0,0));
        centro = rotar * centro;
        referencia = rotar * referencia;
        axis = rotar * axis;
    }

    void rotar_y(float angulo) {
        Matriz_transformacion rotar = Matriz_transformacion(
                Vector(cosf(angulo),0,-sinf(angulo)),Vector(0,1,0),
                Vector(sinf(angulo),0,cosf(angulo)),Punto(0,0,0));
        centro = rotar * centro;
        referencia = rotar * referencia;
        axis = rotar * axis;
    }

    void rotar_z(float angulo) {
        Matriz_transformacion rotar = Matriz_transformacion(
                Vector(cosf(angulo),sinf(angulo),0),
                Vector(-sinf(angulo),cosf(angulo),0),Vector(0,0,1),
                Punto(0,0,0));
        centro = rotar * centro;
        referencia = rotar * referencia;
        axis = rotar * axis;
    }

};
