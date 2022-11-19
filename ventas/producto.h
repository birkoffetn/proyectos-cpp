#ifndef __PRODUCTO__H__
#define __PRODUCTO__H__

#include<string>

const int TAMANIO_NOMBRE_PROD= 20;
const std::string FICHERO_PRODUCTOS= "productos.dat";

struct Producto{
    int codigo;
    char nombre[TAMANIO_NOMBRE_PROD];
    double costo;
    double precio;
    int stock;
};

struct ExisteCodigo{
    ExisteCodigo(int codigo): codigo(codigo){}
    bool operator()(const Producto& producto){
        return codigo== producto.codigo;
    }
private:
    int codigo;
};

void producto_leer_codigo(const char* mensaje, Producto& producto);

void producto_leer_datos(const char* mensaje, Producto& producto);

void producto_ver_venta(const Producto& producto);

bool producto_existe_codigo(int codigo);

void producto_guardar_nuevo(const Producto& producto);

int producto_imprimir_tabular(std::ostream& salida);

bool producto_cambiar(Producto& producto);

bool producto_cargar(int codigo, Producto& producto);

void producto_imprimir(const Producto& producto);

#endif