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
#include "macros.hpp"
#include "materiales.hpp"

//!  Definición de la clase sistema mochila
class Mochila
{
	//!  Atributos privados de la clase mochila
private:
	int _volumenMochila;
	std::vector<Materiales> _m;

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
	 * @brief      Devuelve el vector de materiales
	 *
	 * @return     Vector de materiales
	 */
	inline std::vector<Materiales> getMateriales()const {return _m;};

	/**
	 * @brief      Muestra el vector de materiales
	 *
	 * @param[in]  v     Vector de materiales
	 */
	void mostrarMateriales(std::vector<Materiales> v);

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

};
#endif