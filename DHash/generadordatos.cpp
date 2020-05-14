#include <iostream> 
#include <fstream> 
#include <time.h>
using namespace std;


int main(){
    fstream file;
    file.open("1000000.txt", ios::out);
    char key[5];
    char nombre[12];
    char apellido[20];
    char carrera[20];
    srand(time(NULL));
    for(int j = 0 ; j < 10000 ; j++){
        for(int i=0; i <= 4; i++){
            if(rand()%2== 0)
            key[i] = 65 + rand() % (90 - 65);
            else
            key[i] = 48 + rand() % (57 - 48);
            file << key[i];
        }
        file << "|";
        for(int i=0; i <= 11; i++){
            nombre[i] = (char) (65+ (rand()+65) % (90 - 65));  
            file << nombre[i];
        }
        file << "|";
        for(int i=0; i <= 19; i++){
            apellido[i] = 65 + (rand()+65 ) % (90 - 65);
        file << apellido[i];             
        }
        file << "|";
        for(int i=0; i <= 19; i++){
            carrera[i] = 65 + (rand()+65) % (90 - 65);            
            file << carrera[i]; 
        }
        file << "\n";
    }
}