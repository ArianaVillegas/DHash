#include<iostream> 
#include<pthread.h>
#include "DHash.h"
#include <string.h>
#include <unistd.h>
using namespace std;

int main(int argc, char** argv) {
    DHash<char*> fr("file.dat");

    auto f=fr.search(argv[1]);
    f.showData();

}