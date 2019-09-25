/*!
	\file Grafo.hpp
	\brief Se define el TAD Grafo.
	\author Carlos de la Barrera Perez
	\date
*/

#ifndef _GRAFO_HPP
#define _GRAFO_HPP

#include <vector>

#include <iomanip>

#include <cassert>

#include "Vertice.hpp"

#include "Lado.hpp"

#include <cmath>


namespace ed
{



class Grafo
{
	private:

		//! \name Atributos privados de la clase Grafo		
		
		std::vector<std::vector<float> > _matriz;

		std::vector<ed::Vertice> _v;

		//! \name Métodos públicos de la clase Grafo
	public:

		//! \name Constructor

			/*! 
         \brief     Constructor vacio de la clase grafo
         \note      Codificada inline
         \pre       Ninguna
         \post      Ninguna
         \sa       	Ninguna
          */

		Grafo() 
		{

		}

		//! \name Observadores

			/*! 
         \brief    	Muestra por pantalla la matriz de adyacencia
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        getNumVertices()
          */

		void printM()const;

			/*! 
         \brief    	Muestra por pantalla el vector de vertices
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        getNumVertices()
          */

		void printV()const;

		/*! 
         \brief     Devuleve un vertice del vector de vertices segun el indice que se le pasa
         \note      Codificada en el cpp
         \pre       El vertice debe existir
         \post      Ninguna
         \sa        setLabel(),getNumVertices(),insertVertice()
          */

		ed::Vertice getVertice(int  i)const ;

		/*! 
         \brief     Devuleve el numero de vertices almacenados en el vector de vertices
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        size()
          */

		int getNumVertices()const ;

		/*! 
         \brief     Calcula la distancia euclidea entre dos vertices
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      El valor devuelto deber ser igual a la distancia euclidea entre dos vertices
         \sa        getX(),getY()
          */

		float calcularDistanciaEuclidea ( ed::Vertice v1, ed::Vertice v2 ) ;

		vector <ed::Vertice> getVectorVertices()const;

		/*! 
         \brief     Comprueba si el vertice que se le pasa existe en el vector de vertices
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguno
         \sa        getNumVertices()
          */

		bool existeVertice(ed::Vertice const & v)const;


		////////////////////////////////////////////////////////////

		//! \name Operaciones de modificación

		/*! 
         \brief     Lee un vertice por teclado y lo inserta en la matriz
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      El vertice existe
         \sa       	setX(),setY(),insertVertice(),setLabel()
          */

		void leerVerticeInsertar();

		/*! 
         \brief     Lee un vertice por teclado y lo borra
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      El vertice no existe
         \sa       	setX(),setY(),borrarVertice(),setLabel()
          */

		void leerVerticeBorrar();

		void setVectorVertices(vector <ed::Vertice> v);

		/*! 
         \brief     Insertar un vertice en el vector de vertices y calculo su distancia euclidea para insertarla en la matriz de adyacencias
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      El vertice debe existir
         \sa       	getNumVertices(),calcularDistanciaEuclidea(),getVertice(),getLabel()
          */

		void insertVertice(ed::Vertice & v);

		/*! 
         \brief    Borra un vertice del vector de vertices y elimina su peso de la matriz de adyacencia
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      El vertice no debe existir
         \sa        getNumVertices(),setLabel()
          */

		void borrarVertice(ed::Vertice & v);

		void insertarVertice(ed::Vertice & v);

		void insertarMatriz(int x, int y, float distancia);

		//! \name Operadores

		/*! 
         \brief    Operador de asignacion de la clase grafo
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        Ninguna
          */


		Grafo operator=(Grafo & g);

		// COMPLETAR

}; // Clase Grafo
} // Espacio de nombres ed


#endif // _GRAFO_HPP
