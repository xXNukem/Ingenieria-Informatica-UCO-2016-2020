/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 3
  \author Carlos de la Barrera Perez
  \date
*/

#ifndef _FuncionesAuxiliares_HPP_
#define _FuncionesAuxiliares_HPP_

#include "Grafo.hpp"

#include <iomanip>

namespace ed
{

	int menu();

//! \name Funciones auxiliares

		/*! 
         \brief     Funcion que carga un fichero de vertices
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        setLabel(),getNumVertices(),insertVertice()
          */

bool cargarFichero(std::string const & nombreFichero, ed::Grafo & g);

	/*! 
         \brief     Funcion que guarda el fichero de vertices
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        getNumVertices(),getVertice(),getVertice(),getX(),getY()
     */

void grabarFichero(std::string const & nombreFichero, ed::Grafo const & g);

	/*! 
         \brief     Muestra por pantalla la matriz de adyacencia y el vector de vertices
         \note      Codificada en el cpp
         \pre       El vector de vertices ha de tener al menos dos componentes
         \post      Ninguna
         \sa        getNumVertices(),printM(),printV()
     */

void datosGrafo(ed::Grafo const & g);

void algoritmoKruskal(ed::Grafo  const & g,ed::Grafo & grafo);

void algoritmoPrim(ed::Grafo const & g, ed::Grafo & grafo);

} 

// Fin de _FuncionesAuxiliares_HPP_
#endif

