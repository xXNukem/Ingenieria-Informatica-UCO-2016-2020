
/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 1
  \author 
  \date  
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
	/*! 
  \brief   Lee los vectores
  \warning Ninguna
  \note    Codificada en el funcionesAuxiliares.hpp
  \return  Nada
  \pre     Ninguna
  \post   Nada
  \sa     leerVector3D()
 */   
	void leerVectores(ed::Vector3D &u, ed::Vector3D &v, ed::Vector3D &w);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	/*! 
  \brief   Muestra los vectores
  \warning Ninguna
  \note    Codificada en el funcionesAuxiliares.hpp
  \return  Nada
  \pre     Ninguna
  \post   Nada
  \sa     escribirVector3D()
 */  
	void escribirVectores(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D const &w);


	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
		/*! 
  \brief   Muestra el resultado de ejecutar los observadores
  \warning Ninguna
  \note    Codificada en el funcionesAuxiliares.hpp
  \return  Nada
  \pre     Ninguna
  \post   Nada
  \sa     escribirVector3D(),modulo(),angulo(),alfa(),beta(),gamma(),get1(),get2(),get3()
 */  
	void observadoresDeVectores(ed::Vector3D const &u, ed::Vector3D const &v);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
			/*! 
  \brief   Aplica operaciones a los vectores
  \warning Ninguna
  \note    Codificada en el funcionesAuxiliares.hpp
  \return  Nada
  \pre     Ninguna
  \post   Nada
  \sa     sumConst(),multConst(),sumVect(),multVect()
 */  
	void modificarVector(ed::Vector3D &u, ed::Vector3D const &v, double k);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
			/*! 
  \brief   Escribe el producto escalar
  \warning Ninguna
  \note    Codificada en el funcionesAuxiliares.hpp
  \return  Nada
  \pre     Ninguna
  \post   Nada
  \sa     dotproduct()
 */  
	void mostrarProductoEscalar(ed::Vector3D const &u, ed::Vector3D const &v); 

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
				/*! 
  \brief   Escribe el producto escalar
  \warning Ninguna
  \note    Codificada en el funcionesAuxiliares.hpp
  \return  Nada
  \pre     Ninguna
  \post   Nada
  \sa     crossProduct(),modulo()
 */  
	void mostrarProductoVectorial(ed::Vector3D const &u, ed::Vector3D const &v);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
				/*! 
  \brief   Escribe el producto mixto
  \warning Ninguna
  \note    Codificada en el funcionesAuxiliares.hpp
  \return  Nada
  \pre     Ninguna
  \post   Nada
  \sa     productoMixto(),modulo()
 */
	void mostrarProductoMixto(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D const &w);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
				/*! 
  \brief   Muestra el resultado de aplicar los operadores
  \warning Ninguna
  \note    Codificada en el funcionesAuxiliares.hpp
  \return  Nada
  \pre     Ninguna
  \post   Nada
  \sa     +,-,*,^,<<,>>
 */
	void mostrarOperadores(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D &w,  double k);



} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FUNCIONESAUXILIARES_HPP_
#endif

