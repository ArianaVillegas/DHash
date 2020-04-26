#ifndef NODO_H
#define NODO_H 
#define GRADO 3
#include "Registro.h"
#include <string>
#include <vector>
using namespace std; 


template <typename ID>
class BTree; 

template <typename ID>
class Node {
protected:
    vector<T> keys; //tamano = Grado-1
    bool isLeaf;
    
public: 
    Node(bool isLeaf) : isLeaf(isLeaf) {};
    
    
    template<class>
    friend class BTree; 
};
 
template<typename ID> 
class Nodo_normal: public: Node{
    vector<Node<ID>*> childs;
    
public:
    Nodo_normal( bool isLeaf ) :  Node(isLeaf) {};
    
    template<class>
    friend class BTree; 
};


template< typename ID> 
class Nodo_hoja: public: Node {
    vector <string> direccion_datos; //tamaño igual a GRADO
    public:

    Nodo_hoja ( bool isLeaf ) : Node(isLeaf) {};

    template<class>
    friend class BTree; 
};

#endif 