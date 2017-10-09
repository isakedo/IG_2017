//
// Created by isak on 4/10/17.
//

#ifndef IG_2017_TUPLA_H
#define IG_2017_TUPLA_H

class Tupla {

protected:
    float x,y,z,bit;

public:

    //Constructores
    Tupla () : x(0), y(0), z(0), bit(0) {}
    Tupla (float _x, float _y, float _z, float _bit) : x(_x), y(_y),
                                                       z(_z), bit(_bit) {}

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

    float getBit() const {
        return bit;
    }

    //Setters
    void setX(float x) {
        Tupla::x = x;
    }

    void setY(float y) {
        Tupla::y = y;
    }

    void setZ(float z) {
        Tupla::z = z;
    }

};


#endif //IG_2017_TUPLA_H
