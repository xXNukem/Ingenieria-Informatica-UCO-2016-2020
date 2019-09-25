/*!
	\file combinatoria.hpp
	\brief Clase combinatoria.
	\author Carlos de la Barrera Perez
*/

#ifndef _COMBINATORIA_HPP_
#define _COMBINATORIA_HPP_
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <vector>
#include <unistd.h>
#include "macros.hpp"
#include "ClaseTiempo.cpp"

//!  Definición de la clase combinatoria
class Combinatoria
{
	//! \name Atributos privados de la clase combinatoria
	private:

		int _nMin;
		int _nMax;
		int _repeticiones;
		int _incremento;

	//! \name Métodos públicos de la clase combinatoria
	public:

		//! \name Modificadores de la clase combinatoria

		/**
		 * @brief      Modifica el valor de _nMin
		 *
		 * @param[in]  x     Valor que se le dará a nMin
		 */
		inline void setNMin(int x){_nMin=x;};

		/**
		 * @brief      Modifica el valor de _nMax
		 *
		 * @param[in]  x     Valor que se le dará a nMax
		 */
		inline void setNMax(int x){_nMax=x;};

		/**
		 * @brief      Modifica el valor de _repeticiones
		 *
		 * @param[in]  x     Valor que se le dará a _repeticiones
		 */
		inline void setRepeticiones(int x){_repeticiones=x;};

		/**
		 * @brief      Modifica el valor de _incremento
		 *
		 * @param[in]  x     Valor que se le dará a _incremento
		 */
		inline void setIncremento(int x){_incremento=x;};

		//! \name Observadores de la clase combinatoria

		/**
		 * @brief      Observador de _nMin
		 *
		 * @return     Variable _nMin
		 */
		inline int getNMin(){return _nMin;};

		/**
		 * @brief      Observador de _nMax
		 *
		 * @return     Variable _nMax
		 */
		inline int getNMax(){return _nMax;};

		/**
		 * @brief      Observador de _repeticiones
		 *
		 * @return     Variable _repeticiones
		 */
		inline int getRepeticiones(){return _repeticiones;};

		/**
		 * @brief      Observador de _incremento
		 *
		 * @return     Variable _incremento
		 */
		inline int getIncremento(){return _incremento;};


		/**
		 * @brief      Lee datos por teclado para el experimento de combinatoria
		 */
		void leerDatos();

		/**
		 * @brief      Ejecuta la combinatoria en modo recursivo
		 *
		 * @param[in]  n     Numero N
		 * @param[in]  k     Numero K
		 *
		 * @return     Resultado de la combinatoria
		 */
		double combinatoriaRecursiva(int n,int k);

		/**
		 * @brief      Ejecuta la combinatoria recursiva utilizando tabla de valores
		 *
		 * @param[in]  n              Numero N
		 * @param[in]  k              Numero K
		 * @param      _tablaValores  Vector con resultados de combinatoria previamente obtenidos
		 *
		 * @return     { description_of_the_return_value }
		 */
		double combinatoriaTablaValores(int n, int k, std::vector<double> & _tablaValores);

		/**
		 * @brief      Funcion que realiza la busqueda en la tabla de valores
		 *
		 * @param      v     Vector en el que se almacenan los valores
		 * @param[in]  n     Numero N
		 * @param[in]  k     Numero K
		 *
		 * @return     Valor encontrado en la tabla
		 */
		double busquedaTablaValores(std::vector<double> & v, int n, int k);

		/**
		 * @brief      Ejecuta la combinatoria calculando un coeficiente de factoriales
		 *
		 * @param[in]  n     Numero N
		 * @param[in]  k     Numero K
		 *
		 * @return     Resultado de la combinatoria
		 */
		double combinatoriaNoRecursiva(int n, int k);

		/**
		 * @brief      Clacula el factorial de forma iterativa para la funcion de combinatoriaNoRecursiva
		 *
		 * @param[in]  x     Numero X del que se calcula el factorial
		 *
		 * @return     Resultado del factorial
		 */
		double calcularFactorial(int x);
};
#endif