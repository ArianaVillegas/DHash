#ifndef BTREE_H
#define BTREE_H

#include <algorithm>
#include <vector>
#include "Nodos.h"
#include "pagina.h"
#include <stdio.h>


using namespace std;

template <typename ID>
class BTree {
    private:
        typedef typename vector<ID>::iterator keyIte;
        typedef typename vector<Node<ID>*>::iterator childIte;
        string pos_root;
        unsigned int degree;

        /* ORIGINAL */ 
        /*bool find(ID key, Node<ID>* &node, int &i){
            while(node){
                for(i=0; i<node->keys.size(); ++i) {
                    if(key==node->keys[i]) return true;
                    else ifMadera(key<node->keys[i]) break;
                }
                if(!node->isLeaf) node = node->childs[i];
                else node = 0;
            }
            return false;
        }
         */

        /* Copia */
        bool find(ID key, string nodeDir, int &i){
            Node<ID> node;
             cargar_nodo(node,nodeDir); /*TO DO*/
            while(!node.isLeaf){
                for(i=0; i<node.keys.size(); ++i) {
                    if(key==node.keys[i]) return true;
                    else if(key<node.keys[i]) break;
                }
                cargar_nodo(node,node.childs[i].STOI()); /*TO DO X2*/
            }
            return false;
        }

        /*
        void insKeys(Node<ID>* &node1, Node<ID>* &node2, int pos){
            node1->keys.insert(node1->keys.begin(),node2->keys.begin()+pos+1,node2->keys.end());
            node2->keys.erase(node2->keys.begin()+pos,node2->keys.end());
        }

        void insChilds(Node<ID>* &node1, Node<ID>* &node2, int pos){
            node1->childs.insert(node1->childs.begin(),node2->childs.begin()+pos+1,node2->childs.end());
            node2->childs.erase(node2->childs.begin()+pos+1,node2->childs.end());
        }
*/
        /* Original */
        /*void split(T &key, Node<ID>* &node){
            auto pos = degree/2;
            key = node->keys[pos];
            Node<ID>* newNode = new Node<ID>(degree,node->isLeaf); 
            insKeys(newNode,node,pos);
            if(!node->isLeaf) {
                insChilds(newNode,node,pos);
            }
            node = newNode;
        } */

        /* Split leaf */
        void splitLeaf(ID &key, Node<ID>* &node){
            cout<<" SE ESTA SPLITEANDO con size: "<<node->size<<endl;
            int pos = GRADO/2;
            key = node->keys[pos];
            Node<ID>* newnode = new Node<ID>(true);
            //newnode.keys.insert(newnode.keys.begin(), node.keys.begin()+pos, node.keys.end());
            node->insert_keys(*newnode,pos,node->size);
            int size_temporal=node->size;
            //node.keys.erase(node.keys.begin()+pos, node.keys.end());
            node->erase_keys(pos,node->size);



                //newnode.childs.insert(newnode.childs.begin(), node.childs.begin()+pos, node.childs.end());
                node->insert_childs(*newnode,pos,size_temporal);
                //node.childs.erase(node.childs.begin()+pos, node.childs.end());
                //*no pongo nada aca porque se supone que lo hace el erase de arriba
                node->childs[GRADO-1] = newnode->childs[0];


            escribir_nodo(*node);
            //node.write();
            escribir_nodo(*newnode);
            //newnode.write();
            node->print_node();
            newnode->print_node();
            node = newnode;
        }       

        /* Split */
        void split(ID &key, Node<ID>* &node){
            int pos = GRADO/2;
            key = node->keys[pos];
            Node<ID>* newnode = new Node<ID>(false);
            //newnode.keys.insert(newnode.keys.begin(), node.keys.begin()+pos, node.keys.end());
            node->insert_keys(*newnode,pos+1/*pos*/,node->size);
            //node.keys.erase(node.keys.begin()+pos, node.keys.end());
            int size_temporal=node->size;
            node->erase_keys(pos,node->size);


                //newnode.childs.insert(newnode.childs.begin(), node.childs.begin()+pos+1, node.childs.end());
                node->insert_childs(*newnode,pos/*pos+1*/,size_temporal);
                //node.childs.erase(node.childs.begin()+pos+1, node.childs.end());
                //no pongo nada porque se supone que el erase lo hace


            escribir_nodo(*node);
            //node.write();
            escribir_nodo(*newnode);
            //newnode.write();
            node = newnode;
        }       

        
        /* ORIGINAL */
      /*  bool insert(ID &key, Node<ID>* &node){
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
        } */

        /* COPY */ 
        bool insert(Registro<ID> record, ID &key, Node<ID>* &nodo){
            /* Buscamos la posicion a seguir en los nodos */
            int i=0;
            for (i = 0; i < nodo->size; i++)
                if(key<nodo->keys[i]) break;

            /* Preguntar si es hoja */
            Pagina newpage;
            if(!nodo->isLeaf){
                string tnode = nodo->childs[i].to_string();
                Node <ID> tnodo;
                /*IMPORTANTE*/
                cargar_nodo(tnodo, stoi(tnode));
                Node<ID>* ptnodo = &tnodo;
                if(insert(record, key, ptnodo)){
                    for(int pos = ptnodo->size; pos>i; pos--){
                        nodo->keys[pos] = nodo->keys[pos-1];
                        nodo->childs[pos+1] = nodo->childs[pos];
                    }
                    nodo->keys[i] = key;
                    /*Arreglar error de asignación*/

                    STRING ss;
                    ss= ptnodo->position;
                    nodo->childs[i+1] = ss; 
                    nodo->size++;
                    escribir_nodo(*nodo);
                }
            }else{
                Pagina page(nodo->childs[i-1].to_string()); /* TO DO */
                if(page.size()==MAX_RECORDS){
                    /*  Insertamos en el registro en la pagina y lo separamos en dos  */
                    page.All_registers.push_back(record);
                    page.sort();    /* TO DO */
                    newpage.All_registers.insert(newpage.All_registers.begin(),page.All_registers.begin() + MAX_RECORDS/2, page.All_registers.end());
                    page.All_registers.erase(page.All_registers.begin() + MAX_RECORDS/2, page.All_registers.end());
                    newpage.setName();
                    /* Hace que los keys apuntan a su respectiva pagina */ 
                    for(int pos = nodo->size; pos>i; pos--){
                        nodo->keys[pos] = nodo->keys[pos-1];
                        nodo->childs[pos] = nodo->childs[pos-1];
                    }
                    nodo->keys[i] = newpage.All_registers[0].codigo;
                    nodo->childs[i] = newpage.name; 
                    nodo->size++;
                    escribir_nodo(*nodo);
                    //nodo.write();
                    page.write();
                    newpage.write();
                }else{
                    page.All_registers.push_back(record);
                    page.sort();
                    page.write(); /* TO DO */
                }
                /* TO DO */
            }

            if(nodo->size == GRADO){
                if(nodo->isLeaf) splitLeaf(key,nodo);
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

        void print_tree(STRING abc){
            Node<ID> root;
            cout<<" POS_ROOT.STOI(): "<<abc.STOI()<<endl;
            cargar_nodo(root,abc.STOI());
            root.print_node();
            if(root.isLeaf){
                return;
            }
            for(int i=0;i<root.size+1;i++){
                print_tree(root.childs[i]);
            }

        }

        BTree(string index_fileName) {
            fstream file;
            file.open(index_fileName, ios::in |ios::out | ios::app);
            file.seekg(0,ios::end);
            int pos=file.tellg();
            if (pos==0){
                pos_root="";
            }else {
                pos_root = "0";
            }
            file.close();
        }

        bool search(ID k) { 
            auto temp = pos_root; int i;
            find(k,temp,i);
        } 

        /*original*/
        /*bool insert(ID k) {
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
        }*/

        /*copia*/
        bool insert(Registro<ID> registro) {
            cout << "--------------------------------------------" << endl;
            cout << "\t insert registro: " << registro.codigo << endl;

            Node<ID> temp(false);
            if (pos_root==""){
                pos_root="0";
                Node<ID> newroot(true);
                newroot.position=0;
                newroot.size++;
                Pagina first_page;
                first_page.All_registers.push_back(registro);
                first_page.setName();
                newroot.keys[0]=registro.codigo;
                newroot.childs[0]=first_page.name;
                escribir_nodo(newroot);
                first_page.write();
                return true;
            }
            cargar_nodo(temp,stoi(pos_root));//este pos__root es "" por lo que el stoi manda F
            Node<ID>* ptemp = &temp;
            temp.print_node();
            ID codigo_registro =registro.codigo;
            if(insert(registro,codigo_registro,ptemp)){

                Node<ID> newNode(false);
                Node<ID> check;
                newNode = check;
                cargar_nodo(check,0);
                check.position=-1;
                escribir_nodo(check);

                newNode.isLeaf=0;
                newNode.position=0;
                newNode.keys[0]=codigo_registro;
                newNode.childs[0]=check.position;
 
                newNode.childs[1]=ptemp->position;
                newNode.size++;
      //          newNode.print_node();
                /*Aqui esta el problema*/
                cout << "insert(): newNode.position: " << newNode.position << endl;
                escribir_nodo(newNode);
            }
            
            return true;
        }
        
};

#endif