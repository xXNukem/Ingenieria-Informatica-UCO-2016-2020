/*!
   \file  mochila.hpp
   \brief descripcion de la clase sistema monetario
   	\author Carlos de la Barrera Perez
*/
#ifndef _SISTEMAMONETARIO_HPP_
#define _SISTEMAMONETARIO_HPP_
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <vector>
#include <unistd.h>
#include "macros.hpp"
#include "dinero.hpp"

//!  Definición de la clase sistema monetario
class SistemaMonetario
{
	//! \name Atributos privados de la clase sistema monetario
private:
	std::vector<Dinero> _d;

//! \name Métodos públicos de la clase sistema monetario
public:
	//! \name Observadores de la clase sistema monetario

	/**
	 * @brief      Devuelve el vector de dinero
	 *
	 * @return     Vector de dinero
	 */
	std::vector<Dinero> getDinero() {return _d;};

	/**
	 * @brief      Muestra el sistema monetario leido
	 */
	void mostrarSistemaMonetario();

	//! \name Modificadores de la clase sistema monetario

	/**
	 * @brief      Rellana el vector con los datos leidos del fichero
	 */
	void setDinero();
};

#endif