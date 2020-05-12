#ifndef PAGINA_H
#define PAGINA_H
#include <iostream> 
#include <string>
#include <fstream>
#include "Registro.h"
#include <vector>
#define MAX_RECORDS 10
using namespace std; 

void swap(Registro* a, Registro* b)  
{  
    Registro t = *a;  
    *a = *b;  
    *b = t;  
}  
int partition (vector<Registro> &arr, int low, int high)  
{  
    int pivot = stoi(arr[high].codigo); 
    int i = (low - 1); 
  
    for (int j = low; j <= high - 1; j++)  
    {  
        if (stoi(arr[j].codigo) < pivot)  
        {  
            i++; 
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  
void quickSort(vector <Registro>  &arr, int low, int high)  
{  
    if (low < high)  
    {  
        int pi = partition(arr, low, high);  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}  

istream & operator >> (istream & stream, Registro & record)
{	   
    stream.read((char *) &record, sizeof(record));
    string bufer;
    getline(stream,bufer);
    return stream;  
}

struct Pagina{
    int size; 
    string name;  //to define 
    vector<Registro> All_registers;
    string puntero_siguiente;

    void sort(){
        quickSort(All_registers,0,All_registers.size()-1);
    }
    void setName(){
        name = All_registers[0].codigo;
        name +=  ".txt"; 
    }
    void write(){
        fstream file;
        file.open(name,ios::out| ios::binary);
        for( int i = 0 ; i  < All_registers.size() ; i++){
            file.write((char*) &All_registers[i] , sizeof(All_registers[i]));
            file << endl;
        }
        file.close();
    };

    Pagina(string fileName): name{fileName} {
        loadPage(fileName);
    }; 
    Pagina(): name{""} {  
    }; 
    void loadPage(string fileName){
        fstream file;
        file.open(fileName, ios::in | ios::binary);
        Registro buffer;
        string bug;
        while(file >> buffer){  
            cout << file.tellg() << endl; 
            All_registers.push_back(buffer);
        }  
        file.close();
    }

    void printPage(){
        for(int i = 0; i < All_registers.size() ; i ++){
            All_registers[i].show();
        }
    }
};


#endif