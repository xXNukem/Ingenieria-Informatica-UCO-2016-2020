/*! 
   \file  main.cpp
   \brief Funcio principal del programa
*/

#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include "macros.hpp"
#include "auxiliares.hpp"
#include "combinatoria.hpp"

/**
 * @brief      Funcion main
 *
 * @return     0
 */
int main()
{
	int opcion;

	srand(time(NULL));
		do{

			opcion=menu();

			switch(opcion)
			{
				case 1:
					std::cout<<"Ejecutando combinatoria con recursividad"<<std::endl;
					ejecutarAlgoritmo(opcion);
					getchar();
					break;
				case 2:
					std::cout<<"Ejecutando combinatoria con recursividad y tablas"<<std::endl;
					ejecutarAlgoritmo(opcion);
					getchar();
					break;
				case 3:
					std::cout<<"Ejecutando combinatoria sin recursividad"<<std::endl;
					ejecutarAlgoritmo(opcion);
					getchar();
					break;
				case 4:
					std::cout<<"Ejecutando Torres de Hanoi"<<std::endl;
					ejecutarAlgoritmo(opcion);
					getchar();
					break;

			}	

		}while(opcion!=0);

	return 0;
}