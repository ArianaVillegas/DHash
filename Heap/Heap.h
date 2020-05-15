#include <bits/stdc++.h>
#include "Registro.h"
#include <time.h> 
using namespace std;

template <typename ID>
class Heap{
        string fileName;
    public:
        Heap(string _fileName){
            fileName = _fileName;
        }

        void menu(){
            cout << "\nBASE DE DATOS";
            cout << "\n1. Ver a los alumnos";
            cout << "\n2. Insertar alumnos desde archivo";
            cout << "\n3. Insertar un alumno";
            cout << "\n4. Buscar un alumno";
            cout << "\n5. Eliminar un alumno";
            cout << "\n0. Salir";
            cout << "\nElíge una opción: ";
        }

        void showMenu(){
            int opt;
            menu();
			time_t t,t2;
            cin >> opt;
            while(opt){
                if(opt==1){
                    vector<Registro> records=load();
                    for(Registro r:records)
                        r.showData();
                }else if(opt==2){
                    string file;
                    cout << "\nNombre del archivo: ";
                    cin >> file;
					t = clock();
                    addFile(file);
					t2 = clock();
					cout <<  "\n Demoro: "  << (float)(t2-t)/CLOCKS_PER_SEC << " segundos en insertar los registros" ; 
       
                }else if(opt==3){
                    Registro r;
                    r.setData();
					t = clock();
                    add(r);
					t2 = clock();
				    cout <<  "\n Demoro: "  << (float)(t2-t)/CLOCKS_PER_SEC << " segundos en insertar el registros" ; 
                }else if(opt==4){
                    string pos;
                    char key[5];
                    cout << "\nKey del alumno a buscar: ";
                    cin >> pos;
                    strcpy(key, pos.c_str());
					t = clock();
                    auto r = search(key);
					t2 = clock();
                    bool diff=0;
                    char comp[]="-1";
                    for(int i=0; i<2; i++){
                        if(comp[i]!=r.codigo[i]) {
                            diff = 1;
                            break;
                        }
                    }
                    if(diff){
                        r.showData();
						cout <<  "\n Demoro: "  << (float)(t2-t)/CLOCKS_PER_SEC << " segundos en encontrar el registros" ;

                    }else{
                        cout << "Registro no encontrado.\n";
                    }
                }else if(opt==5){
                    string pos;
                    char key[5];
                    cout << "\nKey del alumno a eliminar: ";
                    cin >> pos;
                    strcpy(key, pos.c_str());
                    if(del(key)){
                        cout << "El registro se ha eliminado correctamente.\n";
                    }else{
                        cout << "Registro no encontrado.\n";
                    }
                }else{
                    cout << "\nLa opción elegida no es valida. Elige otra.\n";
                }
                menu();
                cin >> opt;
            }
        }

        void add(Registro r){
            auto start = chrono::high_resolution_clock::now();
            fstream fFile;
            fFile.open(fileName, ios::binary | ios::out | ios::app);
            fFile.write((char*) &r, sizeof(Registro));
            fFile.close();
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
            cout << "Tiempo de ejecución: " << duration.count() << "ms" << '\n';
            cout << "Accesos a memoria: " << 1 << '\n';
        }

        void addFile(string newfile){
            ifstream inFile; 
            string line;
            inFile.open(newfile);
            while(getline(inFile, line)){
                istringstream sl(line);
                char _cod[5], _nombre[12], _apellido[20], _car[20];
                string cd, n, a, c;
                getline(sl,cd,'|');
                getline(sl,n,'|');
                getline(sl,a,'|');
                getline(sl,c,'\n');
                strcpy(_cod, cd.c_str());
                strcpy(_nombre, n.c_str());
                strcpy(_apellido, a.c_str());
                strcpy(_car, c.c_str());
                Registro r(_cod,_nombre,_apellido,_car);
                add(r);
            }
            inFile.close();
        }

        vector<Registro> load(){
            vector<Registro> records;
            ifstream inFile; string line;
            inFile.open(fileName, ios::binary);
            Registro r;
            while(inFile.read((char*) &r, sizeof(Registro))){
                records.push_back(r);
            }
            inFile.close();
            return records;
        }

        Registro search(ID key){
            auto start = chrono::high_resolution_clock::now();
            ifstream inFile;
            string line; Registro r;
            inFile.open(fileName);
            int access = 0;
            while(inFile.read((char*) &r, sizeof(Registro))){
                access++;
                bool diff=0;
                for(int i=0; i<5; i++){
                    if(key[i]!=r.codigo[i]) {
                        diff = 1;
                        break;
                    }
                }
                if(diff) continue;
                inFile.close();
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
                cout << "Tiempo de ejecución: " << duration.count() << "ms" << '\n';
                cout << "Accesos a memoria: " << access << '\n';
                return r;
            }
            inFile.close();
            strcpy(r.codigo,"-1");
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
            cout << "Tiempo de ejecución: " << duration.count() << "ms" << '\n';
            cout << "Accesos a memoria: " << access << '\n';
            return r;
        }

        bool del(ID key){
            auto start = chrono::high_resolution_clock::now();
            ifstream inFile; ofstream outFile;
            string line; Registro r;
            inFile.open(fileName);
            bool find = 0;
            int access = 0;
            outFile.open("temp.txt",ios::out | ios::app);
            while(inFile.read((char*) &r, sizeof(Registro))){
                access++;
                bool diff=0;
                for(int i=0; i<5; i++){
                    if(key[i]!=r.codigo[i]) {
                        diff = 1;
                        break;
                    }
                }
                if(!diff){
                    find = 1;
                    continue;  
                } 
                outFile.write((char*) &r, sizeof(Registro));
            }
            inFile.close();
            outFile.close();
            remove(fileName.c_str());
            rename("temp.txt", fileName.c_str());
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
            cout << "Tiempo de ejecución: " << duration.count() << "ms" << '\n';
            cout << "Accesos a memoria: " << access << '\n';
            if(find) return true;
            return false;
        }
};
