#include"producto.h"
#include"utiles.h"

#include<iomanip>

void producto_leer_codigo(const char* mensaje, Producto& producto){
    std::cout<<mensaje<<"\n";
    leer       ("Codigo: ", producto.codigo);
}

void producto_leer_datos(const char* mensaje, Producto& producto){
    std::cout<<mensaje<<"\n";
    leer_cadena("Nombre: ", producto.nombre, TAMANIO_NOMBRE_PROD);
    leer       ("Costo : ", producto.costo);
    leer       ("Precio: ", producto.precio);
    leer       ("Stock : ", producto.stock);
}

void producto_ver_venta(const Producto& producto){
    std::cout<<"----------------------------\n";
    std::cout<<"Nombre: "<<producto.nombre<<"\n";
    std::cout<<"Precio: "<<producto.precio<<"\n";
    std::cout<<"Stock : "<<producto.stock<<"\n";
    std::cout<<"----------------------------\n";
}

bool producto_existe_codigo(int codigo){
    auto predicado= [codigo](const Producto& producto){ return codigo== producto.codigo; };
    int posicion= registro_si_existe<Producto>(FICHERO_PRODUCTOS, predicado);
    return posicion != EOF;
}

void producto_guardar_nuevo(const Producto& producto){
    registro_agregar(FICHERO_PRODUCTOS, producto);
}

int producto_imprimir_tabular(std::ostream& salida){
    int contador= 0;
    salida<<std::fixed;
    salida.precision(2);
    salida<<std::right<<std::setw(8)<<"CODIGO";
    salida<<' '<<std::left<<std::setw(TAMANIO_NOMBRE_PROD)<<"NOMBRE";
    salida<<' '<<std::right<<std::setw(7)<<"COSTO";
    salida<<' '<<std::right<<std::setw(7)<<"PRECIO";
    salida<<' '<<std::right<<std::setw(6)<<"STOCK";
    salida<<'\n';
    std::ifstream entrada(FICHERO_PRODUCTOS);
    if(entrada.is_open()){
        Producto producto;
        while(entrada.read(reinterpret_cast<char*>(&producto), sizeof(Producto))){
            salida<<std::right<<std::setw(8)<<producto.codigo;
            salida<<' '<<std::left<<std::setw(TAMANIO_NOMBRE_PROD)<<producto.nombre;
            salida<<' '<<std::right<<std::setw(7)<<producto.costo;
            salida<<' '<<std::right<<std::setw(7)<<producto.precio;
            salida<<' '<<std::right<<std::setw(6)<<producto.stock;
            salida<<"\n";
            ++contador;
        }
        if(contador> 0){
            salida<<contador<<" productos listados."<<std::endl;
        }
        else{
            salida<<"No hay productos registrados."<<std::endl;
        }
    }
    else{
        std::cerr<<"No es posible abrir '"<<FICHERO_PRODUCTOS<<"' para lectura."<<std::endl;
    }
    return contador;
}

bool producto_cambiar(Producto& producto){
    bool actualizado= false;
    system("cls");
    std::cout<<"---CAMBIAR DATOS---\n";
    std::cout<<"-------------------\n";
    std::cout<<"Nombre: "<<producto.nombre<<"\n";
    if(confirmar_accion("Desea modificcar?")){
        leer_cadena("Nombre: ", producto.nombre, TAMANIO_NOMBRE_PROD);
        actualizado= true;
    }
    std::cout<<"-------------------\n";
    std::cout<<"Costo: "<<producto.costo<<"\n";
    if(confirmar_accion("Desea modificcar?")){
        leer("Costo: ", producto.costo);
        actualizado= true;
    }
    std::cout<<"-------------------\n";
    std::cout<<"Precio: "<<producto.precio<<"\n";
    if(confirmar_accion("Desea modificcar?")){
        leer("Precio: ", producto.precio);
        actualizado= true;
    }
    return actualizado;
}
