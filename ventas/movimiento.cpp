#include"movimiento.h"
#include"detalle.h"

#include"utiles.h"

#include<iostream>
#include<iomanip>

int movimiento_escoger_tipo(const char* mensaje){
    do{
        int opcion;
        std::cout<<mensaje<<"\n";
        std::cout<<"1. Venta   2. Compra:\n";
        leer("Ingrese opcion: ", opcion);
        if(opcion == 1 || opcion== 2){
            return opcion;
        }
        else{
            std::cout<<"\nOpcion incorrecta, intente de nuevo:"<<std::endl;
        }
    }while(true);
}

void movimiento_leer_datos(Movimiento& movimiento){
    movimiento.tipo= movimiento_escoger_tipo("Escoja el tipo de movimiento");
    leer_cadena("Detalle: ", movimiento.detalle, TAMANIO_DETALLE);
    movimiento.cantidadRegistros= 0;
    movimiento.id= registro_contar_registros<Movimiento>(FICHERO_MOVIMIENTO)+ 1;
    movimiento.indiceDetalle= registro_contar_registros<Detalle>(FICHERO_DETALLE)* sizeof(Detalle);
}

void movimiento_guardar_movimiento(const Movimiento& movimiento, const Detalle detalles[]){
    for(int i= 0; i< movimiento.cantidadRegistros; ++i){
        Producto producto;
        if(producto_cargar(detalles[i].codigo, producto)){
            if(movimiento.tipo== TIPO_VENTA){
                producto.stock-= detalles[i].cantidad;
            }
            else{
                producto.stock+= detalles[i].cantidad;
            }
            if(registro_actualizar(FICHERO_PRODUCTOS, producto, ExisteCodigo(detalles[i].codigo)));
            else{
                std::cerr<<"No es posible actualizar existencias. Error al actualizar producto."<<std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else{
            std::cerr<<"No es posible actualizar existencias. Error al leer producto."<<std::endl;
            exit(EXIT_FAILURE);
        }
    }
    for(int i= 0; i< movimiento.cantidadRegistros; ++i){
        registro_agregar(FICHERO_DETALLE, detalles[i]);
    }
    registro_agregar(FICHERO_MOVIMIENTO, movimiento);
}

void movimiento_imprimir(std::ostream& salida, const Movimiento& movimiento, const Detalle detalles[]){
    char relleno= salida.fill('-');
    salida<<std::setw(56)<<"-"<<"\n";

    salida<<"Tipo---: "<<(movimiento.tipo== 1? "Venta": "Compra")<<"\n";
    salida<<"Numero-: "<<movimiento.id<<"\n";
    salida<<"Detalle: "<<movimiento.detalle<<"\n";

    salida<<std::setw(56)<<"-"<<"\n";

    salida.fill(' ');
    salida<<std::right<<std::setw(8)<<"CODIGO";
    salida<<" "<<std::left<<std::setw(20)<<"DETALLE";
    salida<<" "<<std::right<<std::setw(7)<<"CANT.";
    salida<<" "<<std::right<<std::setw(8)<<"PRECIO";
    salida<<" "<<std::right<<std::setw(8)<<"SUBTOTAL\n";
    for(int i= 0; i< movimiento.cantidadRegistros; ++ i){
        detalle_imprimir_tabular(salida, detalles[i]);
        salida<<"\n";
    }
    salida.fill('-');
    salida<<std::setw(56)<<"-"<<"\n";
    int cantidad= 0;
    double total= 0.0;
    salida.fill(' ');
    for(int i= 0; i< movimiento.cantidadRegistros; ++i){
        cantidad+= detalles[i].cantidad;
        total+= detalles[i].precio* detalles[i].cantidad;
    }
    salida<<std::right<<std::setw(38)<<cantidad;
    salida<<std::right<<std::setw(18)<<total<<"\n";
    salida.fill('-');
    salida<<std::setw(56)<<"-"<<"\n";
    salida.fill(relleno);
}
