#ifndef NODO_H
#define NODO_H 
#define GRADO 3 //TAMANO DE HIJOS DE UN NODO
#include "Registro.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std; 
/*

template <typename ID>
class BTree; 

template <typename ID>
class Node {

public: 
    vector<ID> keys; //tamano = Grado-1
    bool isLeaf;

    template<class>
    Node() = default;
    friend class BTree; 
};
 
template<typename ID> 
class Nodo_normal: public Node<ID>{
public:
    vector<string> childs;

    Nodo_normal( bool isLeaf ) :  isLeaf(isLeaf) {};
    
    template<class>
    friend class BTree; 
};
*/

template< typename ID> 
class Nodo {
    public:
    string childs[GRADO]; //tamaño igual a GRADO
    ID keys[GRADO-1]; //tamano = Grado-1
    bool isLeaf;
    int size;           // falta poner en el constructor 
    Nodo ( bool isLeaf ) : isLeaf(isLeaf),size(0) {};
    Nodo (string direccion,int pos ){
        fstream pagina;
        pagina.seekg(pos,ios::beg);
        

        pagina.open(direccion);

    }
    
    template<class>
    friend class BTree; 
};

template<typename ID>
void cargar_nodo(Nodo<ID> &node,int posicion){
    fstream pagina;
    pagina.open("nodos.txt");
    pagina.seekg(posicion,ios::beg);
    int tamano;
    pagina>>tamano;
    pagina.read((char *)&node,tamano);
}

template<typename ID>
void escribir_nodo(Nodo<ID> &node){
    fstream pagina;
    pagina.open("nodos.txt",ios::out | ios::app);
    pagina.write((char*) &node,sizeof(node) );
    
}


#endif 