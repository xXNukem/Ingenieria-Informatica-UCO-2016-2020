/*!
	\file MonticuloMediciones.hpp
	\brief Se define el TAD MonticuloMediciones.
	\author Carlos de la Barrera Perez
	\date 2018-3-7
*/

#ifndef _MONTICULO_MEDICIONES_HPP
#define _MONTICULO_MEDICIONES_HPP

#include <vector>

#include <cassert>

#include "Medicion.hpp"

#include "MonticuloMedicionesInterfaz.hpp"




namespace ed
{

//! \name Definicion de la clase MonticuloMediciones
/**
* @brief Clase MonticuloMediciones
*/
class MonticuloMediciones : public MonticuloMedicionesInterfaz
{
	private:

		//! \name Atributos privados de la clase MonticuloMediciones
			std::vector<Medicion> _mediciones;

		//! \name Métodos privados de la clase MonticuloMediciones

		/*! 
         \brief    	Devuleve la medicion correspondiente al indice que se le pasa
         \note      Codificada en el cpp
         \pre       El indice pasado por argumento no puede estar por debajo de 0 ni por encima del tamaño
         \post      Ninguna
         \sa        size()
          */
			Medicion getElement(int x)const;
				/*! 
         \brief    	Modifica el valor de una medicion segun el indice que se le pase
         \note      Codificada en el cpp
         \pre       El indice pasado por argumento no puede estar por debajo de 0 ni por encima del tamaño
         \post      El elemento correspondiente a la posicion que se le pasa debe ser el elemento que se le ha pasado
         \sa        size(),getElement()
          */
			void setElement(int x, Medicion const & m);
			/*! 
         \brief    	Devuelve el indice correspondiente al hijo izquierdo del indice de un nodo padre que se le pasa
         \note      Codificada en el cpp
         \pre       El indice que se le pasa debe ser mayor que 0
         \post      El indice del hijo debe ser 2*x+1
         \sa        Ninguna
          */
			int getLeftChild(int x)const;
				/*! 
         \brief    	Devuelve el indice correspondiente al hijo derecho del indice de un nodo padre que se le pasa
         \note      Codificada en el cpp
         \pre       El indice que se le pasa debe ser mayor que 0
         \post      El indice del hijo debe ser 2*x+2
         \sa        Ninguna
          */
			int getRightChild(int x)const;
					/*! 
         \brief    	Devuelve el indice correspondiente al padre del nodo del indice que se le pasa
         \note      Codificada en el cpp
         \pre       Ninguna
         \post     	El indice devuelto debe ser x-1/2
         \sa       	Ninguna
          */
			int getParent(int x)const;
			/*! 
         \brief    	Mueve un elemento mayor hacia arriba en el monticulo hasta verificar la ordenacion de maximos
         \note      Codificada en el cpp
         \pre       Ninguna
         \post     	Si no estas en la cabeza el elemento actual debe ser mayor o igual a sus hijo.
         			Si tiene hijo izquierdo el elemento actual debe ser mayor o igual a el y lo mismo para el hijo derecho 
         \sa       	getParent(),getElement(),getLeftChild(),getRightChild()
          */
			void shiftUp(int x);
			/*! 
         \brief    	Mueve un elemento menor hacia abajo en el monticulo hasta verificar la ordena
         \note      Codificada en el cpp
         \pre       Ninguna
         \post     	Si no estas en la cabeza el elemento actual debe ser menor o igual a sus hijo.
         			Si tiene hijo izquierdo el elemento actual debe ser menor o igual a el y lo mismo para el hijo derecho 
         \sa       	getParent(),getElement(),getLeftChild(),getRightChild()
          */
			void shiftDown(int x);

			/*! 
         \brief    	Busca una medicion en el monticulo
         \return 	True si encuentra la medicion y false si no
         \note      Codificada en el cpp
         \pre       Ninguna
         \post     	Ninguna
         \sa       	begin(),end()
          */
			bool has(Medicion const &m);

		// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN

	  /////////////////////////////////////////////////////////////////////////////////////

	//! \name Métodos públicos de la clase MonticuloMediciones
	public:

		//! \name Constructor
			/*! 
         \brief    	Constructor vacio de la clase
         \return 	Nada
         \note      Funcion inline
         \pre       Ninguna
         \post     	Ninguna
         \sa       	Nada
          */
			MonticuloMediciones()
			{

			}

		//! \name Observadores

				/*! 
         \brief    	Comprueba si el monticulo esta vacio
         \return 	True si esta vacio, false si no lo esta
         \note      Codificada en el cpp
         \pre       Ninguna
         \post     	si esta vacio el tamaño del monticulo es 0 sino es distinto de 0
         \sa       	size()
          */
			bool isEmpty()const;
				/*! 
         \brief    	Devuelve el tamaño del monticulo
         \return 	Entero con el tamaño del monticulo
         \note      Codificada en el cpp
         \pre       Ninguna
         \post     	Ninguna
         \sa       	size()
          */
			int size()const;
					/*! 
         \brief    	Devuelve el elemento de la cima del monticulo
         \return 	Objeto de tipo medicion que contiene el elemento de la cima del monticulo
         \note      Codificada en el cpp
         \pre       El monticulo no debe estar vacio
         \post     	el elemento devuelto es igual al de la cima
         \sa       	getElement(),isEmpty(),getElement()
          */
			Medicion const top()const;
			

		////////////////////////////////////////////////////////////

		//! \name Operaciones de modificación

			/*! 
         \brief    	Inserta una nueva medicion en el monticulo
         \note      Codificada en el cpp
         \pre       Ninguna
         \post     	El elemento insertado debe estar en el monticulo y el monticulo no estar vacio
         \sa       	getFecha(),pushBack(),shiftUp(),begin(),end()
          */
			void insert(Medicion const &m);
			/*! 
         \brief    	Elimina la cabeza del monticulo
         \note      Codificada en el cpp
         \pre       Ninguna
         \post     	El monticulo no debe estar vacio
         \sa       	size(),isempty(),erase(),shiftDown()
          */
			void remove();
				/*! 
         \brief    	Elimina todos los elementos del monticulo
         \note      Codificada en el cpp
         \pre       Ninguna
         \post     	El monticulo esta vacio
         \sa       	clear()
          */
			void removeAll();
					/*! 
         \brief    Asigna un monticulo a otro
         \note      Codificada en el cpp
         \pre       El monticulo no debe estar vacio
         \post     	La medicion que se le pasa debe encontrarse en el monticulo
         \sa       	shiftDown()
          */
			void modify(Medicion const &m);
			

		//! \name Operadores
   					/*! 
         \brief    Asigna un monticulo a otro monticulo
         \note      Codificada en el cpp
         \pre      	el monticulo que recibe debe ser distinto al que se le asigna
         \post     	Ninguna
         \sa       	Nada
          */
			MonticuloMediciones operator=(MonticuloMediciones const &mm);

 


		////////////////////////////////////////////////////////////////////

		//! \name Función de escritura

				/*! 
         \brief   Muestra mediciones por pantalla
         \note      Codificada en el cpp
         \pre      	Ninguna
         \post     	Ninguna
         \sa       	size(),clear(),ignore(),getElement(),getFecha(),strcmp(),getDia(),getMes(),getAgno(),getChar()
          */
			void print();
		// COMPLETAR

	}; // Clase MonticuloMediciones

} // Espacio de nombres ed


#endif // _MONTICULO_MEDICIONES_HPP
