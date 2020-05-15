#include<iostream> 
#include<pthread.h>
#include "DHash.h"
#include <string.h>
#include <unistd.h>

using namespace std;

DHash<char*> fr("file.dat");

void* transacion1 ( void * aux){
    string a =*(string*)aux; 
    fr.addFile(a);
    string r2 = "5H516";
    char r22[5];
    strcpy(r22,r2.c_str());
    auto f = fr.search(r22);
    f.showData();
    strcpy(f.Nombre, "Cesar");
    fr.add(f);

}

void* transacion2 ( void * aux){
    string a =*(string*)aux;
    sleep(2); 
    fr.addFile(a);
    string r1 = "TV5C2";
    char r12[5];
    strcpy(r12,r1.c_str());
    auto f = fr.search(r12);
    f.showData();
    sleep(2);
    string r2 = "3J6F3";
    char r22[5];
    strcpy(r22,r2.c_str());
    auto f2 = fr.search(r22);
    f2.showData();
    strcpy(f2.Carrera, "CS");
    fr.add(f2);

}

void* transacion3 ( void * aux){
    string a =*(string*)aux;
    sleep(3); 
    fr.addFile(a);
    sleep(3);
    string r2 = "3J6F3";
    char r22[5];
    strcpy(r22,r2.c_str());
    auto f = fr.search(r22);
    f.showData(); 
    string r1 = "v3135";
    char r12[5];
    strcpy(r12,r1.c_str());
    
    auto f2 = fr.search(r12);
    f2.showData(); 
    
}

int main(){ 
    pthread_t t[3];    
    string file1 = "../Datos/100000.txt";
    pthread_create(&t[0], NULL, transacion1, (void*)&file1);
    string file2 = "../Datos/10000.txt";
    pthread_create(&t[1], NULL, transacion2, (void*)&file2);
    string file3 = "../Datos/1000d.txt";
    pthread_create(&t[2], NULL, transacion3, (void*)&file3);
    pthread_join(t[0],NULL);
    pthread_join(t[1],NULL);
    pthread_join(t[2],NULL);

    return 0;
}