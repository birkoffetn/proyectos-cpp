#ifndef __USUARIO__H__

#include<string>

const int TAMANIO_USUARIO= 15;
const int TAMANIO_PASSWORD= 15;

const std::string FICHERO_USUARIOS= "usuarios.dat";

struct Usuario{
    char usuario[TAMANIO_USUARIO];
    char password[TAMANIO_PASSWORD];
};

void usuario_leer(const char* mensaje, Usuario& usuario);

bool operator==(const Usuario& a, const Usuario& b);

bool usuario_existe(const Usuario& usuario);

void usuario_guardar(const Usuario& usuario);

#endif