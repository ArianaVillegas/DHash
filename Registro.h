#ifndef REGISTRO_H
#define REGITRO_H
#include <iostream>
#include <string>
using namespace std; 


struct Registro
{
    char codigo[5];
	char Nombre[12] ;
	char Apellidos[20] ;
    char Carrera[20];
    /*Registro(){
        codigo.resize(5,32);
        Nombre.resize(12,32); 
        Apellidos.resize(20,32);
        Carrera.resize(20,32);
         
    }*/
    void show(){
        cout<<"codigo: "<<codigo<<" Nombre: "<<Nombre<<" Carrera : "<<Carrera<<endl;
    }    
};

#endif