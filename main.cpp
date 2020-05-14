//
// Created by cesar21456 on 2020-05-11.
//
#include <iostream>
#include "Btree.h"
using namespace std;

typedef STRING char_t;

int main(){
    BTree<STRING> btree("nodos.txt");
    Registro<STRING> temporal;
    //strcpy(temporal.codigo,"1234");
    temporal.codigo="0000";
    strcpy(temporal.Apellidos,"Madera");
    strcpy(temporal.Nombre,"Cesar");
    strcpy(temporal.Carrera,"CS");
    btree.insert(temporal);
    for (int i=0;i< 30;i++ ){
        cout<<"--------------------------------------"<<endl;
        cout<<" SE ESTA INSERTANDO EL ELEMENTO "<< i<<endl;
        string crear_codigo="00";
        int codigo=i+1;
        if(i<9){
            crear_codigo+="0";
        }
        crear_codigo+=to_string(codigo);
        temporal.codigo=crear_codigo;
        btree.insert(temporal);

    }
    STRING zero;
    zero=0;
    btree.print_tree(zero);
    Node<STRING> GAA;
    cargar_nodo(GAA,6);
    GAA.print_node();
    cargar_nodo(GAA,5);
    GAA.print_node();


    /*
    Node<STRING> temporal1;
    cargar_nodo(temporal1,1);
    cout<<"VERIFICACION -----------------------------------------------------"<<endl;
    temporal1.print_node();

    temporal.codigo="0004";
    btree.insert(temporal);
    temporal.codigo="0005";
    btree.insert(temporal);
    temporal.codigo="0006";
    btree.insert(temporal);
    temporal.codigo="0007";
    btree.insert(temporal);
    temporal.codigo="0008";
    btree.insert(temporal);
    temporal.codigo="0009";
    btree.insert(temporal);
    temporal.codigo="0010";
    btree.insert(temporal);
    */


}