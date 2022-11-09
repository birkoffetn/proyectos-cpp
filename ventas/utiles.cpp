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