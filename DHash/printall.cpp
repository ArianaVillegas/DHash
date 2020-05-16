#include <bits/stdc++.h>
#include "DHash.h"

using namespace std;

int main(int argc, char** argv){
    
    DHash<char*> fr("file.dat");
    int mode = atoi(argv[1]);
    fr.printall(mode);
    return 0;
}

