//
// Isak Edo Vivancos - 682405
// Interfaz para punto geométrico con sus operaciones necesarios como sobrecarga
// de sus operadores.
//

#pragma once

class Punto : public Tupla{

private:
    float bit;

public:

    //Constructor
    Punto() = default;
    Punto (float _x, float _y, float _z) : Tupla(_x,_y,_z), bit(1) {}

    //Operadores
    //Resta de puntos
    Vector operator- (const Punto& pun) const {
        Vector resultado = Vector (this->x - pun.x, this->y - pun.y,
                                   this->z - pun.z);
        return resultado;
    }

    //Punto mas dirección
    Punto operator+ (const Vector& vec) const {
        Punto resultado = Punto (this->x + vec.getX(), this->y + vec.getY(),
                                   this->z + vec.getZ());
        return resultado;
    }

    //Punto mas dirección, invirtiendo direccion
    Punto operator- (const Vector& vec) const {
        Punto resultado = Punto (this->x - vec.getX(), this->y - vec.getY(),
                                 this->z - vec.getZ());
        return resultado;
    }


    //Punto por direccion
    float operator * (const Vector& vec) const {
        return this->x * vec.getX() + this->y * vec.getY() + this->z *
                                                                     vec.getZ();
    }

    float getBit() const {
        return bit;
    }

};