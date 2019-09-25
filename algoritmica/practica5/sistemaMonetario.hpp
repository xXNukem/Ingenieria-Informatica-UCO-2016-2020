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
#include <limits.h>
#include <algorithm>
#include "macros.hpp"
#include "dinero.hpp"

//!  Definición de la clase sistema monetario
class SistemaMonetario
{
	//! \name Atributos privados de la clase sistema monetario
private:
	std::vector<Dinero> _d;
	std::vector<std::vector<int> > _tabla;
	int _cambio;

//! \name Métodos públicos de la clase sistema monetario
public:
	//! \name Observadores de la clase sistema monetario

	/**
	 * @brief      Muestra el sistema monetario leido
	 */
	void mostrarSistemaMonetario();

	/**
	 * @brief      Lee la tabla y obtiene una solucion
	 */
	void obtenerSolucion();

	/**
	 * @brief      Devuelve el valor de la variable cambio
	 *
	 * @return     Variable cambio
	 */
	inline int getCambio() {return _cambio;};

	void mostrarTablaDinero(int filas, int columnas);

	//! \name Modificadores de la clase sistema monetario

	/**
	 * @brief      Rellana el vector con los datos leidos del fichero
	 */
	void setDinero();

	/**
	 * @brief      Asigna valor a la variable cambio
	 *
	 * @param[in]  x     Valor que se asigna a cambio
	 */
	inline void setCambio(int x) {_cambio = x;};

	/**
	 * @brief      Crea la tabla para el problema
	 *
	 * @param[in]  v       Vector con el sistema monetario leido
	 * @param[in]  cambio  Cambio que se quiere obtener
	 */
	void setTablaDinero(int cambio);
};

#endif