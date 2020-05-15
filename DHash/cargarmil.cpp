#include <bits/stdc++.h>
#include "DHash.h"

using namespace std;

int main(){
    
    DHash<char*> fr("file.dat");
    fr.addFile("../Datos/1000d.txt");
    return 0;
}

