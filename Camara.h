//
// Isak Edo Vivancos - 682405
// Camara pinhole para capturar la imagen
//

#pragma once

class Camara {

private:

    Plano_proyeccion plano = Plano_proyeccion();
    Vector up = Vector(), left = Vector(), forward = Vector();
    Punto posicion = Punto(), inicio = Punto();
    Matriz_transformacion rotacion = Matriz_transformacion(),
            trasladar_origen = Matriz_transformacion(),
            trasladar_posicion = Matriz_transformacion();

public:

    //Constructor
    Camara() = default;
    Camara(const Vector& _left, const Vector& _up, const Vector& _forward,
           const Punto& _posicion) :
            left(_left), up(_up), forward(_forward), posicion(_posicion) {

        inicio = _posicion + _forward + _up + _left;
        rotacion = Matriz_transformacion(Vector(1,0,0),Vector(0,1,0),
                                         Vector(0,0,1),Punto(0,0,0));
        trasladar_origen = Matriz_transformacion(
                Vector(1,0,0),Vector(0,1,0),Vector(0,0,1),
                Punto(-posicion.getX(),-posicion.getY(),-posicion.getZ()));
        trasladar_posicion = Matriz_transformacion(
                Vector(1,0,0),Vector(0,1,0),Vector(0,0,1),
                Punto(posicion.getX(),posicion.getY(),posicion.getZ()));
    }

    const Punto &getPosicion() const {
        return posicion;
    }

    const Vector getRayo(const int& x, const int& y) const {
        Punto iter = Punto(inicio.getX() + x,inicio.getY(), inicio.getZ() - y);
        //Traslada al origen, rota y lo devuelve a su punto original
        iter = trasladar_origen * iter;
        iter = rotacion * iter;
        iter = trasladar_posicion * iter;
        return iter - posicion;
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
