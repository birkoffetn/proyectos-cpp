#ifndef __UTILES__H__
#define __UTILES__H__

#include<iostream>
#include<cctype>
#include<fstream>
#include<cstdio>
#include<string>

template<typename T>
void escribir_error(const T&){
    std::cout<<"Entrada incorrecta."<<std::endl;;
}

template<typename T>
void leer(const char* mensaje, T& dato){
    do{
        std::cout<<mensaje;
        if(isspace(std::cin.peek())){
            std::cout<<"No empiece con espacios en blanco."<<std::endl;
        }
        else{
            std::cin>>dato;
            if(std::cin.good()){
                if(std::cin.get()== '\n'){
                    return;
                }
                else{
                    std::cout<<"Termine su entrada con un salto de linea."<<std::endl;
                }
            }
            else{
                escribir_error(dato);
            }
        }
        std::cout<<"Intente de nuevo."<<std::endl;
        std::cin.clear();
        std::cin.ignore(1024000, '\n');
    }while(true);
}

template<typename T>
void registro_agregar(const std::string& nombreFichero, const T& registro){
    std::ofstream salida(nombreFichero, std::ios_base::app | std::ios_base::binary);
    if(salida.is_open()){
        salida.write(reinterpret_cast<const char*>(&registro), sizeof(T));
    }
    else{
        std::cerr<<"No se puede abrir '"<<nombreFichero<<"' para escritura."<<std::endl;
    }
}

template<typename T, typename Pred>
int registro_si_existe(const std::string& nombreFichero, Pred pred){
    std::ifstream entrada(nombreFichero, std::ios_base::binary);
    T registro;
    if(entrada.is_open()){
        int indice= entrada.tellg();
        while(entrada.read(reinterpret_cast<char*>(&registro), sizeof(T))){
            if(pred(registro)){
                return indice;
            }
            indice= entrada.tellg();
        }
    }
    else{
        std::cerr<<"Error al abrir '"<<nombreFichero<<"' para lectura."<<std::endl;
    }
    return EOF;
}

template<typename T, typename Pred>
bool registro_actualizar(const std::string& nombreFichero, const T& registro, Pred pred){
    int posicion= registro_si_existe<T>(nombreFichero, pred);
    if(posicion== EOF){
        return false;
    }
    else{
        std::ofstream salida(nombreFichero, std::ios_base::in |std::ios_base::binary);
        if(salida.is_open()){
            salida.seekp(posicion);
            salida.write(reinterpret_cast<const char*>(&registro), sizeof(T));
            return true;
        }
        else{
            std::cerr<<"Error al abrir '"<<nombreFichero<<"' para escritura."<<std::endl;
            return false;
        }
    }
}

template<typename T, typename Pred>
int registro_eliminar(const std::string& nombreFichero, Pred predicado){
    std::ifstream entrada(nombreFichero);
    if(entrada.is_open()){
        std::ofstream salida("temp");
        if(salida.is_open()){
            T registro;
            int contador= 0;
            while(entrada.read(reinterpret_cast<char*>(&registro), sizeof(T))){
                if(predicado(registro)){
                    ++contador;
                    continue;
                }
                else{
                    salida.write(reinterpret_cast<const char*>(&registro), sizeof(T));
                }
            }
            entrada.close();
            salida.close();
            if(contador> 0){
                std::string respaldo= nombreFichero+ ".back";
                std::rename(nombreFichero.c_str(), respaldo.c_str());
                std::rename("temp", nombreFichero.c_str());
                std::remove(respaldo.c_str());
            }
            else{
                std::remove("temp");
            }
            return contador;
        }
        else{
            std::cerr<<"No es posible crear fichero temporal."<<std::endl;
            return 0;
        }
    }
    else{
        std::cerr<<"No es posible abrir '"<<nombreFichero<<"' para lectura"<<std::endl;
        return 0;
    }
}

void leer_cadena(const char* mensaje, char* cadena, size_t tamanio);

#endif