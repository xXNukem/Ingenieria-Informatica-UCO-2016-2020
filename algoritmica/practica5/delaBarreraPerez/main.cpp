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

/**
 * @brief      Funcion main
 *
 * @return     0
 */
int main()
{
	int opcion;


	do {

		opcion = menu();

		switch (opcion)
		{
		case 1:
			std::cout << "Ejecutando algoritmo del cambio " << std::endl;
			ejecutarOperacion(opcion);
			getchar();
			break;
		case 2:
			std::cout << "Ejecutando ealgoritmo de la mochila " << std::endl;
			ejecutarOperacion(opcion);
			getchar();
			break;
		case 3:
			std::cout << "Ejecutando el algoritmo del cambio para estudiar su complejidad computacional " <<
			          std::endl;
			ejecutarOperacion(opcion);
			getchar();
			break;
		}

	} while (opcion != 0);

	return 0;
}