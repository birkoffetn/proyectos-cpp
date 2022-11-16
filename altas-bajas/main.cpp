#include<iostream>
#include<fstream>

using namespace std;

const int SIZE_NAME= 20;
const int SIZE_EMAIL= 30;

struct Record{
    int id;
    char name[SIZE_NAME];
    int phone;
    char email[SIZE_EMAIL];
};

void read_record_id(Record* record){
    cout<<"Id------:";
    cin>>record->id;
}

void read_record(Record* record){
    cout<<"Nombre--: ";
    cin.ignore();
    cin.getline(record->name, SIZE_NAME);
    cout<<"Telefono: ";
    cin>>record->phone;
    cin.ignore();
    cout<<"Email---: ";
    cin.getline(record->email, SIZE_EMAIL);
}

void print_record(Record* record){
    cout<<"Id------:"<<record->id<<"\n";
    cout<<"Nombre--: "<<record->name<<"\n";
    cout<<"Telefono: "<<record->phone<<"\n";
    cout<<"Email---: "<<record->email<<"\n";
}

void save_new(struct Record* record){
    ofstream output("agenda.dat", ios_base::app | ios_base::binary);
    if(output.is_open()){
        output.write((char*)record, sizeof(Record));
    }
    else{
        cout<<"No es posible abrir 'agenda.dat' para escritura."<<endl;
    }
}

int modify_by_id(int id, Record* newRecord){
    int cont= 0;
    ifstream input("agenda.dat", ios_base::binary);
    if(input.is_open()){
        ofstream temp("temp.dat", ios_base::binary);
        if(temp.is_open()){
            Record current;
            while(input.read((char*)&current, sizeof(Record))){
                if(current.id== id){
                    if(newRecord!= nullptr){
                        temp.write((char*)newRecord, sizeof(Record));
                    }
                    cont+= 1;
                }
                else{
                    temp.write((char*)&current, sizeof(Record));
                }
            }
            temp.close();
            input.close();
            if(cont> 0){
                //pendiente: hacer comprobaciones
                rename("agenda.dat", "agenda.back");
                rename("temp.dat", "agenda.dat");
                remove("agenda.back");
            }
            else{
                remove("temp.dat");
            }
        }
        else{
            cout<<"No es posible crear fichero temporal."<<endl;
            exit(EXIT_FAILURE);
        }
    }
    else{
        cout<<"No es posible abrir 'agenda.dat' para lectura"<<endl;
        exit(EXIT_FAILURE);
    }
    return cont;
}

int remove_by_id(int id){
    return modify_by_id(id, nullptr);
}

bool read_first_by_id(int id, Record* record){
    ifstream input("agenda.dat", ios_base::binary);
    bool stock= false;
    if(input.is_open()){
        while(input.read((char*)record, sizeof(Record))){
            if(id== record->id){
                stock= true;
                break;
            }
        }
    }
    else{
        cout<<"No es posible abrir 'agenda.dat' para lectura"<<endl;
        exit(EXIT_FAILURE);
    }
    return stock;
}

int print_all_records(){
    int cont= 0;
    ifstream input("agenda.dat", ios_base::binary);
    if(input.is_open()){
        Record temp;
        while(input.read((char*)&temp, sizeof(temp))){
            print_record(&temp);
            cout<<"--------------------\n";
            ++cont;
        }
    }
    else{
        cout<<"No es posible abrir 'agenda.dat' para lectura"<<endl;
        exit(EXIT_FAILURE);
    }
    return cont;
}

void create_agenda(){
    ofstream agenda("agenda.dat", ios_base::binary | ios_base::app);
    if(!agenda.is_open()){
        cout<<"No es posible abrir fichero 'agenda.dat' para lectura-escritura."<<endl;
        cout<<"No es posible ejecutar la aplicacion, saliendo..."<<endl;
        exit(EXIT_FAILURE);
    }
}

int main(){
    int option;
    Record record;
    Record temp;
    int cont;
    create_agenda();
    do{
        system("cls");
        cout<<"---Mi agenda persona---\n";
        cout<<"1. Crear nuevo contacto\n";
        cout<<"2. Modificar Existente\n";
        cout<<"3. Eliminar contacto\n";
        cout<<"4. Listar contactos\n";
        cout<<"5. Buscar contacto\n";
        cout<<"opcion: ";
        cin>>option;
        switch(option){
            case 1:
                cout<<"Ingrese los datos del contacto:\n";
                read_record_id(&record);
                if(read_first_by_id(record.id, &temp)){
                    cout<<"Id de contacto ya registrado."<<endl;
                }
                else{
                    read_record(&record);
                    save_new(&record);
                    cout<<"Contacto guardado exitosamente"<<endl;
                }
                system("pause");
                break;
            case 2:
                cout<<"Ingrese los datos solicitados para iniciar modificacion:\n";
                read_record_id(&record);
                if(read_first_by_id(record.id, &temp)){
                    cout<<"Ingrese los datos a modificar:\n";
                    read_record(&record);
                    modify_by_id(record.id, &record);
                    cout<<"Contacto modificado exitosamente."<<endl;
                }
                else{
                    cout<<"No hay contacto registrado con ese id."<<endl;
                }
                system("pause");
                break;
            case 3:
                cout<<"Ingrese los datos del contacto a eliminar:\n";
                read_record_id(&record);
                cont= remove_by_id(record.id);
                if(cont> 0){
                    cout<<"Contacto eliminado exitosamente."<<endl;
                }
                else{
                    cout<<"No hay contacto registrado con ese id."<<endl;
                }
                system("pause");
                break;
            case 4:
                cout<<"Mostrando el contenido de la agenda:\n";
                cont= print_all_records();
                if(cont>0){
                    cout<<cont<<" registros mostrados"<<endl;
                }
                else{
                    cout<<"Agenda vacia, no hay registros que mostrar."<<endl;
                }
                system("pause");
                break;
            case 5:
                cout<<"Ingrese el id del contacto a buscar:\n";
                read_record_id(&record);
                if(read_first_by_id(record.id, &record)){
                    cout<<"Contacto encontrado:\n";
                    print_record(&record);
                }
                else{
                    cout<<record.id<<" no se encuentra registrado."<<endl;
                }
                system("pause");
                break;
            case 0:
                cout<<"Saliendo agenda..."<<endl;
                break;
            default:
                cout<<"Opcion incorrecta, intente de nuevo:"<<endl;
                system("pause");
                break;
        }
    }while(option!= 0);
    return 0;
}
