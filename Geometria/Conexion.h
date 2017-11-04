//
// Isak Edo Vivancos - 682405
// Conexión entre dos puntos en la superficie de dos esferas distintas, se
// calcula la conexión desde las cordinadas locales de cada punto en el
// constructor
//

#pragma once

class Conexion {

private:
    Punto_Superficie origen = Punto_Superficie(), destino = Punto_Superficie();
    Vector con_origen = Vector(), con_destino = Vector();
    // En sus respectivas coordenadas locales

public:

    //Constructor
    Conexion (const Punto_Superficie& _origen,
              const Punto_Superficie& _destino) {
        origen = _origen;
        destino = _destino;
        Vector conexion_globales = destino.getPosicion() - origen.getPosicion();
        Cambio_Base_Inversa locales_origen = Cambio_Base_Inversa (
        origen.getLatitud(),origen.getLongitud(), origen.getNormal(),
        origen.getPosicion());
        Cambio_Base_Inversa locales_destino = Cambio_Base_Inversa (
        destino.getLatitud(), destino.getLongitud(), destino.getNormal(),
        destino.getPosicion());
        con_origen = locales_origen * conexion_globales;
        con_destino = locales_destino * conexion_globales;
    }

};