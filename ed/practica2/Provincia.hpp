/*!	
	\file  Provincia.hpp
	\brief Definición de la clase Provincia
	\author  
	\date  
	\version 

*/

#ifndef _PROVINCIA_HPP_
#define _PROVINCIA_HPP_

// Para comprobar las pre y post condiciones
#include <cassert>

#include <string>


#include "ListaDoblementeEnlazadaOrdenadaMunicipios.hpp"


// DEBES COMPLETAR O MODIFICAR EL CÓDIGO DE LA CLASE Provincia

// DEBES COMPLETAR LOS COMENTARIOS DE DOXYGEN

// IMPORTANTE
// Se incluyen los prototipos de las funciones virtuales que hay que redefinir
// Hay que incluir los prototipos de las demás funciones


/*!	
	\namespace ed
	\brief Espacio de nombres para la Provincia Estructuras de Datos

*/
namespace ed{
/*!	

  \class Provincia
  \brief Definición de la clase Provincia

*/
  //!  Definicion de la clase provincia
class Provincia
{
	//!	\name Métodos públicos de la clase Provincia

	private:
		std::string      _nombre;     //!<  \brief Nombre de la Provincia
		int              _codigo;	  //!<  \brief Código de la Provincia

	  	ed::ListaDoblementeEnlazadaOrdenadaMunicipios _listaMunicipios; //!<  \brief Lista de municipios de la Provincia


	/////////////////////////////////////////////////////////////////////

	//!	\name  Métodos públicos de la clase Provincia

  public: 
//! \name Constructores 

  /*! 
  \brief   Constructor vacio
  \warning Ninguna
  \note    Se realizará en el .hpp
  \return  Ninguna
  \pre     Ninguna
  \post    Ninguna
  \sa      Ninguna
 */

	
	Provincia()
	{

	}
	/*! 
  \brief   Constructor parametrizado
  \warning Ninguna
  \note    Se realizará en el .hpp
  \return  Ninguna
  \pre     Ninguna
  \post    Ninguna
  \sa      Ninguna
 */
  	Provincia(std::string nombre, int codigo)
  	{
  		_nombre=nombre;
  		_codigo=codigo;

  			#ifndef NDEBUG
  				assert(getNombre()==_nombre);
  				assert(getCodigo()==_codigo);
  				assert(hayMunicipios()==false);
  			#endif
  	}
	
	/////////////////////////////////////////////////////////////////////

	//!	\name Observadores

    /*! 
  \brief   Devuelve el nombre de la provincia
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Nombre de la provincia
  \pre     Ninguna
  \post    Ninguna
  \sa      Ninguna
 */
  	std::string getNombre();

   /*! 
  \brief   Devuelve el codigo postal de la provincia
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Codigo postal de la provincia
  \pre     Ninguna
  \post    Ninguna
  \sa      Ninguna
 */
  	int getCodigo();
    /*! 
  \brief   Comprueba si la provincia tiene municipios
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  true si hay municipios en la provincia y false si no los hay
  \pre     Ninguna
  \post    Ninguna
  \sa      Ninguna
 */
  	bool hayMunicipios();
       /*! 
  \brief   Devuelve el numero de municipios de la provincia
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Numero de municipios que tiene la provincia
  \pre     Ninguna
  \post    Ninguna
  \sa      Ninguna
 */
  	int getNumeroMunicipios();
          /*! 
  \brief   Comprueba si un municipio determinado existe
  \warning Ninguna
  \param   Cadena de caracteres con el nombre del municipio
  \note    Se realizará en el .cpp
  \return  true si el municipio que se le pasa existe y false si no existe
  \pre     Ninguna
  \post    Ninguna
  \sa      hayMunicipios(),setNombre(),find()
 */
  	bool existeMunicipio(std::string const &nMunicipio);
          /*! 
  \brief   Devuelve los datos de un municipio
  \warning Ninguna
  \param   Cadena de caracteres con el nombre del municipio
  \note    Se realizará en el .cpp
  \return  Informacion del municipio que se le pasa
  \pre     Ninguna
  \post    Ninguna
  \sa      setNombre(),existeMunicipio(),find(),getCurrentItem()
 */
  	ed::Municipio getMunicipio(std::string const&nMunicipio);
             /*! 
  \brief   Cuenta el total de hombres de la provincia
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Numero total de hombres del municipio
  \pre     Ninguna
  \post    Ninguna
  \sa      goToHead(),nItems(),getCurrentItems,getHombres(),goToNext(),isLastItem()
 */
  	int getTotalHombres();
                /*! 
  \brief   Cuenta el total de mujeres de la provincia
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Numero total de mujeres del municipio
  \pre     Ninguna
  \post    Ninguna
  \sa      goToHead(),nItems(),getCurrentItems,getMujeres(),goToNext(),isLastItem()
 */
  	int getTotalMujeres();
     /*! 
  \brief   Suma el total de hombres y el total de mujeres
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Suma de hombres y mujeres del municipio
  \pre     Ninguna
  \post    Ninguna
  \sa      getTotalHombres(),getTotalMujeres()
 */
  	int getTotalHabitantes();
  	
	/////////////////////////////////////////////////////////////////////

	//!	\name Modificadores

  /*! 
  \brief   Da nombre a la provincia
  \warning Ninguna
  \param    Cadena de caracteres con el nombre de la provincia
  \note    Se realizará en el .cpp
  \return  Nada
  \pre     Ninguna
  \post    getNombre()==nombre
  \sa      getNombre()
 */
  	void setNombre(std::string n);
    /*! 
  \brief   Da codigo postal a la provincia
  \warning Ninguna
  \param   Entero con el codigo postal de la provincia
  \note    Se realizará en el .cpp
  \return  Nada
  \pre     Ninguna
  \post    getCodigo()==codigo
  \sa      getCodigo()
 */
  	void setCodigo(int x);
        /*! 
  \brief   Inserta un nuevo municipio en la lista
  \warning Ninguna
  \param   Objeto de tipo municipio
  \note    Se realizará en el .cpp
  \return  Nada
  \pre     existeMunicipio(m.getNombre())==false
  \post    Ninguna
  \sa      getNombre(),existeMunicipio(),insert()
 */
  	void insertarMunicipio(ed::Municipio m);
           /*! 
  \brief   Elimina un municipio de la provincia
  \warning Ninguna
  \param   Cadena de caracteres con el nombre del municipio
  \note    Se realizará en el .cpp
  \return  Nada
  \pre     Ninguna
  \post    existeMunicipio(m.getNombre())==true)
       listaMunicipios.find(m)==true)
  \sa      existeMunicipio(),getNombre(),find(),remove(),nItems()
 */
  	void borrarMunicipio(std::string nMunicipio);
              /*! 
  \brief   Elimina todos los municpios de la provincia
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Nada
  \pre     Ninguna
  \post    hayMunicipios()==false
  \sa      removeAll(),hayMunicipios()
 */
  	void borrarTodosLosMunicipios();
	/////////////////////////////////////////////////////////////////////

	//! \name Función de escritura de la clase Provincia
  /*! 
  \brief  Muestra por pantalla los municipios con sus datos
  \warning Ninguna
  \note    Se realizará en el .cpp
  \return  Nada
  \pre     Ninguna
  \post    Ninguna
  \sa      isEmpty(),nItems(),goToHead(),getCurrentItem(),getNombre(),getCodigo(),getHombres(),getMujeres(),getTotalHabitantes(),goToNext(),isLastItem()
 */
  	void escribirMunicipios();


	/////////////////////////////////////////////////////////////////////

	//! Operaciones con ficheros
    /*! 
  \brief  Carga un fichero en el programa
  \warning Ninguna
  \param  Cadena de caracteres con el nombre del fichero
  \note    Se realizará en el .cpp
  \return  true en caso de exito y false en caso de fallo
  \pre     Ninguna
  \post    Ninguna
  \sa      setNombre(),setCodigo(),insertarMunicipio()
 */
  	bool cargarFichero(std::string const & cadena);
    /*! 
  \brief  Guarda un fichero con las modicicaciones realizadas
  \warning Ninguna
  \param   Cadena de caracteres con el nombre del fichero
  \note    Se realizará en el .cpp
  \return  true en caso de exito y false en caso de fallo
  \pre     Ninguna
  \post    Ninguna
  \sa      hayMunicipios(),getNombre(),getCodigo(),goToHead(),goToNext(),isLastItem(),getCurrentItem()
 */
  	bool grabarFichero(std::string const & cadena);
}; //Fin de la clase  Provincia


} // Fin del espacio de nombres ed

#endif // _PROVINCIA_HPP_
