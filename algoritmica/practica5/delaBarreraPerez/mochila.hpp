/*!
   \file  mochila.hpp
   \brief descripcion de la clase mochila
   	\author Carlos de la Barrera Perez
*/
#ifndef _MOCHILA_HPP_
#define _MOCHILA_HPP_
#include <iostream>

#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <string>
#include <algorithm>
#include "macros.hpp"
#include "materiales.hpp"

//!  Definición de la clase sistema mochila
class Mochila
{
	//!  Atributos privados de la clase mochila
private:
	int _volumenMochila;
	std::vector<Materiales> _m;
	std::vector<std::vector<int> > _tabla;

//!  Metodos publicos de la clase mochila
public:

	//! \name Observadores de la clase sistema monetario

	/**
	 * @brief      Devuelve el volumen de la mochila
	 *
	 * @return     Devuelve el volumen
	 */
	inline int getVolumen() {return _volumenMochila;};

	/**
	 * @brief      Muestra el vector de materiales
	 *
	 * @param[in]  v     Vector de materiales
	 */
	void mostrarMateriales();

	/**
	 * @brief      Muestra la matriz generada
	 *
	 * @param[in]  filas     Numero de filas
	 * @param[in]  columnas  Numero de columnas
	 */
	void mostrarTablaMochila(int filas, int columnas);

	/**
	 * @brief      Lee la tabla y obtiene la solucion
	 */
	void obtenerSolucion();

	//! \name Modificadores de la clase mochila

	/**
	 * @brief      Modifica la variable volumen
	 *
	 * @param[in]  x     Volumen que se asigna a la variable
	 */
	inline void setVolumen(int x) {_volumenMochila = x;};


	/**
	 * @brief      Rellena el vector de materiales con lo que se lee en el fichero
	 */
	void setMateriales();

	/**
	 * @brief      Crea la tabla para el algoritmo de la mochila
	 *
	 * @param[in]  v        Vector de materiales
	 * @param[in]  volumen  Volumen de la mochila
	 */
	void setTablaMochila(int volumen);
};
#endif