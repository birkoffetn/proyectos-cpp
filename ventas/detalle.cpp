#include"detalle.h"

#include<cstring>

void detalle_leer_venta(const Producto& producto, Detalle& detalle){
    detalle.codigo= producto.codigo;
    strcpy(detalle.nombre, producto.nombre);
    detalle.precio= producto.precio;
}