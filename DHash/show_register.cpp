#include<iostream> 
#include<pthread.h>
#include "DHash.h"
#include <string.h>
#include <unistd.h>
using namespace std;

int main(int argc, char** argv) {
    DHash<char*> fr("file.dat");
    auto f=fr.search(argv[1]);
    if(argc == 2){
    string a = f.codigo;
    if(a != "-1")
        f.showData();
    else
        cout << "Registro No encontrado";
    }
    else{
        f.showData(atoi(argv[2]));
    }
}