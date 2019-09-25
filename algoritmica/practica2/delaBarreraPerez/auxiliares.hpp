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
#include "combinatoria.hpp"
#include "sistemaMatrices.hpp"
#include "sistemaEcuaciones.hpp"
#include "estadistica.hpp"
#include "hanoi.hpp"



/**
 * @brief      Funcion que llama al menu principal del programa
 *
 * @return     nada
 */
int menu();


/**
 * @brief      Funcion central del programa que se encarga de ejecutar los algoritmos y llamar al resto de funciones
 *
 * @param[in]  opcion Opcion recibida por el menu principal que dice que algoritmo ejecutar
 */
void ejecutarAlgoritmo(int opcion);



/**
 * @brief      Aplica las ecuaciones correspondientes a cada algoritmo con los valores obtenidos al resolver el sistema y calcula de esta forma el tiempo teorico
 *
 * @param      _matrizSoluciones  Matriz donde se almacenan las soluciones del sistema
 * @param      n                  Vector que contiene el numero de elementos con el que se realizo el experimento
 * @param      opcion             Opcion que determina que ecuacion aplicar
 *
 * @return     Vector con los tiempos teoricos calculados para cada n
 */
std::vector<float> calcularTiempoTeorico(std::vector<std::vector<double> > & _matrizSoluciones, std::vector<double> & n, int & opcion);


/**
 * @brief      Calcula los dias de ejecucion para un determinado valor de n
 *
 * @param[in]  _matrizSoluciones  Matriz donde se almacenan las soluciones del sistema
 * @param[in]  o                  Opcion que determina que ecuacion aplicar
 */
void calcularDias(std::vector<std::vector<double> > _matrizSoluciones, int o);


/**
 * @brief      Guarda en un fichero de texto tres columas, la 1º es n, la 2º es el tiempo pratico y la 3º es el tiempo teorico
 *
 * @param      n           { parameter_description }
 * @param      t_practico  The t practico
 * @param      t_teorico   The t teorico
 */
void grabarFichero(std::vector<double> const &n,std::vector<float> const &t_practico, std::vector<float> const &t_teorico);


#endif