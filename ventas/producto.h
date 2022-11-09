#ifndef __PRODUCTO__H__
#define __PRODUCTO__H__

#include<string>

const int TAMANIO_NOMBRE_PROD= 30;
const std::string FICHERO_PRODUCTOS= "productos.dat";

struct Producto{
    int codigo;
    char nombre[TAMANIO_NOMBRE_PROD];
    double costo;
    double precio;
    int stock;
};

void producto_leer_codigo(const char* mensaje, Producto& producto);

void producto_leer_datos(const char* mensaje, Producto& producto);

bool producto_existe_codigo(int codigo);

void producto_guardar_nuevo(const Producto& producto);

int producto_imprimir_tabular(std::ostream& salida);

#endif