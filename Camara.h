//
// Isak Edo Vivancos - 682405
// Camara pinhole para capturar la imagen
//

#pragma once

class Camara {

private:

    int offset = 0;
    __uint16_t num_pixeles_ejex, num_pixeles_ejey;
    Plano_proyeccion plano = Plano_proyeccion();
    Vector up = Vector(), left = Vector(), forward = Vector();
    Punto posicion = Punto(), inicio = Punto();
    Matriz_transformacion rotacion = Matriz_transformacion(),
            trasladar_origen = Matriz_transformacion(),
            trasladar_posicion = Matriz_transformacion();
    std::mt19937 mt;
    std::uniform_real_distribution<float> dist;

public:

    //Constructor
    Camara() = default;
    Camara(const Vector& _left, const Vector& _up, const Vector& _forward,
           const Punto& _posicion, const __uint16_t& _num_pixeles_ejex,
           const __uint16_t& _num_pixeles_ejey, const std::mt19937 _mt) :
            left(_left), up(_up), forward(_forward), posicion(_posicion),
            num_pixeles_ejex(_num_pixeles_ejex),
            num_pixeles_ejey(_num_pixeles_ejey), mt(_mt){

        plano = Plano_proyeccion(num_pixeles_ejex,num_pixeles_ejey);
        inicio = _posicion + _forward + _up + _left;
        rotacion = Matriz_transformacion(Vector(1,0,0),Vector(0,1,0),
                                         Vector(0,0,1),Punto(0,0,0));
        trasladar_origen = Matriz_transformacion(
                Vector(1,0,0),Vector(0,1,0),Vector(0,0,1),
                Punto(-posicion.getX(),-posicion.getY(),-posicion.getZ()));
        trasladar_posicion = Matriz_transformacion(
                Vector(1,0,0),Vector(0,1,0),Vector(0,0,1),
                Punto(posicion.getX(),posicion.getY(),posicion.getZ()));
        dist = std::uniform_real_distribution<float>(-0.5f, 0.5f);
    }

    const Punto &getPosicion() const {
        return posicion;
    }

    __uint16_t getNum_pixeles_ejex() const {
        return num_pixeles_ejex;
    }

    __uint16_t getNum_pixeles_ejey() const {
        return num_pixeles_ejey;
    }

    const Vector getRayo(const int& x, const int& y) const {
        Punto iter = Punto(inicio.getX() + x,inicio.getY(), inicio.getZ() - y);
        //Traslada al origen, rota y lo devuelve a su punto original
        iter = trasladar_origen * iter;
        iter = rotacion * iter;
        iter = trasladar_posicion * iter;
        return iter - posicion;
    }

    const Vector getRayo_random(const int& x, const int& y) {
        float rand1 = dist(mt);
        float rand2 = dist(mt);
        float rand3 = dist(mt);
        float offset_x = (offset % 5) * 0.25f - 0.5f;
        float offset_y = (offset / 5) * 0.25f - 0.5f;
        Punto iter = Punto(inicio.getX() + x,inicio.getY(), inicio.getZ() - y);
        Punto random = Punto(iter.getX() + offset_x + rand1, iter.getY() + rand2,
                             iter.getZ() + offset_y + rand3);
        //Traslada al origen, rota y lo devuelve a su punto original
        random = trasladar_origen * random;
        random = rotacion * random;
        random = trasladar_posicion * random;
        offset += 1;
        if(offset == 25) offset = 0;
        return random - posicion;
    }

    const RGB &getColor(const int& x, const int& y) const {
        return plano.getColor(x,y);
    }

    void setColor(const int& x, const int& y, const RGB& color) {
        plano.setColor(x,y,color);
    }

    void rotar_x(const float& angulo) {
        Matriz_transformacion rotar = Matriz_transformacion(
                Vector(1,0,0),Vector(0,cosf(angulo),sinf(angulo)),
                Vector(0,-sinf(angulo),cosf(angulo)),Punto(0,0,0));
        rotacion = rotacion * rotar;
    }

    void rotar_y(const float& angulo) {
        Matriz_transformacion rotar = Matriz_transformacion(
                Vector(cosf(angulo),0,-sinf(angulo)),Vector(0,1,0),
                Vector(sinf(angulo),0,cosf(angulo)),Punto(0,0,0));
        rotacion = rotacion * rotar;
    }

    void rotar_z(const float& angulo) {
        Matriz_transformacion rotar = Matriz_transformacion(
                Vector(cosf(angulo),sinf(angulo),0),
                Vector(-sinf(angulo),cosf(angulo),0),Vector(0,0,1),
                Punto(0,0,0));
        rotacion = rotacion * rotar;
    }


};
