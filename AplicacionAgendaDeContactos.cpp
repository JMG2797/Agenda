#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <conio.h>

using namespace std;

const char DIR_ARCHIVO[] = "contactos.dat";

struct Contacto{
    char nombre[30];
    char apellido[45];
    char direccion[100];
    int edad;
    char correo[45];
    char telefono[10];
    char notas[250];
};
void ingresarContacto(Contacto c);
Contacto leerContacto();

bool existeContacto(char nombre[],char apellido[]);
Contacto buscarContacto(char nombre[],char apellido[]);

void mostrarContacto(Contacto c);

void listarContactos();

void eliminarContacto(char nombre[],char apellido[]);

void actualizarContacto(char nombre[],char apellido[]);

void menuIngresar();
void menuBuscar();
void menuListado();
void menuEliminar();
void menuActualizar();

int main(){
    /**/
    int op;
    do{
        system("cls");
        cout<<"\t\t\t\t\tAGENDA DE CONTACTOS"<<endl;
        cout<<"\t\t\t\tCrear contacto...............[1]"<<endl;
        cout<<"\t\t\t\tBuscar contacto..............[2]"<<endl;
        cout<<"\t\t\t\tLista de contactos...........[3]"<<endl;
        cout<<"\t\t\t\tEliminar contacto............[4]"<<endl;
        cout<<"\t\t\t\tActualizar contacto..........[5]"<<endl;
        cout<<"\t\t\t\tSALIR........................[6]"<<endl;
        cout<<"\t\t\t\tIngrese una opcion ->:";
        cin>>op;
        cin.ignore();
        switch(op){
            case 1 : system("cls");/** Clean Screen **/
                     menuIngresar();
                     break;
            case 2 : system("cls");
                     menuBuscar();
                     break;
            case 3 : system("cls");
                     menuListado();
                     break;
            case 4 : system("cls");
                     menuEliminar();
                     break;
            case 5 : system("cls");
                     menuActualizar();
                     break;
            case 6 : break;
            default: cout<<"\t\t\tOpcion incorrecta"<<endl;
        }
    }while(op!=6);
    return 0;
}

void ingresarContacto(Contacto c){
    ofstream salida;
    /**/
    salida.open(DIR_ARCHIVO,ios::binary | ios::app);
    salida.write((char*)&c,sizeof(Contacto));
    salida.close();
}

Contacto leerContacto(){
    Contacto c;
    cout<<"\t\t\tNOMBRE   : ";
    cin.getline(c.nombre,30);
    cout<<"\t\t\tAPELLIDO : ";
    cin.getline(c.apellido,45);
    cout<<"\t\t\tDIRECCION : ";
    cin.getline(c.direccion,100);
    cout<<"\t\t\tEDAD     : ";
    cin>>c.edad;
    cin.ignore();
    cout<<"\t\t\tCORREO   : ";
    cin.getline(c.correo,45);
    cout<<"\t\t\tTELEFONO   : ";
    cin.getline(c.telefono,10);
    cout<<"\t\t\tNOTAS   : ";
    cin.getline(c.notas,250);
    return c;
}

bool existeContacto(char nombre[],char apellido[]){

    Contacto c;
    ifstream entrada;
    entrada.open(DIR_ARCHIVO,ios::binary);

    if(entrada.good()){
        while(entrada.read((char*)&c,sizeof(Contacto))){
            if(strcmp(nombre,c.nombre)==0 && strcmp(apellido,c.apellido)==0){
                entrada.close();
                return true;
            }
        }

        entrada.close();
        return false;
    }

    else{
        entrada.close();
        return false;
    }
}

Contacto buscarContacto(char nombre[],char apellido[]){
    Contacto c;
    ifstream entrada;
    entrada.open(DIR_ARCHIVO,ios::binary);

    if(entrada.good()){

        while(entrada.read((char*)&c,sizeof(Contacto))){
            if(strcmp(nombre,c.nombre)==0 && strcmp(apellido,c.apellido)==0){
                entrada.close();
                return c;
            }
        }
    }
}
void mostrarContacto(Contacto c){
    cout<<endl;
    cout<<"\t\t\t NOMBRE    : "<<c.nombre<<endl;
    cout<<"\t\t\t APELLIDO  : "<<c.apellido<<endl;
    cout<<"\t\t\t DIRECCION : "<<c.direccion<<endl;
    cout<<"\t\t\t EDAD      : "<<c.edad<<endl;
    cout<<"\t\t\t CORREO    : "<<c.correo<<endl;
    cout<<"\t\t\t TELEFONO  : "<<c.telefono<<endl;
    cout<<"\t\t\t NOTAS     : "<<c.notas<<endl;
    cout<<"Presione cualquier tecla para salir"<<endl;
    cout<<endl;
}

void listarContactos(){
    ifstream entrada;
    entrada.open(DIR_ARCHIVO,ios::binary);
    Contacto c;
    if(entrada.good()){
        while(entrada.read((char*)&c,sizeof(Contacto))){
            mostrarContacto(c);
        }

    }
    else{
        cout<<"No se puede leer el archivo"<<endl;
    }
    entrada.close();
}

void eliminarContacto(char nombre[],char apellido[]){
    ifstream entrada;
    ofstream temporal;
    entrada.open(DIR_ARCHIVO,ios::binary);
    temporal.open("temp.dat",ios::binary);
    Contacto c;
    if(entrada.good()){
        while(entrada.read((char*)&c,sizeof(Contacto))){
            if(strcmp(nombre,c.nombre)!=0 || strcmp(apellido,c.apellido)!=0){
                temporal.write((char*)&c,sizeof(Contacto));
            }
        }
    }
    entrada.close();
    temporal.close();
    remove(DIR_ARCHIVO);
    rename("temp.dat",DIR_ARCHIVO);
}

void actualizarContacto(char nombre[],char apellido[]){
    ifstream entrada;
    ofstream temporal;
    entrada.open(DIR_ARCHIVO,ios::binary);
    temporal.open("temp.dat",ios::binary);
    Contacto c;

    if(entrada.good()){
        while(entrada.read((char*)&c,sizeof(Contacto))){
            if(strcmp(nombre,c.nombre)==0 && strcmp(apellido,c.apellido)==0){
                Contacto actualizado = leerContacto();
                temporal.write((char*)&actualizado,sizeof(Contacto));
            }
            else{
                temporal.write((char*)&c,sizeof(Contacto));
            }
        }
    }

    entrada.close();
    temporal.close();
    remove(DIR_ARCHIVO);
    rename("temp.dat",DIR_ARCHIVO);
}

void menuIngresar(){

    cout<<"\t\t\t\tINGRESO DE NUEVO CONTACTO"<<endl;
    Contacto nuevo = leerContacto();
    ingresarContacto(nuevo);
    cout<<"\t\t\tContacto agregado con exito"<<endl;
}

void menuBuscar(){
    cout<<"\t\t\t\tBUSCAR CONTACTO"<<endl;
    char nombre[30],apellido[45];
    cout<<"\t\t\tIngrese los datos de busqueda:"<<endl;
    cout<<"\t\t\tNOMBRE   : ";
    cin.getline(nombre,30);
    cout<<"\t\t\tAPELLIDO: ";
    cin.getline(apellido,45);
    if(existeContacto(nombre,apellido)){
        Contacto buscado = buscarContacto(nombre,apellido);
        mostrarContacto(buscado);
    }
    else{
        cout<<"\t\t\tNo se ha encontrado el contacto"<<endl;
    }
}

void menuListado(){
    cout<<"\t\t\t\tLISTA DE CONTACTOS"<<endl;
    listarContactos();
    getch();/**obtener caracter**/
}

void menuEliminar(){
    cout<<"\t\t\t\tELIMINAR CONTACTO"<<endl;
    char nombre[30],apellido[45];
    cout<<"\t\t\tIngrese el contacto que quiera eliminar:"<<endl;
    cout<<"\t\t\tNOMBRE   : ";
    cin.getline(nombre,30);
    cout<<"\t\t\tAPELLIDO: ";
    cin.getline(apellido,45);
    if(existeContacto(nombre,apellido)){
        Contacto eliminar = buscarContacto(nombre,apellido);
        int op;
        cout<<"\t\t\t ¿Seguro que desea eliminar el siguiente contacto?";
        mostrarContacto(eliminar);
        do{
            cout<<"\t\t\tSI[1]....NO[2]:";
            cin>>op;
            switch(op){
                case 1: eliminarContacto(nombre,apellido);
                        cout<<"\t\t\tSe ha eliminado el contacto"<<endl;
                        break;
                case 2: break;
                default: cout<<"\t\t\tOPCION INCORRECTA"<<endl;
            }
        }while(op!=1 && op!=2);
    }
    else{
        cout<<"\t\t\tNO EXISTE EL CONTACTO"<<endl;
    }
}
void menuActualizar(){
    cout<<"\t\t\t\tACTUALIZAR CONTACTO"<<endl;
    char nombre[30],apellido[45];
    cout<<"\t\t\tIngrese el contacto que quiera actualizar:"<<endl;
    cout<<"\t\t\tNOMBRE   : ";
    cin.getline(nombre,30);
    cout<<"\t\t\tAPELLIDO: ";
    cin.getline(apellido,45);
    if(existeContacto(nombre,apellido)){
        Contacto buscado = buscarContacto(nombre,apellido);
        cout<<"\t\t\tContacto:"<<endl;
        mostrarContacto(buscado);
        actualizarContacto(nombre,apellido);
        cout<<"\t\t\tCONTACTO ACTUALIZADO"<<endl;
    }
    else{
        cout<<"\t\t\tNO EXISTE EL CONTACTO"<<endl;
    }
}
