//
// Isak Edo Vivancos - 682405
// Clase básica de geometria con su color.
//

#pragma once

class Geometria {

private:
    RGB color = RGB();

public:

    //Constructor
    Geometria() = default;
    explicit Geometria(const RGB& _color) : color(_color) {}

    const RGB &getColor() const {
        return color;
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

    virtual void escalar(float factor_x, float factor_y, float factor_z) = 0;
    virtual void trasladar(float factor_x, float factor_y, float factor_z) = 0;
    virtual void rotar_x(float angulo) = 0;
    virtual void rotar_y(float angulo) = 0;
    virtual void rotar_z(float angulo) = 0;

};
