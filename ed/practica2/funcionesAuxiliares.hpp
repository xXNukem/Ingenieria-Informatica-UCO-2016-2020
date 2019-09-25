/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 2
  \author 
  \date  
*/

#ifndef _FUNCIONESAUXILIARES_HPP_
#define _FUNCIONESAUXILIARES_HPP_

#include "Provincia.hpp"


// SE DEBEN INCLUIR LOS COMENTARIOS DE DOXYGEN DE CADA FUNCIÓN

namespace ed
{

  int menu();

	///////////////////////////////////////////////////////////////////
   /*! 
  \brief  Comprueba si hay municipios en la provincia
  \warning Ninguna
  \param   Ninguno
  \note    Se realizará en el .cpp
  \return  Ninguna
  \pre     Ninguna
  \post    Ninguna
  \sa      hay municipios()
 */
  
	void comprobarProvinciaVacia(ed::Provincia & provincia);

	///////////////////////////////////////////////////////////////////
 /*! 
  \brief  Carga un fichero de provincia
  \warning Ninguna
  \param   Objeto de tipo provincia
  \note    Se realizará en el .cpp
  \return  Ninguna
  \pre     Ninguna
  \post    Ninguna
  \sa      getNombre(),cargarFichero()
 */

	void cargarProvincia(ed::Provincia & provincia);
/*! 
  \brief  Guarda un fichero con las modificaciones realizadas
  \warning Ninguna
  \param   Objeto de tipo provincia
  \note    Se realizará en el .cpp
  \return  Ninguna
  \pre     Ninguna
  \post    Ninguna
  \sa      grabarFichero()
 */

	void grabarProvincia(ed::Provincia & provincia);

	///////////////////////////////////////////////////////////////////
	/*! 
  \brief  Muestra los datos de una provincia
  \warning Ninguna
  \param   Objeto de tipo provincia
  \note    Se realizará en el .cpp
  \return  Ninguna
  \pre     Ninguna
  \post    Ninguna
  \sa      getNombre(),getCodigo(),getNumeroMunicipios(),getTotalHombres(),getTotalMujeres(),getTotalHabitantes()
 */


	void consultarDatosDeProvincia(ed::Provincia & provincia);
	/*! 
  \brief  Muestra por pantalla los municipios de una provincia
  \warning Ninguna
  \param   Objeto de tipo provincia
  \note    Se realizará en el .cpp
  \return  Ninguna
  \pre     Ninguna
  \post    Ninguna
  \sa      escribirMunicipios()
 */

	void mostrarMunicipiosDeProvincia(ed::Provincia & provincia);

	///////////////////////////////////////////////////////////////////
		/*! 
  \brief  Modifica los datos de una provincia
  \warning Ninguna
  \param   Objeto de tipo provincia
  \note    Se realizará en el .cpp
  \return  Ninguna
  \pre     Ninguna
  \post    Ninguna
  \sa      getNombre(),getCodigo(),setNombre(),setCodigo
 */



	void modificarDatosDeProvincia(ed::Provincia & provincia);
	/*! 
  \brief  Borra todos los municipios de la provincia
  \warning Ninguna
  \param   Objeto de tipo provincia
  \note    Se realizará en el .cpp
  \return  Ninguna
  \pre     Ninguna
  \post    Ninguna
  \sa      borrarTodoslosMunicipios(),hayMunicipios()
 */


	void borrarTodosLosMunicipiosDeProvincia(ed::Provincia & provincia);


	///////////////////////////////////////////////////////////////////

		/*! 
  \brief  Muestra los datos de un municipio por pantalla
  \warning Ninguna
  \param   Objeto de tipo provincia
  \note    Se realizará en el .cpp
  \return  Ninguna
  \pre     Ninguna
  \post    Ninguna
  \sa      hayMunicipios(),existeMunicipio(),getMunicipio(),getNombre(),getCodigoPostal(),getHombres(),getMujeres()
 */


	void consultarMunicipioDeProvincia(ed::Provincia & provincia);
		/*! 
  \brief Inserta un nuevo municipio en la provincia
  \warning Ninguna
  \param   Objeto de tipo provincia
  \note    Se realizará en el .cpp
  \return  Ninguna
  \pre     Ninguna
  \post    Ninguna
  \sa      getNombre(),existeMunicipio(),setNombre(),setCodigoPostal(),setHombres(),setMujeres(),insertarMunicipio()
 */

	void insertarMunicipioEnProvincia(ed::Provincia & provincia);
/*! 
  \brief Borra un municipio de la provincia
  \warning Ninguna
  \param   Objeto de tipo provincia
  \note    Se realizará en el .cpp
  \return  Ninguna
  \pre     Ninguna
  \post    Ninguna
  \sa      getNombre(),getNumeroMunicipios(),existeMunicipio(),borrarMunicipio()
 */

	void borrarMunicipioDeProvincia(ed::Provincia & provincia);


} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FUNCIONESAUXILIARES_HPP_
#endif

