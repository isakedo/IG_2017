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
    explicit Geometria(RGB _color) : color(_color) {}

    const RGB &getColor() const {
        return color;
    }

};
