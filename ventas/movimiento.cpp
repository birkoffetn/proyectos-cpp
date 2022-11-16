#include"movimiento.h"
#include"detalle.h"

#include"utiles.h"

int movimiento_escoger_tipo(const char* mensaje){
    do{
        int opcion;
        std::cout<<mensaje<<"\n";
        std::cout<<"1. Entrada   2. Salida:\n";
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
}

void movimiento_guardar_movimiento(const Movimiento& movimiento, const Detalle detalles[]){
    registro_agregar(FICHERO_MOVIMIENTO, movimiento);
    for(int i= 0; i< movimiento.cantidadRegistros; ++i){
        registro_agregar(FICHERO_DETALLE, detalles[i]);
    }
}
