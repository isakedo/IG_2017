//
// Isak Edo Vivancos - 682405
// Tupla genérica de 3 valores en coma flotante de simple precisión
//

#pragma once

class Tupla {

protected:

    float x,y,z;

public:

    //Constructores
    Tupla () = default;
    Tupla (float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    //Getters
    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    float getZ() const {
        return z;
    }
};
