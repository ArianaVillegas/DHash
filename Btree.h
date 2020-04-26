#ifndef BTREE_H
#define BTREE_H

#include <algorithm>
#include <vector>
#include "Nodos.h"

using namespace std;

template <typename ID>
class BTree {
    private:
        typedef typename vector<ID>::iterator keyIte;
        typedef typename vector<Node<ID>*>::iterator childIte;

        Node<T>* root;
        unsigned int degree;

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
            } else node->keys.insert(node->keys.begin()+i,key);
            if(node->keys.size()==degree){
                split(key,node);
                return true;
            }
            return false;
        }

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
};

#endif