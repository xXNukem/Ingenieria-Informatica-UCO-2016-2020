/*!
	\file estadistica.hpp
	\brief Fichero hpp de las funciones de estadistica
	\author Carlos de la Barrera Perez
*/

#ifndef _ESTADISTICA_HPP_
#define _ESTADISTICA_HPP_
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <vector>
#include <unistd.h>
#include "macros.hpp"
#include <math.h>

/**
 * @brief      Obtiene el coeficiente de determinacion utilizando el tiempo practico y teorico
 *
 * @param      t_practico  Vector con el tiempo practico
 * @param      t_teorico   Vector con el tiempo teorico
 *
 * @return     Coeficiente de determinacion
 */
float getCoeficienteDeterminacion(std::vector <float>const &t_practico, std::vector <float>const &t_teorico);

/**
 * @brief      Obtiene la varianza
 *
 * @param[in]  v     Vector con el tiempo teorico o practico
 * @param[in]  x     Media del tiempo teorico o practico
 *
 * @return     Varianza
 */
float getVarianza(std::vector<float> v, double x);

/**
 * @brief      Calcula la media de un vector
 *
 * @param[in]  m     Vector del que se calculara la media
 *
 * @return     Media del vector
 */
float getMedia(std::vector<float> m);


#endif