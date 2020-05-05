#ifndef BTREE_H
#define BTREE_H

#include <algorithm>
#include <vector>
#include "Nodos.h"
#include "Registro.h"
using namespace std;

template <typename ID>
class BTree {
    private:
        typedef typename vector<ID>::iterator keyIte;
        typedef typename vector<Node<ID>*>::iterator childIte;

        Node<ID>* root;
        unsigned int degree;
        /* ORIGINAL */ 
        bool find(ID key, Node<ID>* &node, int &i){
            while(node){
                for(i=0; i<node->keys.size(); ++i) {
                    if(key==node->keys[i]) return true;
                    else if(key<node->keys[i]) break;
                }
                if(!node->isLeaf) node = node->childs[i];
                else node = 0;
            }
            return false;
        }


        /* Copia */
        bool find(ID key, string nodeDir, int &i){
            Nodo node = read(nodeDir); /*TO DO*/
            while(!node->isLeaf){
                for(i=0; i<node->keys.size(); ++i) {
                    if(key==node->keys[i]) return true;
                    else if(key<node->keys[i]) break;
                }
                node = read(node->childs[i]); /*TO DO X2*/
            }
            return false;
        }

        
        void insKeys(Node<ID>* &node1, Node<ID>* &node2, int pos){
            node1->keys.insert(node1->keys.begin(),node2->keys.begin()+pos+1,node2->keys.end());
            node2->keys.erase(node2->keys.begin()+pos,node2->keys.end());
        }

        void insChilds(Node<ID>* &node1, Node<ID>* &node2, int pos){
            node1->childs.insert(node1->childs.begin(),node2->childs.begin()+pos+1,node2->childs.end());
            node2->childs.erase(node2->childs.begin()+pos+1,node2->childs.end());
        }

        void split(T &key, Node<ID>* &node){
            auto pos = degree/2;
            key = node->keys[pos];
            Node<T>* newNode = new Node<ID>(degree,node->isLeaf); 
            insKeys(newNode,node,pos);
            if(!node->isLeaf) {
                insChilds(newNode,node,pos);
            }
            node = newNode;
        }        

        /* ORIGINAL */
        bool insert(ID &key, Node<ID>* &node){
            int i;
            ID actual;
            for(i=0; i<node->keys.size(); ++i)
                if(key<=node->keys[i]) break;
            if(!node->isLeaf){
                auto temp = node->childs[i];
                if(insert(key,temp)){
                    node->keys.insert(node->keys.begin()+i,key);
                    node->childs.insert(node->childs.begin()+i+1,temp);
                }
            } 
            //Revisar si es que el nodo tiene ya un tamaño maximo antes de insertar el nuevo registro 
            else node->keys.insert(node->keys.begin()+i,key);
            if(node->keys.size()==degree){
                split(key,node);
                return true;
            }
            return false;
        }
        /* COPY */ 
        bool insert(Record record, ID &key, string node){
            /* Cargamos nodo */ 
            Nodo <ID> nodo;
            cagar_nodo(nodo, stoi(node));
            
            /* Buscamos la posicion a seguir en los nodos */
            int i;  
            for (i = 0; i < nodo.size; i++)
                if(key<=node.keys[i]) break;

            /* Preguntar si es hoja */
            if(!node.isLeaf){
                
            }else{
                Pagina page = loadPage(node.childs[i]); /* TO DO */
                if(page.size==MAX_RECORDS){
                    Pagina newpage;
                    page.All_registers.push_back(record);
                    page.sort();    /* TO DO */
                    newpage.All_registers.insert(page.All_registers.begin() + MAX_RECORDS/2, page.All_registers.end());
                    page.All_registers.remove(page.All_registers.begin() + MAX_RECORDS/2, page.All_registers.end());
                    
                    if(node.size == GRADO){
                        // Falta revisar
                        /*Node newnode;
                        split(newnode, node);  TO DO (actualizar keys y size) 
                        if(key < newnode.keys[0]){
                            node.keys[node.size] = key;
                            sort(node.keys.begin(),node.keys.end());
                            node.childs[node.size++] = newpage.name;
                        }else{
                            newnode.keys[newnode.size] = key;
                            sort(newnode.keys.begin(),newnode.keys.end());
                            newnode.childs[newnode.size++] = newpage.name;
                        }*/
                    }else{
                        for(int pos = node.size; pos>i; pos--){
                            node.keys[pos] = node.keys[pos-1];
                            node.childs[pos] = node.childs[pos-1];
                        }
                        node.keys[i] = newpage.All_registers[0].key;
                        node.childs[i] = newpage.name; 
                        node.size++;
                    }
                    page.write();
                    newpage.write();
                }else{
                    page.All_registers.push_back(record);
                    page.sort();    /* TO DO */
                }
                page.write(); /* TO DO */
            }
        }

    

        /* algoritmos a insertar un registro en pagina 
        si no esta lleno, se pone en heap
        si esta lleno, se ordena y se parte en 2 paginas, mitad ordenado en la pagina original y mitad ordenado en la siguiente pagina
        y se crea un mini nodo 
        En el caso de los nodos hoja, la cantidad de childs es lo mismo que la cantidad de keys 

        
        */
        /*pasos



        1- Se recibe el string direccion del root
        2- Se carga el nodo
        3- Ubicar donde se tiene que insertar
        4- preguntar si es hoja
        5- SI NO ES HOJA: 
        5.1- Insertar con el string de n' child, y el key 
        6- SI ES HOJA:
        6.1- Cargar pagina
        6.2 PREGUNTAR POR EL SIZE DEL PAGE
        6.3- Si es que la pagina AUN NO SE LLENA, se inserta en esa pagina
        




        */

        void findMaxLeft(Node<ID>* &node){
            while(!node->isLeaf)
                node=node->childs.back();
        }

        void traverseInOrder(Node<ID>* node) {
            int i;
            for(i=0; i<node->keys.size(); ++i){
                if(!node->isLeaf) traverseInOrder(node->childs[i]);
                cout << node->keys[i] << ' ';
            }
            if(!node->isLeaf) traverseInOrder(node->childs[i]);
        }

        void deleteAll(Node<ID>* node){
            int i;
            for(i=0; i<node->keys.size(); ++i){
                if(!node->isLeaf) deleteAll(node->childs[i]);
            }
        }

    public:
        BTree(unsigned int degree) : degree(degree), root(nullptr) {
            root = new Node<ID>(degree);
        }

        bool search(ID k) { 
            auto temp = root; int i;
            find(k,temp,i);
        } 

        bool insert(ID k) {
            auto temp = root;
            if(insert(k,temp)){
                Node<T>* newNode = new Node<T>(degree,false);
                newNode->keys.push_back(k);
                newNode->childs.push_back(root);
                newNode->childs.push_back(temp);
                temp = newNode;
            }
            root = temp;
            return true;
        }

        /*copia*/
        bool insert(Registro registro) {
            auto temp = root;
            if(insert(k,temp)){
                Node<T>* newNode = new Node<T>(degree,false);
                newNode->keys.push_back(k);
                newNode->childs.push_back(root);
                newNode->childs.push_back(temp);
                temp = newNode;
            }
            root = temp;
            return true;
        }
        
};

#endif