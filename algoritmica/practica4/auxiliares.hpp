/*!
	\file auxiliares.hpp
	\brief fichero hpp para las funciones auxiliares
	\author Carlos de la Barrera Perez
*/

#ifndef _AUXILIARES_HPP_
#define _AUXILIARES_HPP_
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <vector>
#include <unistd.h>
#include "macros.hpp"
#include "mochila.hpp"
#include "materiales.hpp"
#include "dinero.hpp"
#include "sistemaMonetario.hpp"
#include "algoritmos.hpp"
using namespace std;


/**
 * @brief      Funcion que llama al menu principal del programa
 *
 * @return     nada
 */
int menu();

/**
 * @brief      Funcion que ejecuta la operacion que le decimos en el menu
 *             principal
 *
 * @param[in]  opcion  1 para el cambio y 2 para la mochila
 */
void ejecutarOperacion(int opcion);


#endif