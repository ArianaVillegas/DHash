#ifndef REGISTRO_H
#define REGITRO_H
#include <iostream>
#include <string>
using namespace std; 


struct Registro
{
    string  codigo;
	string  Nombre ;
	string  Apellidos ;
    string Carrera;
    Registro(){
        codigo.resize(5);
        Nombre.resize(12); 
        Apellidos.resize(20);
        Carrera.resize(20);
    }
    void show(){
        cout<<"codigo: "<<codigo<<" nombre: "<<" Nombre: "<<Nombre<<" Carrera "<<Carrera<<endl;
    }    
};

#endif