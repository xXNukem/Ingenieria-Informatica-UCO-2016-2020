/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 3
  \author Carlos de la Barrera Perez
  \date  2018-3-7
*/

#ifndef _FuncionesAuxiliares_HPP_
#define _FuncionesAuxiliares_HPP_

#include "MonticuloMediciones.hpp"

// SE DEBEN INCLUIR LOS COMENTARIOS DE DOXYGEN

namespace ed
{
	//! \name Funcion de menu
		/*! 
         \brief     Funcion que muestra el menu por pantalla   
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        ignore()
          */
	int menu();

	//! \name Funciones adicionales de programa principal

		/*! 
         \brief    	Muestra una serie de datos de la informacion que tien el monticulo por pantalla  
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        isEmpty(),top(),remove(),getFecha(),getPrecipitacion(),getMes(),getAgno(),size()
          */
	void datosMonticulo(ed::MonticuloMediciones const &monticulo);
	/*! 
         \brief    	Inserta una nueva precipitacion en el monticulo y la ordena
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        leerFecha(),setPrecipitacion(),setFecha(),insert()
          */
	void insertarPrecipitacion(ed::MonticuloMediciones &monticulo);
	/*! 
         \brief    	Genera un documento HTML con un grafico circular de precipitaciones por mes 
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        isEmpty(),top(),remove(),getFecha(),getPrecipitacion(),getMes(),getAgno(),size(),close()
          */
	void generarArbolGrafico(ed::MonticuloMediciones const &monticulo);
	/*! 
         \brief    	Genera un documento HTML con un grafico de barras 
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        isEmpty(),top(),remove(),getFecha(),getPrecipitacion(),getMes(),getAgno(),size(),close()
          */
	void generarArbolGrafico2(ed::MonticuloMediciones const &monticulo);
		/*! 
         \brief    	Elimina todas las mediciones del monticulo
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        removeAll(),isEmpty()
          */
	void vaciarMonticulo(ed::MonticuloMediciones &monticulo);
	/*! 
         \brief    	Elimina tantas mediciones como se le introduzcan por teclado
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        removeAll(),isEmpty()
          */
	void borrarMediciones(ed::MonticuloMediciones &monticulo);

  /*! 
         \brief     Busca una fecha e imprime su precipitacion.
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        removeAll(),isEmpty()
          */

  void buscarFecha(ed::MonticuloMediciones const &monticulo);

	//! \name Funciones de ficheros

		/*! 
         \brief    	Carga un fichero que se le introduce por teclado o por argumento si estamos en el programa de prueba
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        leerFecha(),remove(),top(),getFecha(),getPrecipitacion()
          */
	bool cargarMonticuloDeFichero(std::string const & nombreFichero, ed::MonticuloMediciones & monticulo); 

			/*! 
         \brief    	Crea un nuevo fichero apartir del monticulo cargado en el programa 
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        size(),devolverMedicion(),getFecha(),getPrecipitacion(),close()
          */
	void grabarMonticuloEnFichero (std::string const & nombreFichero, ed::MonticuloMediciones const & monticulo); 


} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FuncionesAuxiliares_HPP_
#endif

