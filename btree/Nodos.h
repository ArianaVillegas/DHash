#ifndef NODO_H
#define NODO_H 
#define GRADO 3 //TAMANO DE HIJOS DE UN NODO
#include <string.h>
#include <vector>
#include <fstream>
#include <algorithm> 
#include <stdio.h>
#include "STRING.h"
#include <unistd.h>
using namespace std; 



template< typename ID> 
class Node {
    public:
    STRING childs[GRADO+1]; //tamaño igual a GRADO (+1 de overflow)
    ID keys[GRADO]; //tamano = Grado-1(+1 de overflow)
    bool isLeaf;
    int size;           // falta poner en el constructor 
    int position;
    Node ( bool isLeaf ) : isLeaf(isLeaf),size(0),position(-1) {
        for(int i=0; i<GRADO; i++){
            if(i!=GRADO-1) keys[i] = "-1";
            childs[i] = "-1";
        }
    };
    Node ( ) : size(0),position(-1) {
        for(int i=0; i<GRADO; i++){
            if(i!=GRADO-1) keys[i] = "-1";
            childs[i] = "-1";
        }
    };
    void print_node(){
        cout << "Nodo:"<<position<<endl;
        cout<< "isLEAF: "<<int(isLeaf)<<endl;
        for(int i=0;i<size;i++){
            cout<<" "<<keys[i];
        }
        cout<<endl;
        cout << "Child: ";
        for(int i=0;i<size;i++){
            childs[i].print();
        }
        if (!isLeaf){
            childs[size].print();
        }
        cout<<endl;
        cout<<"SU SIZE ES: "<<size<<endl;
    }


    template<class>
    friend class BTree;

    void insert_keys(Node<ID> &second,int start,int end){
        int helper=0;
        for (int i=start;i<end;i++){
            second.keys[helper]=this->keys[i];
            helper++;
            second.size++;
        }

    }
    void erase_keys(int start,int end){
        size-=(end-start);
    }

    void insert_childs(Node<ID> &second,int start,int end){
        int helper=0;
        for (int i=start;i<end;i++){
            second.childs[helper]=this->childs[i];
            helper++;
        }
    }

};

/**
     * @param node the node you are trying to read
     * @param position the logical position you are trying to read 
     * */
template<typename ID>
bool cargar_nodo(Node<ID> &node,int position){
    fstream pagina;
    pagina.open("nodos.txt",ios::binary|ios::in );

    pagina.seekg(0,ios::end);
    int size=pagina.tellg();

    if(size==0){
        return false;
    }
    if (position<0){
        exit(28);
    }
    pagina.seekg(position*(sizeof(node)+1),ios::beg);
    pagina.read((char *)&node,sizeof(node ));
    pagina.close();
    return true;
}



template<typename ID>
void escribir_nodo(Node<ID> &node){
    cout << "escribir_nodo: node.position: " << node.position << endl;  
    if(node.position==-1){
        fstream pagina;
        cout<<"------------------"<<endl;
        node.print_node();
        cout<<"------------------"<<endl;
        pagina.open("nodos.txt",ios::binary|ios::app |ios::out);
        /*if (pagina.tellg()/(sizeof(Node<ID>)+1)==5){
            cout <<" SE DETUVO EN EL IF"<<endl;
            //sleep(25);
            //exit(22);
        }*/
        pagina.seekp(0,ios::end);
        node.position=pagina.tellp()/(sizeof(Node<ID>)+1);
        pagina.write((char*) &node,sizeof(Node<ID>) );
        pagina<<endl;
        pagina.close();
    }else{
        fstream pagina;
        node.print_node();
      //  cout << node.position*sizeof(node) << '\n';
        cout << "escribir_nodo():  Primer sleep" <<endl;
      //  sleep(5);
        pagina.open("nodos.txt");
        cout << "escribir_nodo():  Segundo sleep" <<endl;
     //   sleep(5);
        if (pagina.tellp()/(sizeof(Node<ID>)+1)==5){
            cout <<" SE DETUVO EN EL ELSE"<<endl;
            sleep(25);
        }
        pagina.seekp(node.position*(sizeof(Node<ID>)+1));
        cout << "escribir_nodo(): sizeof(node): " << sizeof(node) << endl;
        cout << "escribir_nodo(): sizeof(Node<ID>): " << sizeof(Node<ID>) << endl;
        cout << "escribir_nodo(): pagina.tellp(): " << pagina.tellp() << endl;
        cout << "escribir_nodo():  Tercer sleep" <<endl;
     //   sleep(5);
        pagina.write((char*) &node,sizeof(Node<ID>));
        pagina<<endl;
        pagina.close();
     }
}




#endif 