/*!
	\file   ListaDoblementeEnlazadaOrdenadaMunicipios.hpp
	\brief  Clase de una lista doblemente enlazada y ordenada de Municipios
	\author  
	\date  
	\version 1.0

*/

#ifndef __ListaDoblementeEnlazadaOrdenadaMunicipios_HPP__
#define __ListaDoblementeEnlazadaOrdenadaMunicipios_HPP__

// Para comprobar las pre y post-condiciones
#include <cassert>

#include "ListaOrdenadaMunicipiosInterfaz.hpp"

#include "NodoDoblementeEnlazadoMunicipio.hpp"

#include "Municipio.hpp"

// DEBES ESPECIFICAR LAS FUNCIONES DE LA CLASE ListaDoblementeEnlazadaOrdenadaMunicipios


/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos

*/ 
namespace ed {
 
/*!	
  \class ListaDoblementeEnlazadaOrdenadaMunicipios 
  \brief Definición de la clase ListaDoblementeEnlazadaOrdenadaMunicipios
	  	\n Lista doblemente enlazada de nodos de municipios ordenados alfabéticamente de forma ascendente 
*/

  class ListaDoblementeEnlazadaOrdenadaMunicipios: public ed::ListaOrdenadaMunicipiosInterfaz
  {
	//! \name  Atributos y métodos privados 

	private:
		ed::NodoDoblementeEnlazadoMunicipio *_head;    //!< \brief puntero al primer nodo de la lista
		ed::NodoDoblementeEnlazadoMunicipio *_current; //!< \brief puntero al nodo current de la lista

    // \name Observadores privados 

    inline ed::NodoDoblementeEnlazadoMunicipio * getHead() const
	{
		return this->_head;
	}

	inline ed::NodoDoblementeEnlazadoMunicipio * getCurrent() const
	{
		return this->_current;
	}

    //! \name Modificadores privados 

	inline void setHead(ed::NodoDoblementeEnlazadoMunicipio *head) 
	{
		this->_head = head;

		#ifndef NDEBUG
			// Se comprueba la postcondición
			assert(this->getHead() == head);
		#endif //NDEBUG		
	}

    inline void setCurrent(ed::NodoDoblementeEnlazadoMunicipio *current) 
	{
		this->_current = current;

		#ifndef NDEBUG
			// Se comprueba la postcondición
			assert(this->getCurrent() == current);
		#endif //NDEBUG		
	}


	//! \name  Métodos públicos

	public:

	//! \name Constructores

    /*! 
		\brief Construye una lista vacía
		\note  Función inline
		\post  isEmpty() == true
	*/
	inline ListaDoblementeEnlazadaOrdenadaMunicipios()
    {
		 setHead(NULL);
		 setCurrent(NULL);

		 	#ifndef NDEBUG
		 		assert(isEmpty()==true);
		 	#endif
	}
	 
	//! \name Destructor 

    /*! 
		\brief Destruye una lista liberando la memoria de sus nodos
		\note Función codificada en el fichero cpp
		\post isEmpty() == true
	*/
	~ListaDoblementeEnlazadaOrdenadaMunicipios ()
     {
		  setCurrent(NULL);
		  setHead(NULL);

		  	#ifndef NDEBUG
		 		assert(isEmpty()==true);
		 	#endif
     }


	//! \name Observadores públicos 

	/*!
		\brief  Comprueba si la lista está vacía
		\note   Función inline
		\note   Función de tipo "const": no puede modificar al objeto actual
        \return true, si la lista está vacía; false, en caso contrario
    */
	inline bool isEmpty() const
	{
  		bool x;
  		if(_head==NULL && _current==NULL)
  		{
  			x=true;
  		}
  		else
  		{
  			x=false;
  		}

		return x;
	}

	// COMPLETAR EL RESTO DE OBSERVADORES PÚBLICOS
	    /*! 
  \brief   Devuelve el numero de elementos de la lista
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Numero de elementos de la lista
  \pre     Ninguna
  \post    Ninguna
  \sa      getHead(),getNext()
 */

	int nItems()const;
		    /*! 
  \brief   Comprueba si el cursor esta en el primer elemento
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  True si esta en el primer elemento, false si no.
  \pre     isEmpty()==false
  \post    Ninguna
  \sa      isEmpty(),getCurrent(),getHead()
 */
	bool isFirstItem()const;
			    /*! 
  \brief   Comprueba si el cursor esta en el ultimo elemento
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  True si esta en el ultimo elemento, false si no
  \pre     isEmpty()==false
  \post    Ninguna
  \sa      isEmpty(),getCurrent(),getHead()
 */
	bool isLastItem()const;
			    /*! 
  \brief   Devuelve los datos del elemento en el que se encuentra el cursor actualmente
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Elemento actual de la lista
  \pre     isEmpty()==false
  \post    Ninguna
  \sa      isEmpty(),getCurrent(),getItem()
 */
	Municipio const & getCurrentItem() const;
				    /*! 
  \brief   Devuelve los datos del elemento que se encuentra en la posicion anterior al cursor
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Elemento anterior
  \pre     isEmpty()==false
  			isFirstItem()==false
  \post    Ninguna
  \sa      isEmpty(),getPrevious(),getItem()
 */
	Municipio const & getPreviousItem() const;
	 /*! 
  \brief   Devuelve los datos del elemento que se encuentra en la posicion posterior al cursor
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Elemento posterior
  \pre     isEmpty()==false
  			isFirstItem()==false
  \post    Ninguna
  \sa      isEmpty(),getNext(),getItem()
 */
	Municipio const & getNextItem() const;
    //! \name Modificadores públicos

	// COMPLETAR EL RESTO DE MODIFICADORES PÚBLICOS
	 /*! 
  \brief   Manda el cursor a la cabeza
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Nada
  \pre     isEmpty()==false
  \post   	isFirstItem()==true
  \sa      setCurrent(),getHead(),isEmpty(),isFirstItem()
 */
	void gotoHead();
	 /*! 
  \brief   MAnda el cursor al final de la lista
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Nada
  \pre     isEmpty()==false
  \post   	isLastItem()==true
  \sa      isEmpty(),getNext(),getHead(),setCurrent(),isLastItem()
 */
	void gotoLast();
		 /*! 
  \brief   Manda el cursor al elemento anterior
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Nada
  \pre     isEmpty()==false
		isFirstItem()==false
  \post   	Ninguna
  \sa      isEmpty(),isLastItem(),setCurrent(),getCurrent(),getPrevious()
 */
	void gotoPrevious();
		 /*! 
  \brief   Manda el cursor al elemento posterior
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Nada
  \pre     isEmpty()==false
			isLasttItem()==false
  \post   	Ninguna
  \sa      isEmpty(),isLastItem(),setCurrent(),getCurrent(),getNext()
 */
	void gotoNext();
			 /*! 
  \brief   Encuentra un elemento determinado en la lista
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Nada
  \pre     Ninguna
  \post   	getCurrentItem()==item
			item<getCurrentItem() or isLastItem()==true
  \sa      isEmpty(),goToHead(),isLastItem(),getCurrentItem(),goToNext(),isLastItem()
 */
	bool find(ed::Municipio const & item);

	/*!
		\brief Inserta un Municipio de forma ordenada por apellidos y nombre
		\note  Función virtual pura
		\param item: objeto de la clase Municipio que va a ser insertado; referencia constante de la clase Municipio
		\pre   find(item) == false
 		\post  getCurrentItem() == item
		\sa    remove() 
    */
	void insert(ed::Municipio const & item);
	/*!
		\brief Borra el municipio indicado por el cursor
		\pre   La lista no está vacía: isEmpty()== false
		\post  El número de municipios se reduce en uno
           \n nItems()==old.nItems()-1
    \post  Si old.isFirstItem()==falso y  old.isLastItem()==falso
				   entonces old.getPreviousItem()== getPreviousItem() y old.getNextItem()==getCurrentItem()
		\post  Si old.lastItem()==verdadero entonces
		       isEmpty()==verdadero  
           o old.getPreviousItem()==getCurrentItem() y isLastItem()==verdadero
    \post  Si old.isFirstItem()==verdadero entonces
           isEmpty()==verdadero o old.getNextItem()==getCurrentItem() y isFirstItem()==verdadero
		\sa    insert()
     */
	void remove();
	/*!
		\brief borra todos los elementos de la lista
		\note  Función virtual pura
		\pre   find(item) == false
 		\post  getCurrentItem() == item
		\sa    remove() 
    */
	void removeAll();

}; // Fin de la clase ListaDoblementeEnlazadaOrdenadaMunicipios
 
} //namespace ed
 
#endif // __ListaDoblementeEnlazadaOrdenadaMunicipios_HPP__
