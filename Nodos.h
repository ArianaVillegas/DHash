#ifndef NODO_H
#define NODO_H 
#define GRADO 3
#include "Registro.h"
#include <string>
#include <vector>
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
    vector <string> childs; //tamaño igual a GRADO
    vector<ID> keys; //tamano = Grado-1
    bool isLeaf;

    Nodo ( bool isLeaf ) : isLeaf(isLeaf) {};

    template<class>
    friend class BTree; 
};

#endif 