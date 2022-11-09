#include"utiles.h"

#include<iostream>

void leer_cadena(const char* mensaje, char* cadena, size_t tamanio){
    do{
        std::cout<<mensaje;
        for(size_t i= 0; i< tamanio; ++i){
            char actual= std::cin.get();
            if(actual== '\n'){
                cadena[i]= '\0';
                return;
            }
            else{
                cadena[i]= actual;
            }
        }
        std::cout<<"Ingrese un maximo de "<<tamanio<<" caracteres."<<std::endl;
        std::cin.ignore(1024000, '\n');
    }while(true);
}

bool confirmar_accion(const char* mensaje){
    do{
        int opcion;
        std::cout<<mensaje<<"\n";
        std::cout<<"  1. SI     2. NO\n";
        leer("Ingrese opcion: ", opcion);
        if(opcion== 1){
            return true;
        }
        else if(opcion== 2){
            return false;
        }
        else{
            std::cout<<"Opcion incorrecta..."<<std::endl;
        }
    }while(true);
}
