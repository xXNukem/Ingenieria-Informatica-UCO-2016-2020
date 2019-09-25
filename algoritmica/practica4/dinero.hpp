/*!
   \file  dinero.hpp
   \brief descripcion de la clase dinero
   	\author Carlos de la Barrera Perez
*/
#ifndef _DINERO_HPP_
#define _DINERO_HPP_
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <vector>
#include <unistd.h>
#include "macros.hpp"
using namespace std;

//!  Definición de la clase sistema Dinero
class Dinero
{
	//!  Atributos privados de la clase Dinero
private:
	int _valor;
	string _tipo;
	int _cantidadUsada = 0;

	//!  Metodos publicos de la clase Dinero

public:

	//! \name Observadores de la clase dinero

	/**
	 * @brief      Devuelve el valor del dinero
	 *
	 * @return     Variable valor
	 */
	inline int getValor() {return _valor;};

	/**
	 * @brief      Devuelve si el dinero es moneda o billete
	 *
	 * @return     Variable tipo
	 */
	inline string getTipo() {return _tipo;};

	/**
	 * @brief      Devuelve la cantidad de esa moneda o billete utilizadas
	 *
	 * @return     Variable cantidad Usada
	 */
	inline int getCantidadUsada() {return _cantidadUsada;};

	//! \name Modificadores de la clase sistema dinero


	/**
	 * @brief      Modifica la cantidad de moneda o billete usados
	 *
	 * @param[in]  x     Variable que se asigna a la cantidad usada
	 */
	inline void setCantidadUsada(int x) {_cantidadUsada = x;};

	/**
	 * @brief      Modifica el valor del dinero
	 *
	 * @param[in]  x     Variable que se asigna al valor
	 */
	inline void setValor(int x) {_valor = x;};

	/**
	 * @brief      Modifica el tipo de dinero
	 *
	 * @param[in]  x     Variable que se asigna al tipo de dinero
	 */
	inline void setTipo(string x) {_tipo = x;};

};


#endif