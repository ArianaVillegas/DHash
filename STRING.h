//
// Created by cesar21456 on 2020-05-12.
//

#ifndef PROYECTOBD2_STRING_H
#define PROYECTOBD2_STRING_H
#define TAMANO_STRING 10
#include <iostream>
using namespace std;


struct STRING{
    char instance[TAMANO_STRING];

    void operator=(string second){
        //copy(second.begin(),second.begin()+TAMANO_STRING-1,instance);
        
        strcpy(instance,second.c_str());
    }
    void operator=(int second){
        snprintf(instance,sizeof(instance),"%d",second);
    }
    void print(){
        cout<<instance<<" ";
    }
    int STOI(){
        int retorno;
        return  sscanf(instance,"%d ",&retorno );
    }
    string to_string(){
        string temporal=instance;
        return temporal;
    }
    STRING(){
        strcpy(instance, "        ");
    }
};

bool operator <(STRING first,STRING second ){
    return (first.instance<second.instance);
}

ostream& operator<<(ostream& os, const STRING& dt)
{
    os << dt.instance;
    return os;
}



#endif //PROYECTOBD2_STRING_H
