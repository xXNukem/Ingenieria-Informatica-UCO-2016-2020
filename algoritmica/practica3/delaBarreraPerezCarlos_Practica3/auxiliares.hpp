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
#include "entero.hpp"
#include "funcionesbajonivel.hpp"
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
 * @param[in]  opcion  1 para sumar y 2 para multiplicar
 */
void ejecutarOperacion(int opcion);

/**
 * @brief      Obtiene el tamaño de la cadena mayor
 *
 * @param[in]  e1    Objeto de tipo entero
 * @param[in]  e2    Objeto de tipo entero
 *
 * @return     Entero que corresponde al tamaño del entero con mayor numero de
 *             digitos
 */
int obtenerTam(Entero e1, Entero e2);


#endif