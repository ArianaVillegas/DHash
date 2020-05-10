#include "Nodos.h"
#include <iostream>
#include <string.h>

using namespace std; 

void execute(){


    Nodo<int> nodo(false);
    nodo.childs[0]="archivo1";
    nodo.childs[1]="archivo2";
    nodo.childs[2]="archivo3";
    nodo.keys[0]=1;
    nodo.keys[1]=2;
    nodo.size=2; 
    escribir_nodo(nodo);  
 
}
int main(){
   execute();
    cout<<"TERMINO EL EXECUTE"<<endl;
    Nodo<int> temp(true);
    cargar_nodo(temp,0);
    temp.print_node();   

}