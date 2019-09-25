/*! 	
	\file   NodoDoblementeEnlazadoMunicipio.hpp
	\brief  Declaración del TAD NodoDoblementeEnlazadoMunicipio: nodo doblemente enlazado con el campo informativo Municipio
	\author 
	\date 
	\version 1.0

*/

#ifndef _NodoDoblementeEnlazadoMunicipio_HPP_
#define _NodoDoblementeEnlazadoMunicipio_HPP_

#include "NodoMunicipioInterfaz.hpp"
#include "Municipio.hpp"


/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed{
/*!

  \class NodoDoblementeEnlazadoMunicipio
  \brief Definición de la clase NodoDoblementeEnlazadoMunicipio
  \note  Hereda de la clase NodoMunicipioInterfaz
  \attention Todos los métodos han sido definidos como "inline"
*/
class NodoDoblementeEnlazadoMunicipio: public NodoMunicipioInterfaz
{
//!	\name Atributos o métodos privados

 private:
	Municipio					      _item;      //!< \brief campo informativo del nodo 
	NodoDoblementeEnlazadoMunicipio * _previous;  //!< \brief puntero al nodo previous
	NodoDoblementeEnlazadoMunicipio * _next;      //!< \brief puntero al nodo next


//!	\name Funciones o métodos públicos

	public:

//! \name Constructor

/*!		
	\brief Constructor parametrizado 
	\note  Función inline
  	\param item: campo informativo del nodo, referencia constante a un Municipio 
   	\param previous: puntero al nodo previous
   	\param next: puntero al nodo next
	\pre   Ninguna
  	\post  Crea un nuevo objeto de la clase NodoDoblementeEnlazadoMunicipio con los valores de los argumentos
	  	\sa    setItem, setPrevious, setNext 
*/
	inline NodoDoblementeEnlazadoMunicipio(const ed::Municipio& item, NodoDoblementeEnlazadoMunicipio* previous, NodoDoblementeEnlazadoMunicipio* next)
    {
		this->setItem(item);
		this->setPrevious(previous);
		this->setNext(next);
	}

//!	\name Destructor
 
/*!		
	\brief Destructor
	\note  Función inline
	\pre   Ninguna
	\post  
	\sa   NodoDoblementeEnlazadoMunicipio()
*/
	inline ~NodoDoblementeEnlazadoMunicipio()
	{
		this->setPrevious(NULL);
		this->setNext(NULL);
	}


//! \name Observadores

/*!	
	\brief  Método público que permite conocer el campo informativo del nodo doble
	\note   Función inline
	\return Devuelve el valor del atributo _item
	\pre    Ninguna
	\post   Ninguna
	
*/
	inline ed::Municipio const & getItem()  const
	{
 		return this->_item;
	}


/*!	
	\brief  Método público que permite conocer el puntero al nodo previous
	\note   Función inline
  	\note   Método "const" que no modifica el objeto de la clase
	\pre    Ninguna
	\post   Ninguna
    \return Devuelve el puntero al nodo previous
*/
	inline NodoDoblementeEnlazadoMunicipio  *getPrevious() const 
	{
		return this->_previous;
	}


/*!	
	\brief  Método público que permite conocer el puntero al nodo next
	\note   Función inline
    \note   Metodo "const" que no modifica el objeto de la clase
	\pre    Ninguna
	\post   Ninguna
	\return Devuelve el puntero al nodo next
*/
	inline NodoDoblementeEnlazadoMunicipio  *getNext() const
	{
		return this->_next;
	}


//! \name Modificadores


/*!	
	\brief Método público que permite modificar el campo informativo del nodo doble
	\note  Función inline
    \attention  La clase Municipio debe tener sobrecargado el operador de asignación "="
	\param item: nuevo valor del campo informativo; referencia constante a un Municipio 
	\pre   Ninguna
	\post  El campo informativo del nodo actual es igual al parámetro pasado como argumento
	\return void
*/
	inline void setItem(ed::Municipio const & item)  
	{
		this->_item  = item;
	}		


/*!	
	\brief  Método público que permite modificar el puntero al nodo previous
	\note   Función inline
	\param  previous: nuevo puntero al nodo previous
	\pre    Ninguna
	\post   El nodo previous es igual al parámetro pasado como argumento
			\n getPrevious() == item
	\return void
*/
	inline void setPrevious(NodoDoblementeEnlazadoMunicipio  *previous) 
	{
		this->_previous = previous;
	}

		
/*!	
	\brief  Método público que permite modificar el puntero al nodo next
	\note   Función inline
	\param  next: nuevo puntero al nodo next
	\pre    Ninguna
	\post   El campo informativo es igual al parámetro pasado como argumento
			\n getNext() == item
	\return void
*/
	inline void setNext(NodoDoblementeEnlazadoMunicipio  *next) 
	{
		this->_next = next;
	}
		
// Fin de la clase NodoDoblementeEnlazadoMunicipio
};

// Fin del espacio de nombres ed
}

//Fin  _NodoDoblementeEnlazadoMunicipio_HPP_
#endif  
