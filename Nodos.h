#ifndef NODO_H
#define NODO_H 
#define GRADO 3 //TAMANO DE HIJOS DE UN NODO
#define TAMANO_STRING 10
#include "Registro.h"
#include <string.h>
#include <vector>
#include <fstream>
#include <algorithm> 
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

struct STRING{
    char instance[TAMANO_STRING];
    
    void operator=(string second){
        copy(second.begin(),second.begin()+TAMANO_STRING-1,instance);
    }
    void print(){
        cout<<instance<<" ";
    }
};




template< typename ID> 
class Nodo {
    public:
    STRING childs[GRADO+1]; //tamaño igual a GRADO
    ID keys[GRADO]; //tamano = Grado-1
    bool isLeaf;
    int size;           // falta poner en el constructor 
    string position;
    Nodo ( bool isLeaf ) : isLeaf(isLeaf),size(0) {};
    void print_node(){
        for(int i=0;i<size;i++){
            cout<<" "<<keys[i];
        }
        cout<<endl;
        for(int i=0;i<size;i++){
            childs[i].print();
        }
        if(!isLeaf){
            childs[2].print(); 
        }        
        cout<<endl;
    }


    template<class>
    friend class BTree; 
};

/**
     * @param node the node you are trying to read
     * @param position the logical position you are trying to read 
     * */
template<typename ID>
void cargar_nodo(Nodo<ID> &node,int position){
    fstream pagina;
    pagina.open("nodos.txt",ios::binary|ios::in);
    pagina.seekg(position*sizeof(node),ios::beg);
    pagina.read((char *)&node,sizeof(node ));
    pagina.close();
}


/**
     * @param node the node you are trying to read
     * */
template<typename ID>
void escribir_nodo(Nodo<ID> &node){
    fstream pagina;
    pagina.open("nodos.txt",ios::binary|ios::app);
    pagina.write((char*) &node,sizeof(node) );
    pagina.close();
}

/*

*/

/**
     * @param node the node you are trying to write
     * @param pos the logical position you are trying to write 
     * */
template<typename ID>
void escribir_nodo(Nodo<ID> &node,int pos){
    fstream pagina;
    pagina.open("nodos.txt",ios::binary);
    pagina.seekp(pos*sizeof(node),ios::beg);
    pagina.write((char*) &node,sizeof(node) );
    pagina.close();
}


#endif 