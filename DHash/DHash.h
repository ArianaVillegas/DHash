#include <bits/stdc++.h>
#include "pagina.h"
#include <time.h> 
#include <algorithm>
using namespace std;

const int DEEP=8;

struct RegTable{
    int pos;
    int d;
};

template <typename ID>
class DHash{
        int size;
        string fileName;
        string hashTable;
        RegTable HT[1<<DEEP];
    public:
        DHash(string _fileName){
            fileName = _fileName;
            hashTable = "hashTable.dat";
            fstream fFile, hFile;
            fFile.open(fileName, ios::binary | ios::in | ios::out | ios::app);
            hFile.open(hashTable, ios::binary | ios::in | ios::out | ios::app);
            fFile.seekp(0,ios::end);
            size = fFile.tellp()/sizeof(Pagina);
            if(!size){
                Pagina p;
                fFile.write((char*) &p, sizeof(Pagina));
                fFile.write((char*) &p, sizeof(Pagina));
                size = 2;
            }
            if(hFile.tellp()/sizeof(int) == 0){
                RegTable init;
                for(int i=0; i<(1<<DEEP); i++){
                    init.pos = i%2;
                    init.d = 1;
                    hFile.write((char*) &init, sizeof(RegTable));
                }
            }
            hFile.seekp(0,ios::beg);
            for(int i=0; i<(1<<DEEP); i++){
                RegTable init;
                hFile.read((char*) &init, sizeof(RegTable));
                HT[i] = init;
            }

            fFile.close();
            hFile.close();
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
            time_t t,t2;
            menu();
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
                    cout <<  "\n Demoro: "  << (float)(t2-t)/CLOCKS_PER_SEC << " segundos en insertar el registro" ; 
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
                        cout <<  "\n Demoro: "  << (float)(t2-t)/CLOCKS_PER_SEC << " segundos en encontrar el registro" ; 
                    }else{
                        cout << "Registro no encontrado.\n";
                    }
                }else if(opt==5){
                    cout << "EN PROCESO\n";
                    /*string pos;
                    char key[5];
                    cout << "\nKey del alumno a eliminar: ";
                    cin >> pos;
                    strcpy(key, pos.c_str());
                    if(del(key)){
                        cout << "El registro se ha eliminado correctamente.\n";
                    }else{
                        cout << "Registro no encontrado.\n";
                    }*/
                }else{
                    cout << "\nLa opción elegida no es valida. Elige otra.\n";
                }
                menu();
                cin >> opt;
            }
        }

        int hashfunction(string key){
            int ans=0;
            int size = key.size();
            for(int i=0; i<min(5,size); i++){
                ans += (int)key[i];
            }
            return ans%(1<<DEEP);
        }

        void add(Registro r){
            auto start = chrono::high_resolution_clock::now();
            int access=0;
            int hpos = hashfunction(string(r.codigo));
            int pos = HT[hpos].pos;
            int d = HT[hpos].d;
            fstream fFile;
            fFile.open(fileName, ios::binary | ios::in | ios::out | ios::ate);

            Pagina p; bool split = 0;
            fFile.seekp(pos*sizeof(Pagina), ios::beg);
            fFile.read((char*) &p, sizeof(Pagina)); access++;
            if(p.size==MAX_RECORDS){
                while(d!=DEEP){
                    d++; 
                    Pagina temp=p, newp;
                    p.size = newp.size = 0;
                    for(int k=0; k<temp.size; k++){
                        int res = hashfunction(string(temp.registers[k].codigo));
                        if((res/(1<<HT[hpos].d))%2){
                            newp.registers[newp.size++] = temp.registers[k];
                        }else{
                            p.registers[p.size++] = temp.registers[k];
                        }
                    }

                    for(int i=0; i<(1<<DEEP); i++){
                        if((i%(1<<(d-1)))!=hpos%(1<<(d-1))) continue;
                        if((i/(1<<(d-1)))%2){
                            HT[i].pos = size;
                        }
                        HT[i].d++;
                    }

                    size++;

                    if((newp.size==MAX_RECORDS && ((hpos/(1<<(d-1)))%2)) || (p.size==MAX_RECORDS && ((hpos/(1<<(d-1)))%2)==0)){
                        fFile.seekp(pos*sizeof(Pagina), ios::beg);
                        fFile.write((char*) &p, sizeof(Pagina)); access++;
                        fFile.seekp(0, ios::end);
                        fFile.write((char*) &newp, sizeof(Pagina)); access++;
                        fFile.close();
                        add(r);
                        return;
                    }

                    if((hpos/(1<<(d-1)))%2){
                        newp.registers[newp.size++] = r;
                    }else{
                        p.registers[p.size++] = r;
                    }

                    fFile.seekp(pos*sizeof(Pagina), ios::beg);
                    fFile.write((char*) &p, sizeof(Pagina)); access++;
                    fFile.seekp(0, ios::end);
                    fFile.write((char*) &newp, sizeof(Pagina)); access++;
                    fFile.close();
        
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
                    cout << "Tiempo de ejecución: " << duration.count() << "ms" << '\n';
                    cout << "Accesos a memoria: " << access << '\n';
                    return;
                }
                if(p.size==MAX_RECORDS){
                    Pagina overflow = p;
                    fFile.seekp(0, ios::end);
                    fFile.write((char*) &overflow, sizeof(Pagina)); access++;
                    p.size = 0;
                    p.next = size++;
                }
            }

            p.registers[p.size++] = r;
            fFile.seekp(pos*sizeof(Pagina), ios::beg);
            fFile.write((char*) &p, sizeof(Pagina)); access++;
            fFile.close();
        
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
            cout << "Tiempo de ejecución: " << duration.count() << "ms" << '\n';
            cout << "Accesos a memoria: " << access << '\n';
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
            Pagina p;
            bool v[1<<DEEP] = {0};
            for(int i=0; i<(1<<DEEP); i++){
                if(v[HT[i].pos]) continue;
                v[HT[i].pos] = 1;
                inFile.seekg(HT[i].pos*sizeof(Pagina),ios::beg);
                inFile.read((char*) &p, sizeof(Pagina));
                for(int j=0; j<p.size; j++){
                    p.registers[j].showData();
                }
                while(p.next!=-1){
                    inFile.seekg(p.next*sizeof(Pagina),ios::beg);
                    inFile.read((char*) &p, sizeof(Pagina));
                    for(int j=0; j<p.size; j++){
                        p.registers[j].showData();
                    }
                }
            }
            inFile.close();
            return records;
        }

        Registro search(ID key){
            auto start = chrono::high_resolution_clock::now();
            ifstream inFile;
            string line; Registro r;
            inFile.open(fileName, ios::binary);
            int access = 0;

            int hpos = hashfunction(string(key));
            int i = HT[hpos].pos;
            Pagina p;
            inFile.seekg(i*sizeof(Pagina),ios::beg);
            inFile.read((char*) &p, sizeof(Pagina));
            access++;
            for(int j=0; j<p.size; j++){
                bool diff=0;
                for(int k=0; k<5; k++){
                    if(key[k]!=p.registers[j].codigo[k]) {
                        diff = 1;
                        break;
                    }
                }
                if(diff) continue;
                inFile.close();
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
                //cout << "Tiempo de ejecución: " << duration.count() << "ms" << '\n';
               // cout << "Accesos a memoria: " << access << '\n';
                return p.registers[j];
            }
            while(p.next!=-1){
                inFile.seekg(p.next*sizeof(Pagina),ios::beg);
                inFile.read((char*) &p, sizeof(Pagina));
                access++;
                for(int j=0; j<p.size; j++){
                    bool diff=0;
                    for(int k=0; k<5; k++){
                        if(key[k]!=p.registers[j].codigo[k]) {
                            diff = 1;
                            break;
                        }
                    }
                    if(diff) continue;
                    inFile.close();
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
                    //cout << "Tiempo de ejecución: " << duration.count() << "ms" << '\n';
                    //cout << "Accesos a memoria: " << access << '\n';
                    return p.registers[j];
                }
            }
            
            inFile.close();
            strcpy(r.codigo,"-1");
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
            //cout << "Tiempo de ejecución: " << duration.count() << "ms" << '\n';
            //cout << "Accesos a memoria: " << access << '\n';
            return r;
        }

        void printall(int mode) {
            ifstream inFile;
            string line; Registro r;
            inFile.open(fileName, ios::binary);
            vector<int> usados;
            for (int i=0;i<(1<<DEEP);i++){
                int apunta_a=HT[i].pos;
                auto temp=find(usados.begin(),usados.end(),apunta_a);
                if (temp==usados.end()){
                    //aun no printeo esta pagina
                    usados.push_back(apunta_a);
                    Pagina p;
                    inFile.seekg(apunta_a*sizeof(Pagina),ios::beg);
                    inFile.read((char *)&p,sizeof(Pagina));
                    for (int j=0;j<p.size();j++){
                        p.registers[j].showData(mode);
                    }
                    while(p.next!=-1){
                        Pagina p;
                        inFile.seekg(apunta_a*sizeof(Pagina),ios::beg);
                        inFile.read((char *)&p,sizeof(Pagina));
                        for (int j=0;j<p.size();j++){
                            p.registers[j].showData(mode);
                        }
                        
                    }
            
                
                
                }else{
                    continue;
                }
                
            }
        }




            


        /*bool del(ID key){
            auto start = chrono::high_resolution_clock::now();
            fstream inFile; 
            inFile.open(fileName, ios::binary | ios::in | ios::out);

            int i = hashfunction(string(key));
            int access = 0;
            Pagina p;
            inFile.seekg(i*sizeof(Pagina),ios::beg);
            inFile.read((char*) &p, sizeof(Pagina));
            access++;
            for(int j=0; j<p.size; j++){
                bool diff=0;
                for(int k=0; k<5; k++){
                    if(key[k]!=p.registers[j].codigo[k]) {
                        diff = 1;
                        break;
                    }
                }
                if(diff) continue;
                cout << j << "--->" << p.size << '\n';
                for(; j<p.size; j++){
                    cout << "se reemplaza" << p.registers[j].codigo << ' ' << p.registers[j+1].codigo << '\n';
                    p.registers[j] = p.registers[j+1];
                }
                p.size--;
                inFile.write((char*) &p, sizeof(Pagina)); access++;
                inFile.close();
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
                cout << "Tiempo de ejecución: " << duration.count() << "ms" << '\n';
                cout << "Accesos a memoria: " << access << '\n';
                return true;
            }
            while(p.next!=-1){
                inFile.seekg(p.next*sizeof(Pagina),ios::beg);
                inFile.read((char*) &p, sizeof(Pagina));
                access++;
                for(int j=0; j<p.size; j++){
                    bool diff=0;
                    cout << p.registers[j].codigo << '\n';
                    for(int k=0; k<5; k++){
                        if(key[k]!=p.registers[j].codigo[k]) {
                            diff = 1;
                            break;
                        }
                    }
                    if(diff) continue;
                    for(; j<p.size; j++){
                        p.registers[j] = p.registers[j+1];
                    }
                    p.size--;
                    inFile.write((char*) &p, sizeof(Pagina)); access++;
                    inFile.close();
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
                    cout << "Tiempo de ejecución: " << duration.count() << "ms" << '\n';
                    cout << "Accesos a memoria: " << access << '\n';
                    return true;
                }
            }

            inFile.close();
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
            cout << "Tiempo de ejecución: " << duration.count() << "ms" << '\n';
            cout << "Accesos a memoria: " << access << '\n';
            return false;
        }*/
        ~DHash(){
            fstream hFile;
            hFile.open(hashTable, ios::binary | ios::out | ios::ate);
            hFile.seekp(0,ios::beg);
            for(int i=0; i<(1<<DEEP); i++){
                hFile.write((char*) &HT[i], sizeof(RegTable));
            }
            hFile.close();
        }
};