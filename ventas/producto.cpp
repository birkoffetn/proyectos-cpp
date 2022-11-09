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
    salida<<std::right<<std::setw(10)<<"CODIGO";
    salida<<' '<<std::left<<std::setw(TAMANIO_NOMBRE_PROD)<<"NOMBRE";
    salida<<' '<<std::right<<std::setw(10)<<"COSTO";
    salida<<' '<<std::right<<std::setw(10)<<"PRECIO";
    salida<<' '<<std::right<<std::setw(10)<<"STOCK";
    salida<<'\n';
    std::ifstream entrada(FICHERO_PRODUCTOS);
    if(entrada.is_open()){
        Producto producto;
        while(entrada.read(reinterpret_cast<char*>(&producto), sizeof(Producto))){
            salida<<std::right<<std::setw(10)<<producto.codigo;
            salida<<' '<<std::left<<std::setw(TAMANIO_NOMBRE_PROD)<<producto.nombre;
            salida<<' '<<std::right<<std::setw(10)<<producto.costo;
            salida<<' '<<std::right<<std::setw(10)<<producto.precio;
            salida<<' '<<std::right<<std::setw(10)<<producto.stock;
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
