//
// Created by isak on 4/10/17.
//

#ifndef IG_2017_TUPLA_H
#define IG_2017_TUPLA_H

class Tupla {

protected:
    float x,y,z;

public:

    //Constructores
    Tupla () : x(0), y(0), z(0) {}
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
