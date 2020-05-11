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
        string pos_root;
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
            while(!node.isLeaf){
                for(i=0; i<node.keys.size(); ++i) {
                    if(key==node.keys[i]) return true;
                    else if(key<node.keys[i]) break;
                }
                node = read(node.childs[i]); /*TO DO X2*/
            }
            return false;
        }

        
        void insKeys(Node<ID>* &node1, Node<ID>* &node2, int pos){
            node1->keys.insert(node1->keys.begin(),node2->keys.begin()+pos+1,node2->keys.end());
            node2->keys.erase(node2->keys.begin()pos,node2->keys.end());
        }

        void insChilds(Node<ID>* &node1, Node<ID>* &node2, int pos){
            node1->childs.insert(node1->childs.begin(),node2->childs.begin()+pos+1,node2->childs.end());
            node2->childs.erase(node2->childs.begin()+pos+1,node2->childs.end());
        }

        /* Original */
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

        /* Split leaf */
        void splitLeaf(ID &key, Node<ID> &node){
            auto pos = GRADO/2;
            key = node.keys[pos];
            Node<ID> newnode = new Node<ID>(true);
            newnode.keys.insert(newnode.keys.begin(), node.keys.begin()+pos, node.keys.end());
            node.keys.erase(node.keys.begin()+pos, node.keys.end());
            if(!node.isLeaf){
                newnode.childs.insert(newnode.childs.begin(), node.childs.begin()+pos, node.childs.end());
                node.childs.erase(node.childs.begin()+pos, node.childs.end());
                node.childs[GRADO-1] = newnode.childs[0];
            }
            node.write();
            newnode.write();
            node = newnode;
        }       

        /* Split */
        void split(ID &key, Node<ID> &node){
            auto pos = GRADO/2;
            key = node.keys[pos];
            Node<ID> newnode = new Node<ID>(false);
            newnode.keys.insert(newnode.keys.begin(), node.keys.begin()+pos, node.keys.end());
            node.keys.erase(node.keys.begin()+pos, node.keys.end());
            if(!node.isLeaf){
                newnode.children.insert(newnode.children.begin(), node.children.begin()+pos+1, node.children.end());
                node.children.erase(node.children.begin()+pos+1, node.children.end());
            }
            node.write();
            newnode.write();
            node = newnode;
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
        bool insert(Record record, ID &key, Nodo &nodo){
            /* Buscamos la posicion a seguir en los nodos */
            int i;  
            for (i = 0; i < nodo.size; i++)
                if(key<=nodo.keys[i]) break;

            /* Preguntar si es hoja */
            if(!nodo.isLeaf){
                string tnode = nodo.childs[i];
                Nodo <ID> tnodo;
                cagar_nodo(tnodo, stoi(tnode));
                if(insert(record, key, tnodo)){
                    for(int pos = tnodo.size; pos>i; pos--){
                        tnodo.keys[pos] = tnodo.keys[pos-1];
                        tnodo.childs[pos+1] = tnodo.childs[pos];
                    }
                    tnodo.keys[i] = newpage.All_registers[0].key;
                    tnodo.childs[i+1] = newpage.name; 
                    tnodo.size++;
                }
            }else{
                Pagina page = loadPage(node.childs[i]); /* TO DO */
                if(page.size==MAX_RECORDS){
                    /*  Insertamos en el registro en la pagina y lo separamos en dos  */
                    Pagina newpage;
                    page.All_registers.push_back(record);
                    page.sort();    /* TO DO */
                    newpage.All_registers.insert(page.All_registers.begin() + MAX_RECORDS/2, page.All_registers.end());
                    page.All_registers.remove(page.All_registers.begin() + MAX_RECORDS/2, page.All_registers.end());
                    
                    /* Hace que los keys apuntan a su respectiva pagina */ 
                    for(int pos = nodo.size; pos>i; pos--){
                        nodo.keys[pos] = nodo.keys[pos-1];
                        nodo.childs[pos] = nodo.childs[pos-1];
                    }
                    nodo.keys[i] = newpage.All_registers[0].key;
                    nodo.childs[i] = newpage.name; 
                    nodo.size++;

                    node.write();
                    
                    page.write();
                    newpage.write();
                }else{
                    page.All_registers.push_back(record);
                    page.sort();    /* TO DO */
                }
                page.write(); /* TO DO */
            }

            if(nodo.keys.size == GRADO){
                if(nodo.isLeaf) splitLeft(key,nodo);
                else split(key,nodo);
                return true;
            }
            return false;
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
        BTree(string index_fileName) {
            fstream file;
            file.open(index_fileName, ios::in);
            if(file.is_open())
                pos_root = "0";
            else
                pos_root = "";
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
            auto temp =  read(pos_root);
            if(insert(registro,registro.codigo,temp)){
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