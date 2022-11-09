#include "usuario.h"
#include "utiles.h"

#include <cstring>
#include <iostream>

void usuario_leer(const char *mensaje, Usuario &usuario)
{
    std::cout << mensaje << "\n";
    std::cout << "------------------------------------\n";
    leer_cadena("Usuario : ", usuario.usuario, TAMANIO_USUARIO);
    leer_cadena("Password: ", usuario.password, TAMANIO_PASSWORD);
}

bool operator==(const Usuario &a, const Usuario &b)
{
    bool sonIguales = false;
    if (strcmp(a.usuario, b.usuario) == 0)
    {
        if (strcmp(a.password, b.password) == 0)
        {
            sonIguales = true;
        }
    }
    return sonIguales;
}

bool usuario_existe(const Usuario &usuario)
{
    int posicion = registro_si_existe<Usuario>(FICHERO_USUARIOS,
                                               [&usuario](const Usuario &otro)
                                               { return usuario == otro; });
    return posicion != EOF;
}

void usuario_guardar(const Usuario &usuario)
{
    registro_agregar(FICHERO_USUARIOS, usuario);
}
