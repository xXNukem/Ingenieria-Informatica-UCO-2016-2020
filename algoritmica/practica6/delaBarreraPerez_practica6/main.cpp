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
	srand(time(NULL));

	do {

		opcion = menu();

		switch (opcion)
		{
		case 1:
			ejecutarOperacion(opcion);
			getchar();
			break;
		case 2:
			ejecutarOperacion(opcion);
			getchar();
			break;
		case 3:
			ejecutarOperacion(opcion);
			getchar();
			break;
		case 4:
			ejecutarOperacion(opcion);
			getchar();
		break;
		case 5:
			ejecutarOperacion(opcion);
			getchar();
		break;
		}

	} while (opcion != 0);

	return 0;
}