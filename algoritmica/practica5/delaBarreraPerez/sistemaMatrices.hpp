/*!
   \file  estadistica.cpp
   \brief Fichero que contiene la clase SistemaMatrices para calcular el sistema a partir del tiempo practico y el tamaño N
   	\author Carlos de la Barrera Perez
*/
#ifndef _SISTEMAMATRICES_HPP_
#define _SISTEMAMATRICES_HPP_
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <math.h>

//!  Definición de la clase SistemaMatrices
class SistemaMatrices
{

	//! \name  Atributos privados de la clase
private:

	std::vector<std::vector<double> > _matrizCoeficientes;
	std::vector<std::vector<double> > _matrizIndependientes;
	std::vector<std::vector<double> > _matrizSoluciones;

	//! \name  Metodos publicos de la clase
public:
	//!  Observadores

	/**
	 * @brief      Obtiene la matriz de Coeficientes
	 *
	 * @return     Matriz de coeficientes
	 */
	inline std::vector<std::vector<double> > getMatrizCoeficientes() { return _matrizCoeficientes;};

	/**
	 * @brief      Obtiene la matriz de los terminos independientes
	 *
	 * @return     The matriz independientes.
	 */
	inline std::vector<std::vector<double> > getMatrizIndependientes() { return _matrizIndependientes;};

	/**
	 * @brief      Obtiene la matriz soluciones
	 *
	 * @return     Matriz soluciones
	 */
	inline std::vector<std::vector<double> > getMatrizSoluciones() { return _matrizSoluciones;};

	/**
	 * @brief      Crea el sistema de ecuaciones
	 *
	 * @param[in]  n           Vector con el tamaño N de cada experimento
	 * @param[in]  t_practico  Vector con el tiempo practico para cada N
	 * @param[in]  nFil        Filas de la matriz
	 * @param[in]  nCol        Columnas de la matriz
	 */
	void setSistema(std::vector<double> n, std::vector<double> t_practico, int nFil, int nCol);

	/**
	 * @brief      Realiza el sumatorio que se coloca en cada campo de la matriz
	 *
	 * @param[in]  n           Vector con el tamaño N de cada experimento
	 * @param[in]  t_practico  Vector con el tiempo practico para cada N
	 * @param[in]  a           Posicion de la matriz a la que corresponde el sumatorio
	 * @param[in]  b           Posicion de la matriz a la que corresponde el sumatorio
	 *
	 * @return     Resultado del sumatorio
	 */
	double sumatorio(std::vector<double> n, std::vector<double> t_practico, int a, int b);

	/**
	 * @brief      Muestra una matriz(Utilizada de forma auxiliar durante las pruebas del programa)
	 *
	 * @param[in]  m     Matriz a mostrar
	 */
	void mostrarMatriz(std::vector<std::vector<double> > m);

};

#endif