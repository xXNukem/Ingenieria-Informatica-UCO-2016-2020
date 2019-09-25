/*!
	\file hanoi.hpp
	\brief Se define el TAD Vertice.
	\author Carlos de la Barrera Perez

*/

#ifndef _HANOI_HPP_
#define _HANOI_HPP_
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <vector>
#include <unistd.h>
#include "macros.hpp"

//! \name Incializacion de las torres	
#define TORRE_INICIAL 1
#define TORRE_AUXILIAR 2
#define TORRE_FINAL 3


/**
 * @brief      Funcion que calcula las torres de hanoi en modo recursivo
 *
 * @param[in]  discos  Numero de discos
 *
 * @return     Numero de movimientos
 */
int torresHanoi(int discos);

/**
 * @brief      Ejecuta las torres de hanoi en modo texto
 *
 * @param[in]  discos  Numero de discos
 */
void ejecutarHanoiTexto(int discos);

/**
 * @brief      Muestra los discos en las torres
 */
void muestra();

/**
 * @brief      Funcion recursiva que sirve para mostrar hanoi en modo texto
 *
 * @param[in]  numDiscos      Numero de discos
 * @param[in]  torreInicial   Valor de la torre inicial
 * @param[in]  torreAuxiliar  Valor de la torre de en medio
 * @param[in]  torreFinal     Valor de la torre final
 *
 * @return     Numero de movimientos
 */
int hanoi(int numDiscos, int torreInicial, int torreAuxiliar, int torreFinal);
//int torresHanoiTexto(int discos, int inicio, int fin, int aux);

#endif