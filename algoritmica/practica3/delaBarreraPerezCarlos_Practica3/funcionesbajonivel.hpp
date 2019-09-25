/*!
	\file funcionesbajonivel.hpp
	\brief fichero hpp para las funciones de bajo nivel
	\author Carlos de la Barrera Perez
*/
#ifndef FUNCIONES_BAJO_NIVEL
#define FUNCIONES_BAJO_NIVEL
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <vector>
#include <unistd.h>
using namespace std;

//Esta función divide la cadena c en dos subcadenas c1 y c2, siendo ambas del mismo tamaño cuando el número de caracteres de c es par
//y c1 tendrá un caracter más cuando c tenga un número impar de caracteres.

/**
 * @brief      Divide la cadena c en dos subcadenas c1 y c2 siendo ambas del
 *             mismo tamaño cuando el numero de caracteres de es par y c1 tendrá
 *             un caracter mas cuando c tenga un numero impar de caracteres
 *
 * @param[in]  c     Cadena que se subdividira
 * @param      c1    Subdivision 1
 * @param      c2    Subdivision 2
 */
void partirCadena(string c, string &c1, string &c2);


/**
 * @brief      Añade ceros al final de la cadena c segun el parametro nCeros
 *
 * @param      c       Cadena a la que se le añadiran los ceros
 * @param[in]  nCeros  Numero de ceros a añadir
 */
void agregarCerosFinal(string &c, int nCeros);

//Esta función añade tantos ceros como indica nCeros al principio del número almacenado en la cadena c

/**
 * @brief      Añade ceros al principio de la cadena c segun el parametro nCeros
 *
 * @param      c       Cadena a la que se le añadiran los ceros
 * @param[in]  nCeros  Numero de ceros a añadir
 */
void agregarCerosDelante(string &c, int nCeros);


/**
 * @brief      Quita los ceros sin valor de la cadena
 *
 * @param      c     Cadena a la que se le quitaran los ceros
 */
void quitarCerosNoSignificativos(string &c);


/**
 * @brief      Eleva el numero contenido en una cadena a una potencia de 10
 *
 * @param[in]  c         Cadena que se elevara
 * @param[in]  potencia  Potencia a la que se elevara el numero
 *
 * @return     Cadena con el resultado de aplicar la potencia
 */
string multiplicarPotencia10(string c, int potencia);

#endif

