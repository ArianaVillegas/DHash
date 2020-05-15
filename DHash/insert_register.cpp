#include<iostream> 
#include<pthread.h>
#include "DHash.h"
#include <string.h>
#include <unistd.h>
using namespace std;

int main(int argc, char** argv) {
    DHash<char*> fr("file.dat");
    Registro temp;
    string codigo=argv[1];
    string nombre=argv[2];
    string apellido=argv[3];
    string carrera= argv[4];
    strcpy(temp.codigo,codigo.c_str());
    strcpy(temp.Nombre,nombre.c_str());
    strcpy(temp.Apellidos,apellido.c_str());
    strcpy(temp.Carrera,carrera.c_str());
    fr.add(temp);



}