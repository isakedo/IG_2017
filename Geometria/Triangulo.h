//
// Isak Edo Vivancos - 682405
// Geometría del triangulo con tres vertices
//

#pragma once

class Triangulo : public Geometria {

private:

    Punto v1 = Punto(), v2 = Punto(),v3 = Punto();

public:

    //Constructor
    Triangulo() = default;
    Triangulo (const Punto& _v1, const Punto& _v2, const Punto& _v3,
            const RGB& _color, const BRDF_phong& _brdf, bool _emisor = false) :
            v1(_v1), v2(_v2), v3(_v3), Geometria(_color,_brdf,_emisor) {}

    float interseccion(const Vector& dir, const Punto& origen) {

        const float error = 0.0000001;
        Vector lado1, lado2, h, s, q;
        float a,f,u,v;
        lado1 = v2 - v1;
        lado2 = v3 - v1;
        h = dir % lado2;
        //if(h*dir < 0) h = h * 1;
        a = lado1 * h;
        //Comprueba si el rayo es paralelo
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

    Matriz_transformacion coordenadas_cos(const Punto& inter,
                                          const Vector& dir) {
        Vector lado1, lado2, normal;
        lado1 = v2 - v1;
        lado2 = v3 - v1;
        normal = dir % lado2;

        Vector tangente_u;
        normal = normal / normal.mod();
        if(normal.getX() < normal.getY() && normal.getX() < normal.getZ())
            tangente_u = Vector(0,-normal.getZ(),normal.getY());
        else if (normal.getY() < normal.getX() && normal.getY() < normal.getZ())
            tangente_u = Vector(-normal.getZ(),0,normal.getX());
        else
            tangente_u = Vector(-normal.getY(),normal.getX(),0);
        tangente_u = tangente_u / tangente_u.mod();
        Vector tangente_v = normal % tangente_u;
        tangente_v = tangente_v / tangente_v.mod();
        Matriz_transformacion resultado = Matriz_transformacion (
                tangente_u,tangente_v,normal,inter);
        return resultado;
    }

    Matriz_transformacion coordenadas_ref(const Punto& inter,
                                   const Vector& reflejo, const Vector& dir) {
        Vector tangente_u;
        if(reflejo.getX() < reflejo.getY() && reflejo.getX() < reflejo.getZ())
            tangente_u = Vector(0,-reflejo.getZ(),reflejo.getY());
        else if (reflejo.getY() < reflejo.getX() && reflejo.getY() < reflejo.getZ())
            tangente_u = Vector(-reflejo.getZ(),0,reflejo.getX());
        else
            tangente_u = Vector(-reflejo.getY(),reflejo.getX(),0);
        tangente_u = tangente_u / tangente_u.mod();
        Vector tangente_v = reflejo % tangente_u;
        tangente_v = tangente_v / tangente_v.mod();
        Matriz_transformacion resultado = Matriz_transformacion (
                tangente_u,tangente_v,reflejo,inter);
        return resultado;
    }

    Vector getNormal(const Punto& inter, const Vector& dir) {
        Vector lado1, lado2, normal;
        lado1 = v2 - v1;
        lado2 = v3 - v1;
        return dir % lado2;
    }

    void escalar(float factor_x, float factor_y, float factor_z) {
        Matriz_transformacion escalar = Matriz_transformacion(
                Vector(factor_x,0,0),Vector(0,factor_y,0),Vector(0,0,factor_z),
                Punto(0,0,0));
        v1 = escalar * v1;
        v2 = escalar * v2;
        v3 = escalar * v3;
    }

    void trasladar(float factor_x, float factor_y, float factor_z) {
        Matriz_transformacion trasladar = Matriz_transformacion(
                Vector(1,0,0),Vector(0,1,0),Vector(0,0,1),
                Punto(factor_x,factor_y,factor_z));
        v1 = trasladar * v1;
        v2 = trasladar * v2;
        v3 = trasladar * v3;
    }

    void rotar_x(float angulo) {
        Matriz_transformacion rotar = Matriz_transformacion(
                Vector(1,0,0),Vector(0,cosf(angulo),sinf(angulo)),
                Vector(0,-sinf(angulo),cosf(angulo)),Punto(0,0,0));
        v1 = rotar * v1;
        v2 = rotar * v2;
        v3 = rotar * v3;
    }

    void rotar_y(float angulo) {
        Matriz_transformacion rotar = Matriz_transformacion(
                Vector(cosf(angulo),0,-sinf(angulo)),Vector(0,1,0),
                Vector(sinf(angulo),0,cosf(angulo)),Punto(0,0,0));
        v1 = rotar * v1;
        v2 = rotar * v2;
        v3 = rotar * v3;
    }

    void rotar_z(float angulo) {
        Matriz_transformacion rotar = Matriz_transformacion(
                Vector(cosf(angulo),sinf(angulo),0),
                Vector(-sinf(angulo),cosf(angulo),0),Vector(0,0,1),
                Punto(0,0,0));
        v1 = rotar * v1;
        v2 = rotar * v2;
        v3 = rotar * v3;
    }
};
