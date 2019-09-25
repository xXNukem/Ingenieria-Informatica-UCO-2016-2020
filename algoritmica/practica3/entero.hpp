/*!
	\file entero.hpp
	\brief fichero hpp para la clase entero
	\author Carlos de la Barrera Perez
*/

#ifndef _ENTERO_HPP_
#define _ENTERO_HPP_
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <string>
#include <vector>
#include <unistd.h>
#include "macros.hpp"
#include "funcionesbajonivel.hpp"
using namespace std;

//!  Definición de la clase combinatoria
class Entero
{
	//! \name Atributos privados de la clase combinatoria
private:

	string _numero;

//! \name Métodos públicos de la clase combinatoria
public:

//! \name Observadores de la clase entero

	/**
	 * @brief      Devuelve el entero
	 *
	 * @return     Cadena con el entero
	 */
	inline string getNumero() {return _numero;};

//! \name Modificadores de la clase entero

	/**
	 * @brief      Modifica el valor del entero
	 *
	 * @param[in]  x     Cadena con un numero entero
	 */
	inline void setNumero(string x) {_numero = x;};

//! \name Funciones de la clase entero

	/**
	 * @brief      Suma dos numeros enteros grandes
	 *
	 * @param[in]  numero1  Primer numero
	 * @param[in]  numero2  Segundo numero
	 *
	 * @return     Resultado de la suma
	 */
	string sumarNumero(string numero1, string numero2);

	/**
	 * @brief      Multiplica dos numeros enteros grandes
	 *
	 * @param      numero1  Primer numero
	 * @param      numero2  Segundo numero
	 * @param[in]  limite   Limite de digitos hasta realizar la multiplicacion
	 *                      de forma tradicional
	 *
	 * @return     Producto
	 */
	string multiplicaNumeros(string const &numero1, string const &numero2, int limite);

//! \name Sobrecarga del operador de suma

	string operator+(Entero &e);
//! \name Sobrecarga del operador de multiplicacion
	string operator*(Entero &e);
};

//! \name Sobrecarga del operador de salida
ostream &operator<<(ostream &stream, Entero &e);

//! \name Sobrecarga del operador de suma
istream &operator>>(istream &stream, Entero &e);


#endif