//
// Isak Edo Vivancos
// Tupla de colores RGB con color rojo, verde y azul, entre 0 y 255
//

#pragma once

class RGB : Tupla {

public:

    //Constructor, por defecto
    RGB() : Tupla(0,0,0) {}
    RGB(float rojo, float verde, float azul) : Tupla(rojo,verde,azul) {}

    //Getters
    float getR() const {
        return x;
    }

    float getG() const {
        return y;
    }

    float getB() const {
        return z;
    }

    RGB operator+ (const RGB& rgb) const {
        RGB resultado = RGB (this->x + rgb.x, this->y + rgb.y,
                                   this->z + rgb.z);
        return resultado;
    }

    RGB operator* (const RGB& rgb) const {
        RGB resultado = RGB (this->x * rgb.x, this->y * rgb.y,
                             this->z * rgb.z);
        return resultado;
    }

    RGB operator* (const float& val) const {
        RGB resultado = RGB (this->x * val, this->y * val,
                             this->z * val);
        return resultado;
    }

    RGB operator/ (const float& val) const {
        RGB resultado = RGB (this->x / val, this->y / val,
                             this->z / val);
        return resultado;
    }

    //Setters
    void setR(float x) {
        Tupla::x = x;
    }

    void setG(float y) {
        Tupla::y = y;
    }

    void setB(float z) {
        Tupla::z = z;
    }

};