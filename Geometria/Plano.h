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
    Plano (const float& _distancia, const Vector& _normal, const RGB& _color,
        const BRDF_phong& _brdf, bool _emisor = false) : distancia(_distancia),
        normal(_normal / _normal.mod()), Geometria(_color,_brdf,_emisor) {}

    float interseccion(const Vector& dir, const Punto& origen) {
        return -(origen * normal + distancia) / (dir * normal);
    }

    Matriz_transformacion coordenadas_cos(const Punto& inter) {
        Vector aux = fabs(normal.getX()) > 0.1 ? Vector(0,1,0) : Vector(1,0,0);
        Vector tangente_u = normal % aux;
        tangente_u = tangente_u / tangente_u.mod();
        Vector tangente_v = normal % tangente_u;
        tangente_v = tangente_v / tangente_v.mod();
        Matriz_transformacion resultado = Matriz_transformacion (
          tangente_u,tangente_v,normal,inter);
        return resultado;
    }

    Matriz_transformacion coordenadas_ref(const Punto& inter,
                                  const Vector& rayo, const Vector& reflejo) {}

    Vector getNormal(const Punto& inter) { return normal; }
    void escalar(float factor_x, float factor_y, float factor_z) {}
    void trasladar(float factor_x, float factor_y, float factor_z) {}
    void rotar_x(float angulo) {}
    void rotar_y(float angulo) {}
    void rotar_z(float angulo) {}

};
