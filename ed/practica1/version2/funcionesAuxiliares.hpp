
/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 1
  \author Carlos de la Barrera Perez
  \date  2018-1-23
*/

#ifndef _FUNCIONESAUXILIARES_HPP_
#define _FUNCIONESAUXILIARES_HPP_

#include "Vector3D.hpp"


namespace ed
{
	/*! 
		\brief   Muestra el menú del programa principal 
		\return  Devuelve el número de opción elegido
	*/
	int menu();

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	void leerVectores(ed::Vector3D &u, ed::Vector3D &v, ed::Vector3D &w);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	void escribirVectores(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D const &w);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	void observadoresDeVectores(ed::Vector3D const &u, ed::Vector3D const &v);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	void modificarVector(ed::Vector3D &u, ed::Vector3D const &v, double k);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	void mostrarProductoEscalar(ed::Vector3D const &u, ed::Vector3D const &v); 

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	void mostrarProductoVectorial(ed::Vector3D const &u, ed::Vector3D const &v);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	void mostrarProductoMixto(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D const &w);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	void mostrarOperadores(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D &w,  double k);



} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FUNCIONESAUXILIARES_HPP_
#endif

