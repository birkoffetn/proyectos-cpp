#include"detalle.h"

#include<cstring>
#include<iostream>
#include<iomanip>

void detalle_leer_venta(const Producto& producto, Detalle& detalle){
    detalle.codigo= producto.codigo;
    strcpy(detalle.nombre, producto.nombre);
    detalle.precio= producto.precio;
}

void detalle_imprimir_tabular(std::ostream& salida, const Detalle& detalle){
    salida<<std::fixed;
    salida.precision(2);

    salida<<std::right<<std::setw(8)<<detalle.codigo;
    salida<<" "<<std::left<<std::setw(20)<<detalle.nombre;
    salida<<" "<<std::right<<std::setw(7)<<detalle.cantidad;
    salida<<" "<<std::right<<std::setw(8)<<detalle.precio;
    salida<<" "<<std::right<<std::setw(8)<<detalle.cantidad* detalle.precio;
}

void detalle_de_venta(Detalle& detalle, const Producto& producto){
    detalle.codigo= producto.codigo;
    strcpy(detalle.nombre, producto.nombre);
    detalle.precio= producto.precio;
}

void detalle_de_compra(Detalle& detalle, const Producto& producto){
    detalle.codigo= producto.codigo;
    strcpy(detalle.nombre, producto.nombre);
    detalle.precio= producto.costo;
}
