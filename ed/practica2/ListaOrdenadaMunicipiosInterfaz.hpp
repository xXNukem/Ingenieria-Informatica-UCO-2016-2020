/*!
	\file   ListaOrdenadaMunicipiosInterfaz.hpp
	\brief  Clase abstracta de una lista enlazada y ordenada de Municipios
	\author  
	\date  
	\version 1.0

*/

#ifndef _ListaOrdenadaMunicipiosInterfaz_HPP_
#define _ListaOrdenadaMunicipiosInterfaz_HPP_

// Definición de la clase del campo informativo del nodo de la lista
#include "Municipio.hpp"


/////////////////////////////////////////////////////////////////////////////////////
// IMPORTANTE

// SE HAN COMENTADO ALGUNAS FUNCIONES PARA QUE NO SE GENEREN ERRORES DE COMPILACIÓN

// AL QUITAR EL COMENTARIO, TAMBIÉN SE DEBE CODIFICAR LA FUNCIÓN EN LA CLASE HEREDERA
/////////////////////////////////////////////////////////////////////////////////////



/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/ 
namespace ed {
 
/*!	
  \class ListaOrdenadaMunicipiosInterfaz 
  \brief Definición de la clase abstracta ListaOrdenadaMunicipiosInterfaz
	  \n  Lista de nodos de municipios ordenados alfabéticamente de forma ascendente
*/
  class ListaOrdenadaMunicipiosInterfaz
  {
    public:

	//! \name Observadores públicos 

    /*!
        \brief  Comprueba si la lista está vacía
		\note   Función virtual pura, que deberá ser redefinida en la clase heredera
        \note   Función de tipo "const": no puede modificar al objeto actual
        \return true, si la lista está vacía; false, en caso contrario
    */
		virtual bool isEmpty() const = 0;


    /*!
        \brief  Devuelve el número de elementos o ítems de la lista
		\note   Función virtual pura, que deberá ser redefinida en la clase heredera
        \note   Función de tipo "const": no puede modificar al objeto actual
        \return Número entero que representa el número de elementos o ítems de la lista
    */
		virtual int nItems() const = 0;

    /*!
		\brief  Comprueba si el cursor está en el primer Municipio
		\note   Función virtual pura, que deberá ser redefinida en la clase heredera
        \note   Función de tipo "const": no puede modificar al objeto actual
		\pre    La lista no está vacía
		\return Verdadero, si el cursor está situado en la cabeza; falso en caso contrario
	*/
 		virtual bool isFirstItem() const = 0;


    /*!
		\brief  Comprueba si el cursor está en el último Municipio
		\note   Función virtual pura, que deberá ser redefinida en la clase heredera
        \note   Función de tipo "const": no puede modificar al objeto actual
		\pre    La lista no está vacía
		\return true, si el cursor está situado al final de la lista; false, en caso contrario
    */
		virtual bool isLastItem() const = 0;


    /*!
		\brief  Devuelve el Municipio situado en el campo informativo indicado por el cursor
		\note   Función virtual pura, que deberá ser redefinida en la clase heredera
        \note   Función de tipo "const": no puede modificar al objeto actual
		\pre    La lista no está vacía
		\return Una referencia constante al municipio indicado por el cursor
    */
		virtual ed::Municipio const & getCurrentItem() const = 0;


    /*!
		\brief  Devuelve el Municipio situado en el campo informativo anterior
		\note   Función virtual pura, que deberá ser redefinida en la clase heredera
        \note   Función de tipo "const": no puede modificar al objeto actual
		\pre    La lista no está vacía 
		\pre    El cursor no está situado en el primer nodo
		\return Una referencia al municipio situado en el nodo previo al indicado por el cursor
    */
		virtual  ed::Municipio const & getPreviousItem() const = 0;


    /*!
		\brief  Devuelve el Municipio situado en el campo informativo posterior
		\note   Función virtual pura, que deberá ser redefinida en la clase heredera
        \note   Función de tipo "const": no puede modificar al objeto actual
		\pre    La lista no está vacía 
		\pre 	El cursor no está situado en el último nodo
        \return Una referencia al municipio situado en el nodo siguiente al indicado por el cursor
    */
		virtual ed::Municipio const & getNextItem() const = 0;


	//!  \name Modificadores públicos

    /*!
		\brief  Coloca el cursor en la primera posición de la lista
		\note   Función virtual pura, que deberá ser redefinida en la clase heredera
        \pre    La lista no está vacía
        \post   El ítem actual es el primero: isFirstItem() == true
		\return void
		\sa		gotoLast(), gotoPrevious(), gotoNext()
      */
      virtual void gotoHead() = 0;


      /*!
		\brief  Coloca el cursor en la última posición de la lista
		\note   Función virtual pura, que deberá ser redefinida en la clase heredera
        \pre    La lista no está vacía
        \post   El ítem actual es el último:  isLastItem() == true
		\return void
		\sa		gotoHead(), gotoPrevious(), gotoNext()
      */
      virtual void gotoLast() = 0;


      /*!
		\brief  Coloca el cursor en la posición anterior de la lista
		\note   Función virtual pura, que deberá ser redefinida en la clase heredera
		\pre    La lista no está vacía
		\pre    El ítem actual no es el primero: isFirstItem() == false
		\post   Ninguna
		\return void
		\sa		gotoHead(), gotoLast(), gotoNext()
      */
      virtual void gotoPrevious() = 0;

	/*!
		\brief  Coloca el cursor en la posición siguiente de la lista
		\note   Función virtual pura, que deberá ser redefinida en la clase heredera
        \pre    La lista no está vacía
        \pre    El ítem actual no es el último: isLastItem() == false
		\post   Ninguna
		\return void
		\sa		gotoHead(), gotoLast(), gotoPrevious()
	*/
      virtual void gotoNext() = 0;

	

	/*!
		\brief  Coloca el cursor en el nodo que contiene al municipio en su campo informativo, si existe;
		\note   Función virtual pura
		\param  item: municipio buscado; referencia constante de la clase Municipio
 		\post   retVal==true implica que getCurrentItem() == item
    \post   retVal==false implica que getCurrentItem > item o isLastItem() == true
		\return true, si el municipio está en la lista; false, en caso contrario
    */
      virtual bool find(ed::Municipio const & item) = 0;

   
	/*!
		\brief Inserta un Municipio de forma ordenada por apellidos y nombre
		\note  Función virtual pura
		\param item: objeto de la clase Municipio que va a ser insertado; referencia constante de la clase Municipio
		\pre   find(item) == false
 		\post  getCurrentItem() == item
		\sa    remove() 
    */
 		virtual void insert(ed::Municipio const & item) = 0;
			

	/*!
		\brief Borra el municipio indicado por el cursor
		\note  Función virtual pura
		\pre   isEmpty()==false
		\post  isEmpty()==true
		\sa    insert()
     */
		virtual void remove() = 0;
			
}; // Fin de la clase ListaOrdenadaMunicipiosInterfaz
 
} //namespace ed
 
#endif // _ListaOrdenadaMunicipiosInterfaz_HPP_
