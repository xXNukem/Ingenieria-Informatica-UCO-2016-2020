/*! 	
	\file   NodoMunicipioInterfaz.hpp
	\brief  Declaración de la clase NodoMunicipioInterfaz: nodo que contiene como campo informativo a un Municipio
	\author 
	\date 
	\version 

*/

#ifndef _NODOMUNICIPIOINTERFAZ_HPP_
#define _NODOMUNICIPIOINTERFAZ_HPP_

#include "Municipio.hpp"

/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed{


/*!
  \class NodoMunicipioInterfaz
  \brief Definición de la clase abstracta NodoMunicipioInterfaz
*/
class NodoMunicipioInterfaz
{

//! \name Funciones o métodos públicos de la clase Nodo
	public:


  /*!
    \brief Destructor de la clase 
   	\warning Función virtual pura: se debe redefinir en la clase heredera
    \attention Es necesario especificar esta función para liberar memoria en la clase heredera
  */
	virtual ~NodoMunicipioInterfaz()
   {
      // Se debe redefinir en la clase heredera
   }

//! \name Observador

/*!	
	\brief   Método público que permite conocer el campo informativo del nodo: un municipio
	\warning Función virtual pura: se debe redefinir en la clase heredera
	\pre     Ninguna
	\post    Ninguna
    \return  Devuelve una referencia constante a un Municipio
*/
	virtual const ed::Municipio & getItem() const = 0;


//! \name Observador

/*!	
	\brief   Método público que permite modificar el campo informativo del nodo: un municipio
	\warning Función virtual pura: se debe redefinir en la clase heredera
	\param   item: referencia constante a un Municipio	
    \return  void	
	\pre     Ninguna
	\post    El valor del campo informativo debe ser igual al item pasado como argumento
*/
	virtual void  setItem(ed::Municipio const &item) = 0;

// Fin de la clase NodoMunicipioInterfaz
}; 

// Fin del espacio de nombres ed
}

//Fin  _NODOMUNICIPIOINTERFAZ_HPP_
#endif  
