#ifndef REGISTRO_H
#define REGITRO_H
#include <bits/stdc++.h>
using namespace std; 

struct Registro
{
    char codigo[5] = { };
	char Nombre[12] = { };
	char Apellidos[20] = { };
    char Carrera[20] = { };
    Registro(){};
    Registro(char* _cod, char* _nombre, char* _apellido ,char* _carrera){
        strncpy(codigo, _cod, 5);
        strncpy(Nombre, _nombre, 12);
        strncpy(Apellidos, _apellido, 20);
        strncpy(Carrera, _carrera, 20);
    };
    void setData(){
        string line;
        cin.ignore();
        cout << "\nCodigo: ";
        getline(cin,line);
        strncpy(codigo, line.c_str(), 5);
        cout << "Nombre: ";
        getline(cin,line);
        strncpy(Nombre, line.c_str(), 12);
        cout << "Apellidos: ";
        getline(cin,line);
        strncpy(Apellidos, line.c_str(), 20);
        cout << "Carrera: ";
        getline(cin,line);
        strncpy(Carrera, line.c_str(), 20);
    };
    void showData(){
        cout << "\nCodigo: ";
        string cod = codigo;
        string nomb = Nombre;
        string ap = Apellidos;
        string Carre = Carrera;
        cout << cod;
        cout << "\nNombre: ";
        cout << nomb;
        cout << "\nApellidos: ";
        cout << ap;
        cout << "\nCarrera: ";
        cout << Carre;
        cout << "\n----------------\n";    
        };
};

#endif