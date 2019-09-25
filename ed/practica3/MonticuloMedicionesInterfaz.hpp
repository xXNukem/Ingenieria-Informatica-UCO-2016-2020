/*!
	\file MonticuloMedicionesInterfaz.hpp
	\brief Se define la interfaz del TAD MonticuloMediciones.
	\author 
	\date  
*/

#ifndef _MONTICULO_MEDICIONES_INTERFAZ_HPP
#define _MONTICULO_MEDICIONES_INTERFAZ_HPP

#include "Medicion.hpp"



namespace ed
{


/**
* @brief Clase MonticuloMediciones
*/
	class MonticuloMedicionesInterfaz
	{
		public:
			//! \name Metodos virtuales puros
					/*! 
         \brief    	Comprueba si el monticulo esta vacio
         \return 	True si esta vacio, false si no lo esta
         \note      Codificada en el cpp
         \pre       Ninguna
         \post     	si esta vacio el tamaño del monticulo es 0 sino es distinto de 0
         \sa       	size()
          */
			virtual bool isEmpty()const=0;
						/*! 
         \brief    	Devuelve el elemento de la cima del monticulo
         \return 	Objeto de tipo medicion que contiene el elemento de la cima del monticulo
         \note      Codificada en el cpp
         \pre       El monticulo no debe estar vacio
         \post     	el elemento devuelto es igual al de la cima
         \sa       	getElement(),isEmpty(),getElement()
          */
			virtual ed::Medicion const  top()const=0;
			/*! 
         \brief    	Inserta una nueva medicion en el monticulo
         \note      Codificada en el cpp
         \pre       Ninguna
         \post     	El elemento insertado debe estar en el monticulo y el monticulo no estar vacio
         \sa       	getFecha(),pushBack(),shiftUp(),begin(),end()
          */
			virtual void insert(ed::Medicion const &m)=0;
					/*! 
         \brief    	Elimina todos los elementos del monticulo
         \note      Codificada en el cpp
         \pre       Ninguna
         \post     	El monticulo esta vacio
         \sa       	clear()
          */
			virtual void remove()=0;

	}; // Clase MonticuloMedicionesInterfaz

} // Espacio de nombres ed

#endif //  _MONTICULO_MEDICIONES_INTERFAZ_HPP
