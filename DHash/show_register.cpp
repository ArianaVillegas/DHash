#include<iostream> 
#include<pthread.h>
#include "DHash.h"
#include <string.h>
#include <unistd.h>
using namespace std;

int main(int argc, char** argv) {
    DHash<char*> fr("file.dat");
    char data[5];
    for(int i=0;i<5;i++){
        data[i]=argv[1][i];
    }
    auto f=fr.search(data);
    f.showData();



}