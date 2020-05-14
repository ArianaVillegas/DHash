#ifndef PAGINA_H
#define PAGINA_H
#include <iostream> 
#include <string>
#include <fstream>
#include "Registro.h"
#include <vector>
#include "STRING.h"
#define MAX_RECORDS 10
using namespace std; 
typedef STRING char_t;

void swap(Registro<char_t>* a, Registro<char_t>* b)
{  
    Registro<char_t> t = *a;
    *a = *b;  
    *b = t;  
}  
int partition (vector<Registro<char_t>> &arr, int low, int high)
{  
    int pivot = stoi(arr[high].codigo.to_string());
    int i = (low - 1); 
  
    for (int j = low; j <= high - 1; j++)  
    {  
        if (stoi(arr[j].codigo.to_string()) < pivot)
        {  
            i++; 
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  
void quickSort(vector <Registro<char_t>>  &arr, int low, int high)
{  
    if (low < high)  
    {  
        int pi = partition(arr, low, high);  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}  

istream & operator >> (istream & stream, Registro<char_t> & record)
{	   
    stream.read((char *) &record, sizeof(record));
    string bufer;
    getline(stream,bufer);
    return stream;  
}

struct Pagina{
    string name;  //to define
    vector<Registro<char_t>> All_registers;
    string puntero_siguiente;
    int size(){
        return All_registers.size();
    }
    void sort(){
        quickSort(All_registers,0,All_registers.size()-1);
    }
    void setName(){
        name = All_registers[0].codigo.to_string();
        name +=  ".txt"; 
    }
    void write(){
        fstream file;
        file.open(name,ios::out| ios::binary |ios::trunc);
        for( int i = 0 ; i  < All_registers.size() ; i++){
            All_registers[i].show();
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
        Registro<char_t> buffer;
        string bug;
        while(file >> buffer){
            //cout << file.tellg() << endl;
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