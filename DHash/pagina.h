#ifndef PAGINA_H
#define PAGINA_H
#include <iostream> 
#include <string>
#include <fstream>
#include "Registro.h"
#include <vector>
#define MAX_RECORDS 10
using namespace std; 

struct Pagina{
    int next=-1;
    int size=0;
    Registro registers[MAX_RECORDS];
};

#endif