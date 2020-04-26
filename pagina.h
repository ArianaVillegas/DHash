#ifndef PAGINA_H
#define PAGINA_H
#include <iostream> 
#include <string>
#include "Registro.h"
#include <vector>
using namespace std; 

struct Pagina{
    int size; 
    vector<Registro> All_registers;
    string puntero_siguiente;


};














#endif