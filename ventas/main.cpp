#include "utiles.h"
#include "usuario.h"
#include "producto.h"

#include <iostream>
#include <cstring>

void sistema_alta_producto(){
    Producto nuevoProducto;
    producto_leer_codigo("Ingrese un entero que identifique al producto: ", nuevoProducto);
    if(producto_existe_codigo(nuevoProducto.codigo)){
        std::cout<<"El codigo introducido ya está en uso."<<std::endl;
    }
    else{
        producto_leer_datos("Ingrese los datos del nuevo producto: ", nuevoProducto);
        producto_guardar_nuevo(nuevoProducto);
        std::cout<<"Producto agregado exitosamente."<<std::endl;
    }
    system("pause");
}

void sistema_listar_productos(){
    std::cout<<"=> Mostrando productos registrados:\n";
    producto_imprimir_tabular(std::cout);
    system("pause");
}

void sistema_editar_producto(){
    Producto producto;
    int codigo;
    std::cout<<"---EDITAR PRODUCTO---\n";
    leer("Ingrese codigo de producto: ", codigo);
    auto predicado= [codigo](const Producto& producto){ return codigo== producto.codigo; };
    int posicion= registro_si_existe<Producto>(FICHERO_PRODUCTOS, predicado);
    if(posicion== EOF){
        std::cout<<"El producto no se encuentra registrado."<<std::endl;
    }
    else{
        if(registro_leer(FICHERO_PRODUCTOS, posicion, producto)){
            if(producto_cambiar(producto)){
                if(registro_actualizar(FICHERO_PRODUCTOS, producto, predicado)){
                    std::cout<<"Registro modificado correctamente."<<std::endl;
                }
                else{
                    std::cerr<<"Error al guardar cambios..."<<std::endl;
                }
            }
            else{
                std::cout<<"Se sale sin cambios."<<std::endl;
            }
        }
        else{
            std::cerr<<"Error en la lectura de fichero."<<std::endl;
        }
    }
    system("pause");
}

void sistema_aplicacion()
{
    int opcion;
    do{
        system("cls");
        std::cout<<"---Sistema de Ventas---\n";
        std::cout<<"-----------------------\n";
        std::cout<<"1. Crear producto\n";
        std::cout<<"2. Listar productos\n";
        std::cout<<"3. Editar producto\n";
        std::cout<<"0. Cerrar sesion\n";
        std::cout<<"-----------------------\n";
        leer("Ingrese opcion: ", opcion);
        switch(opcion){
        case 1:
            sistema_alta_producto();
            break;
        case 2:
            sistema_listar_productos();
            break;
        case 3:
            sistema_editar_producto();
            break;
        }
    }while(opcion!= 0);
}

void sistema_ingresar()
{
    Usuario usuario;
    usuario_leer("Ingrese los datos del Usuario:", usuario);
    if (usuario_existe(usuario))
    {
        sistema_aplicacion();
    }
    else
    {
        std::cout << "Usuario no registrado o password incorrecto." << std::endl;
        system("pause");
    }
}

void sistema_registrar()
{
    Usuario nuevoUsuario;
    usuario_leer("Ingrese los datos del nuevo usuario: ", nuevoUsuario);
    auto predicado = [&nuevoUsuario](const Usuario &usuario)
    {
        return strcmp(nuevoUsuario.usuario, usuario.usuario) == 0;
    };
    int posicion = registro_si_existe<Usuario>(FICHERO_USUARIOS, predicado);
    if (posicion == EOF)
    {
        std::cout << "Registrando nuevo usuario..." << std::endl;
        usuario_guardar(nuevoUsuario);
        std::cout << "Usuario registrado exitosamente." << std::endl;
    }
    else
    {
        std::cout << "El nombre de usuario ya esta en uso, intente otro" << std::endl;
    }
    system("pause");
}

int main()
{
    int opcion;
    do
    {
        system("cls");
        std::cout << "---Menu principal---\n";
        std::cout << "--------------------\n";
        std::cout << "1. Ingresar\n";
        std::cout << "2. Crear usuario\n";
        std::cout << "0. Salir\n";
        std::cout << "--------------------\n";
        leer("Ingrese opcion: ", opcion);
        switch (opcion)
        {
        case 1:
            sistema_ingresar();
            break;
        case 2:
            sistema_registrar();
            break;
        case 0:
            std::cout << "Saliendo aplicacion..." << std::endl;
            break;
        default:
            std::cout << "Opcion incorrecta, intente de nuevo." << std::endl;
            system("pause");
            break;
        }
    } while (opcion != 0);
    return 0;
}
