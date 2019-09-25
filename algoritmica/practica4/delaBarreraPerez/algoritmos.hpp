/*!
   \file  algoritmos.hpp
   \brief Archivo archivo hpp con los prototipos para los algoritmos voraces
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <vector>
#include <unistd.h>
#include "dinero.hpp"
#include "mochila.hpp"
#include "sistemaMonetario.hpp"
#include "materiales.hpp"


/**
 * @brief      Algoritmo de la mochila
 *
 * @param[in]  n     Numero de elementos del vector de materiales
 * @param[in]  v     Volumen de la mochila
 * @param      m     Vector de materiales
 */
void algoritmoMochila(int n, int v,
                      std::vector<Materiales>
                      &m);

/**
 * @brief      Muestra la solucion del algoritmo de la mochila
 *
 * @param      m     Vector de materiales
 * @param[in]  v     volumen de la mochila
 */
void recuentoMateriales(std::vector<Materiales> &m,
                        int v);//m=vector materiales, v=volumen de la mochila

/**
 * @brief      Algoritmo del cambio
 *
 * @param[in]  d       Vector que contiene el sistema monetario
 * @param[in]  cambio  Cambio que se quiere obtener
 */
void algoritmoCambio(std::vector<Dinero> d, int cambio);

/**
 * @brief      Muestra la solucion del algoritmo del cambio
 *
 * @param[in]  d     Vector de sistema monetario
 */
void recuentoDinero(std::vector<Dinero> d);