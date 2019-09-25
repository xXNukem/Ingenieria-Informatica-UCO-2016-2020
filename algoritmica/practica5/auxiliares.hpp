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
#include "ClaseTiempo.cpp"
#include "sistemaMatrices.hpp"
#include "sistemaEcuaciones.hpp"
#include "estadistica.hpp"

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

/**
 * @brief      Calcula el tiempo teorico
 *
 * @param      _matrizSoluciones  Matriz con las soluciones del sistema
 * @param      n                  Vector de tamaños del ejemplar
 *
 * @return     vector con el tiempo teorico
 */
std::vector<double> calcularTiempoTeorico(std::vector<std::vector<double> > & _matrizSoluciones,
        std::vector<double> & n);

/**
 * @brief      Guarda el fichero de tiempos
 *
 * @param[in]  n           Vector de tamaños del ejemplar
 * @param[in]  t_practico  Vector con los tiempos practicaos
 * @param[in]  t_teorico   Vector con los tiempos teoricos
 */
void grabarFichero(std::vector<double> n, std::vector<double> t_practico,
                   std::vector<double> t_teorico);

/**
 * @brief      Calcula los dias, meses... para un tamaño de ejemplar
 *
 * @param[in]  _matrizSoluciones  Matriz con las soluciones del sistema
 */
void calcularDias(std::vector<std::vector<double> > _matrizSoluciones);

#endif