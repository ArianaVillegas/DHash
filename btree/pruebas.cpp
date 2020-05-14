#include <iostream>
#include <vector> 
#include <fstream>
//#include "Nodos.h"
#include "pagina.h"
#include <string.h> 
using namespace std; 

int main(){
	Pagina page("pagina.txt");
		/*	Registro record1; 
		strcpy(record1.codigo , "001") ;
		strcpy(record1.Nombre ,"Juan");
		strcpy(record1.Apellidos , "Arias");
		strcpy(record1.Carrera , "CS" );
			Registro record2; 
		strcpy(record2.codigo , "003") ;
		strcpy(record2.Nombre , "Pedro");
		strcpy(record2.Apellidos , "SOTO");
		strcpy(record2.Carrera , "Ambiental") ;
			Registro record3; 
		strcpy(record3.codigo , "002");
		strcpy(record3.Nombre , "Jose");
		strcpy(record3.Apellidos , "Rojas");
		strcpy(record3.Carrera , "Civil" );
			Registro record4; 
		strcpy(record4.codigo , "005");
		strcpy(record4.Nombre , "Pedro");
		strcpy(record4.Apellidos , "Tarillo");
		strcpy(record4.Carrera , "Mecatronica") ;
			Registro record5; 
		strcpy(record5.codigo , "004");
		strcpy(record5.Nombre , "Ronaldo");
		strcpy(record5.Apellidos , "Tifuentes");
		strcpy(record5.Carrera , "Energia");
		Registro record6; 
		strcpy(record6.codigo , "006");
		strcpy(record6.Nombre , "Cesar");
		strcpy(record6.Apellidos , "Madera");
		strcpy(record6.Carrera , "CS");
		
		page.All_registers.push_back(record1);
		page.All_registers.push_back(record2);
		page.All_registers.push_back(record3);
		page.All_registers.push_back(record4);
		page.All_registers.push_back(record5);
		page.All_registers.push_back(record6);
			
		page.write(); */
		page.loadPage("pagina.txt");
		page.sort();
		page.write();
		
		Pagina page2("pagina.txt");
		page2.loadPage("pagina.txt");
		page2.printPage();
	//page.printPage();
		/*page.sort();
		cout << endl;
		page.printPage();*/
}
