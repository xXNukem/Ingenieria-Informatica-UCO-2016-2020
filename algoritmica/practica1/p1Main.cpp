#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include "macros.hpp"
#include "medicionMetodo.hpp"
#include "p1auxiliares.hpp"

int main()
{
	int opcion;
	MedicionMetodo m;
	srand(time(NULL));
		do{

			opcion=menu();

			switch(opcion)
			{
				case 1:
					std::cout<<"Ejecutando método de inserción binaria"<<std::endl;
					m.metodoInsercionBinaria();
					getchar();
					break;
				case 2:
					std::cout<<"Ejecutando método de monticulo"<<std::endl;
					m.metodoMonticulo();
					getchar();
					break;

			}	

		}while(opcion!=0);

	return 0;
}
