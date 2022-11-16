#include<iostream>
#include<string>

using namespace std;

class Correspondencia{
public:
    virtual bool operator>=(const Correspondencia& otra) const;
    virtual double getPrecio() const= 0;
    virtual ~Correspondencia();

    const string& getDestinatario() const{ return destinatario; }
    const string& getDireccion() const{ return direccion; }
    const string& getRemitente() const{ return remitente; }
    void setDestinatario(const string& nombre){ destinatario= nombre; }
    void setDireccion(const string& direccion){ this->direccion= direccion; }
    void setRemitente(const string& nombre){ remitente= nombre; }
protected:
    void setPrioridad(int prioridad){ this->prioridad= prioridad; }
private:
    string destinatario;
    string direccion;
    string remitente;
    int prioridad;
};

Correspondencia::~Correspondencia(){}

bool Correspondencia::operator>=(const Correspondencia& otra) const{
    return prioridad>= otra.prioridad;
}

class Fecha{
public:
    int diasA(const Fecha& otra) const{ return 10; }
};

class Carta: public Correspondencia{
public:
    Carta();
    void setFechaEnvio(const Fecha& fecha){ this->fecha= fecha; }
    void setTipoExterior(bool exterior){ this->exterior= exterior; }
    double getPrecio() const override;
private:
    Fecha fecha;
    bool exterior;
};

Carta::Carta(){
    setPrioridad(2);
}

double Carta::getPrecio() const{
    Fecha hoy;
    double precio= 0.0;
    if(fecha.diasA(hoy)> 10){
        precio+= 5;
        if(exterior== true){
            precio+= 5;
        }
    }
    else{
        precio+= 8.0;
        if(exterior== true){
            precio+= 3;
        }
    }
    return precio;
}

class Telegrama: public Carta{
public:
    Telegrama();
    void setCantidadPalabras(int cantidad){ palabras= cantidad; }
    void setPorcentajeImpuesto(int porcentaje){
        impuesto= porcentaje/ 100.0;
    }
    double getPrecio() const override;
private:
    int palabras;
    double impuesto;
};

Telegrama::Telegrama(){
    setPrioridad(1);
}

double Telegrama::getPrecio() const{
    double precio= Carta::getPrecio();
    return precio* (1+ impuesto);
}

enum class Urgencia{Urgente, Medio, Indiferente};

class BultoPostal: public Correspondencia{
public:
    BultoPostal();
    void setPeso(int peso){ this->peso= peso; }
    void setUrgencia(Urgencia urgencia){ this->urgencia= urgencia; }
    double getPrecio() const override;
private:
    Urgencia urgencia;
    int peso;
};

BultoPostal::BultoPostal(){
    setPrioridad(3);
}

double BultoPostal::getPrecio() const{
    double precio= peso* 4;
    if(urgencia== Urgencia::Urgente){
        precio+= 10;
    }
    else if(urgencia== Urgencia::Medio){
        precio+= 8;
    }
    return precio;
}

class ListaCorrespondencia{
public:
    ListaCorrespondencia();
    ~ListaCorrespondencia();
    void agregar(Correspondencia* correspondencia);
    bool estaVacia() const;
    Correspondencia& siguiente();
    void eliminarSiguiente();
    template<typename Fun>
    void foreach(Fun fun) const;
private:
    struct NodoBase{
        NodoBase* siguiente;
        void atarDespues(NodoBase* nodo){
            nodo->siguiente= siguiente;
            siguiente= nodo;
        }
        NodoBase* desatarSiguiente(){
            NodoBase* nodo= siguiente;
            siguiente= siguiente->siguiente;
            nodo->siguiente= nullptr;
            return nodo;
        }
    };
    struct Nodo: public NodoBase{
        Correspondencia* dato;
        Nodo(Correspondencia* dato): dato(dato){
            siguiente= nullptr;
        }
        ~Nodo(){
            delete dato;
        }
    };

    NodoBase centinela;
};

ListaCorrespondencia::ListaCorrespondencia(){
    centinela.siguiente= nullptr;
}

ListaCorrespondencia::~ListaCorrespondencia(){
    while(!estaVacia()){
        eliminarSiguiente();
    }
}

void ListaCorrespondencia::agregar(Correspondencia* correspondencia){
    Nodo* nuevo= new Nodo(correspondencia);
    NodoBase* previo= &centinela;
    while(previo->siguiente!= nullptr){
        if((*nuevo->dato)>= *(static_cast<Nodo*>(previo->siguiente)->dato));
        else break;
        previo= previo->siguiente;
    }
    previo->atarDespues(nuevo);
}

bool ListaCorrespondencia::estaVacia() const{
    return centinela.siguiente== nullptr;
}

Correspondencia& ListaCorrespondencia::siguiente(){
    return *static_cast<Nodo*>(centinela.siguiente)->dato;
}

void ListaCorrespondencia::eliminarSiguiente(){
    Nodo* temp= static_cast<Nodo*>(centinela.desatarSiguiente());
    delete temp;
}

template<typename Fun>
void ListaCorrespondencia::foreach(Fun fun) const{
    const NodoBase* it= centinela.siguiente;
    while(it!= nullptr){
        fun(*static_cast<const Nodo*>(it)->dato);
        it= it->siguiente;
    }
}

class OficinaPostal{
public:
    OficinaPostal(){}
    ~OficinaPostal(){}
    void run();
private:
    template<typename T>
    Correspondencia* create(){ return new T; }
    void recibir();
    void despachar();
    void entregar();
    void calcularPrecio();
    void verLista() const;

    void leerNueva(Carta* carta);
    void leerNueva(Telegrama* telegrama);
    void leerNueva(BultoPostal* bulto);

    Correspondencia* nueva;
    ListaCorrespondencia lista;

    void mostrarCorrespondencia(const Correspondencia* correspondencia) const;
    bool confirmar(const char* mensaje) const;
};

void OficinaPostal::run(){
    int opcion;
    do{
        system("clear");
        cout<<"---Oficina de Correos---\n";
        cout<<"1. Recibir correspondencia\n";
        cout<<"2. Despachar correspondencia\n";
        cout<<"3. Entregar\n";
        cout<<"4. Calcular precio\n";
        cout<<"5. Mostrar lista\n";
        cout<<"0. Salir\n";
        cout<<"Ingrese opcion: ";
        cin>>opcion;
        switch(opcion){
            case 1:
                recibir();
                system("pause");
                break;
            case 2:
                despachar();
                system("pause");
                break;
            case 3:
                entregar();
                system("pause");
                break;
            case 4:
                calcularPrecio();
                system("pause");
                break;
            case 5:
                verLista();
                system("pause");
                break;
            case 0:
                cout<<"Terminando aplicacion..."<<endl;
                break;
            default:
                cout<<"Inorrecto, intente de nuevo:"<<endl;
                system("pause");
                break;
        }
    }while(opcion!= 0);
}

void OficinaPostal::recibir(){
    int opcion;
    cout<<"Ingrese el tipo de correspondencia:\n";
    cout<<"1. Carta     2.Telegrama     3. Bulto postal\n";
    cout<<"Ingrese opcion: ";
    cin>>opcion;
    switch(opcion){
        case 1:
            nueva= create<Carta>();
            leerNueva(static_cast<Carta*>(nueva));
            break;
        case 2:
            nueva= create<Telegrama>();
            leerNueva(static_cast<Telegrama*>(nueva));
            break;
        case 3:
            nueva= create<BultoPostal>();
            leerNueva(static_cast<BultoPostal*>(nueva));
            break;
        default:
            break;
    }
    if(nueva!= nullptr){
        int respuesta;
        cout<<"Guardar correspondencia? 1. SI      2. NO: ";
        cin>>respuesta;
        if(respuesta== 1){
            lista.agregar(nueva);
            nueva= nullptr;
            cout<<"Correspondencia agregada satisfactoriamente."<<endl;
        }
        else{
            cout<<"Selecciono no o una opcion incorrecta."<<endl;
            delete nueva;
            nueva= nullptr;
        }
    }
    else{
        cout<<"Usted ingreso una opcion incorrecta."<<endl;
    }
}

void leer_correspondencia(Correspondencia* correspondencia){
    cout<<"Ingrese los datos para la correspondencia:\n";
    string dato;
    cin.ignore();
    cout<<"Ingrese destinatario: ";
    getline(cin, dato);
    correspondencia->setDestinatario(dato);
    cout<<"Ingrese Direccion---: ";
    getline(cin, dato);
    correspondencia->setDireccion(dato);
    cout<<"Ingrese remitente---: ";
    getline(cin, dato);
    correspondencia->setRemitente(dato);
}

void OficinaPostal::leerNueva(Carta* carta){
    Correspondencia* correspondencia= carta;
    leer_correspondencia(correspondencia);

    string fecha;
    int opcion;
    cout<<"Ingrese los datos de la carta:\n";
    cout<<"Ingrese fecha: ";
    carta->setFechaEnvio(Fecha());
    getline(cin, fecha);
    cout<<"La carta es del exterior?\n";
    cout<<"1. SI    2. NO     ocion: ";
    cin>>opcion;
    if(opcion== 1){
        carta->setTipoExterior(true);
    }
    else{
        carta->setTipoExterior(false);
    }
}

void OficinaPostal::leerNueva(Telegrama* telegrama){
    Carta* carta= telegrama;
    leerNueva(carta);
    int cantidad, porcentaje;
    cout<<"Ingrese los datos del telegrama:\n";
    cout<<"Cantidad palabras---- : ";
    cin>>cantidad;
    telegrama->setCantidadPalabras(cantidad);
    cout<<"Porcentaje de impuesto: ";
    cin>>porcentaje;
    telegrama->setPorcentajeImpuesto(porcentaje);
}

void OficinaPostal::leerNueva(BultoPostal* bulto){
    Correspondencia* correspondencia= bulto;
    leer_correspondencia(correspondencia);
    cout<<"Ingrese los datos del bulto postal:\n";
    int peso, urgencia;
    cout<<"Ingrese peso del bulto: ";
    cin>>peso;
    cout<<"Ingrese urgencia:\n";
    cout<<"1. Urgente   2. Medio  3. Indiferente\n";
    cout<<"opcion: ";
    cin>>urgencia;
    switch(urgencia){
        case 1:
            bulto->setUrgencia(Urgencia::Urgente);
            break;
        case 2:
            bulto->setUrgencia(Urgencia::Medio);
            break;
        default:
            bulto->setUrgencia(Urgencia::Indiferente);
            break;
    }
}

void OficinaPostal::despachar(){
    if(lista.estaVacia()){
        cout<<"No hay nada pendiente de entrega."<<endl;
    }
    else{
        cout<<"Mostrando siguiente producto:\n";
        mostrarCorrespondencia(&lista.siguiente());
        if(confirmar("Esta Seguro?")){
            lista.eliminarSiguiente();
            cout<<"Correspondencia entregada exitosamente."<<endl;
        }
        else{
            cout<<"No se han hecho cambios"<<endl;
        }
    }
}

void OficinaPostal::entregar(){
    if(lista.estaVacia()){
        cout<<"No hay nada que entregar..."<<endl;
    }
    else{
        cout<<"Nombre   : "<<"\n";
        cout<<"Direccion: "<<"\n";
        lista.eliminarSiguiente();
        cout<<"=> Correspondencia entregada."<<endl;
    }
}

void OficinaPostal::calcularPrecio(){
    cout<<"Calculando precio de la lista..."<<endl;
    double total= 0.0;
    auto suma= [&total](const Correspondencia& actual){
        total+= actual.getPrecio();
    };
    lista.foreach(suma);
    cout<<"La suma total es: "<<total<<endl;
}

void OficinaPostal::verLista() const{
    cout<<"Mostrando lista de correspondencia."<<endl;
    if(lista.estaVacia()){
        cout<<"La lista esta vacia, nada que mostrar."<<endl;
    }
    else{
        int contador= 0;
        auto imprimir= [&contador](const Correspondencia& c){
            cout<<c.getDestinatario()<<endl;
            cout<<c.getDireccion()<<endl;
            cout<<"----------------"<<endl;
            ++contador;
        };
        lista.foreach(imprimir);
        cout<<"=> "<<contador<<" registros mostrados."<<endl;
    }
}

void OficinaPostal::mostrarCorrespondencia(const Correspondencia* correspondencia) const{
    cout<<"Destinatario: "<<correspondencia->getDestinatario()<<endl;
    cout<<"Direccion---: "<<correspondencia->getDireccion()<<endl;
    cout<<"Remitente---: "<<correspondencia->getRemitente()<<endl;
}

bool OficinaPostal::confirmar(const char* mensaje) const{
    cout<<mensaje<<endl;
    cout<<"1. SI    2. NO   => opcion: ";
    int opcion;
    cin>>opcion;
    return opcion== 1;
}

int main(){
    OficinaPostal oficina;
    oficina.run();
    return 0;
}
/*
Puedes resolverlo con tres clases principales:
1. Correspondencia (carta, telegrama y bulto heredan de ella).
2. ListaDeEntrega (Lista simple ordenada o una cola de prioridad o un arbol binario)
3. OficinaDeCorreo (Que se relacionará con el usuario y encargada de ofrecer la funcionalidad deseada)
Tambien neccesitas una clase auxiliar Fecha para restar fechas y demas.
*/
