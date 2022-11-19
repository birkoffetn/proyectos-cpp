#ifndef __MOVIMIENTO__H__
#define __MOVIMIENTO__H__

#include<string>

const int TAMANIO_DETALLE= 20;
const int TIPO_VENTA= 1;
const int TIPO_COMPRA= 2;

struct Detalle;

const std::string FICHERO_MOVIMIENTO= "movimientos.dat";

struct Movimiento{
    int id;
    int tipo;
    char detalle[TAMANIO_DETALLE];
    int indiceDetalle;
    int cantidadRegistros;
};

void movimiento_leer_datos(Movimiento& movimiento);

void movimiento_imprimir(const Movimiento& movimiento);

void movimiento_guardar_movimiento(const Movimiento& movimiento, const Detalle detalles[]);

void movimiento_imprimir(std::ostream& salida, const Movimiento& movimiento, const Detalle detalles[]);

#endif
