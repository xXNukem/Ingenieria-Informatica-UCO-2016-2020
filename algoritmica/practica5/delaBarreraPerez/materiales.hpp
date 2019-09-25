/*!
   \file  materiales.hpp
   \brief descripcion de la clase materiales
   	\author Carlos de la Barrera Perez
*/
#ifndef _MATERIALES_HPP_
#define _MATERIALES_HPP_
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
using namespace std;

//! Definición de la clase sistema Materiales
//!
class Materiales
{
	//!  Atributos privados de la clase materiales

private:

	int _id;
	int _vol;
	int _pre;
	string _usado = "nada";
//!  Metodos publicos de la clase materiales

public:


	//! \name Modificadores de la clase sistema materiales

	/**
	 * @brief      Modifica la id
	 *
	 * @param[in]  x     Variable que se asigna a la id
	 */
	inline void setID(int x) {_id = x;};

	/**
	 * @brief      Modifica el volumen
	 *
	 * @param[in]  x     Variable que se asigna al volumen
	 */
	inline void setVOL(int x) {_vol = x;};

	/**
	 * @brief      Modifica el precio por unidad
	 *
	 * @param[in]  x     Variable que se asigna al precio por unidad
	 */
	inline void setPRE(int x) {_pre = x;};

	/**
	 * @brief      Modifica si el material esta usado
	 *
	 * @param[in]  x     Variable que se asigna a usado
	 */
	inline void setUSADO(string x) {_usado = x;};

	//! \name Observadores de la clase sistema monetario

	/**
	 * @brief      Devuelve la id
	 *
	 * @return     Id del material
	 */
	inline int getID() {return _id;};

	/**
	 * @brief      Devuelve el volumen
	 *
	 * @return     Volumen del material
	 */
	inline int getVOL() {return _vol;};

	/**
	 * @brief      Devuelve el precio
	 *
	 * @return     Precio del material
	 */
	inline int getPRE() {return _pre;};

	/**
	 * @brief      Devuelve si el material esta usado
	 *
	 * @return     Estado del material
	 */
	inline string getUSADO() {return _usado;};

};


#endif