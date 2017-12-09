//
// Isak Edo Vivancos - 682405
// Clase básica de geometria con su color.
//

#pragma once

class Geometria {

private:

    RGB color = RGB();
    BRDF_phong brdf = BRDF_phong();
    bool emisor;

public:

    //Constructor
    Geometria() = default;
    explicit Geometria(const RGB& _color, BRDF_phong _brdf,
          bool _emisor = false) : color(_color), brdf(_brdf), emisor(_emisor){}

    const RGB &getColor() const {
        return color;
    }

    const BRDF_phong &getBRDF() const {
        return brdf;
    }

    const bool getEmisor() const {
        return emisor;
    }

    bool ecuacionCuadratica(const float &a, const float &b, const float &c,
                            float &raiz1, float &raiz2)
    {

        float discr = b * b - 4 * a * c;
        if (discr < 0) return false;
        else if (discr == 0) raiz1 = raiz2 = - 0.5f * b / a;
        else {
            raiz1 = -0.5f * (b + sqrtf(discr));
            raiz2 = -0.5f * (b - sqrtf(discr));
        }

        return true;
    }

    virtual float interseccion(const Vector& dir, const Punto& origen) = 0;
    virtual Matriz_transformacion coordenadas_cos(const Punto& inter) = 0;
    virtual Matriz_transformacion coordenadas_ref(const Punto& inter,
                                             const Vector& reflejo) = 0;
    virtual Vector getNormal(const Punto& inter) = 0;

    virtual void escalar(float factor_x, float factor_y, float factor_z) = 0;
    virtual void trasladar(float factor_x, float factor_y, float factor_z) = 0;
    virtual void rotar_x(float angulo) = 0;
    virtual void rotar_y(float angulo) = 0;
    virtual void rotar_z(float angulo) = 0;

};
