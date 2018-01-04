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
            const RGB& _color, const BRDF_phong& _brdf, bool _emisor = false) :
            Geometria(_color,_brdf,_emisor) {
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
        float raiz1, raiz2;

        Vector L = origen - centro;
        float a = dir * dir; // Esto valdra 1 en el caso de la esfera
        float b = dir * L * 2;
        float c = L * L - getRadio() * getRadio();
        //Si no intersecta se devuelve -1
        if (!ecuacionCuadratica(a, b, c, raiz1, raiz2)) return -1;

        if (raiz1 < 0 && raiz2 < 0) return -1;
        else if (raiz1 < 0) return raiz2;
        else if (raiz2 < 0) return raiz1;

        return raiz1 < raiz2 ? raiz1 : raiz2;
    }

    Matriz_transformacion coordenadas_cos(const Punto& inter,
                                          const Vector& dir) {
        Vector tangente_u;
        Vector normal = inter - centro;
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
        Vector normal = inter - centro;
        normal = normal / normal.mod();
        return normal;
    }

    void escalar(float factor_x, float factor_y, float factor_z) {
        Matriz_transformacion escalar = Matriz_transformacion(
                Vector(factor_x,0,0),Vector(0,factor_y,0),Vector(0,0,factor_z),
                Punto(0,0,0));
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

    void rotar_x(float angulo) {}
    void rotar_y(float angulo) {}
    void rotar_z(float angulo) {}

};
