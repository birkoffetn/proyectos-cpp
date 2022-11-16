#ifndef __DETALLE__H__
#define __DETALLE__H__

#include"producto.h"

#include<string>

const std::string FICHERO_DETALLE= "detalles.dat";

struct Detalle{
    int codigo;
    char nombre[TAMANIO_NOMBRE_PROD];
    int cantidad;
    double precio;
};

void detalle_leer_venta(const Producto& producto, Detalle& detalle);

#endif