/*! 
   \file Municipio.hpp
   \brief Fichero de la clase Municipio: vértice del plano euclídeo 
*/

#ifndef _MUNICIPIO_HPP_
#define _MUNICIPIO_HPP_

// Entrada y salida 
#include <iostream>

// 
#include <string>



// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;


// Se incluye la clase Municipio dentro del espacio de nombre de la asigantura: ed
namespace ed {

//!  Definición de la clase Municipio
class Municipio
{

  //! \name Atributos privados de la clase Municipio
   private: 
      	int _codigoPostal;   //!< código postal del Municipio 
		std::string _nombre; //!< nombre del Municipio
      	int _hombres;        //!< número de hombres del Municipio 
      	int _mujeres;        //!< número de mujeres del Municipio  


   //! \name Funciones o métodos públicos de la clase Municipio
   public:

	//! \name Constructores de la clase Municipio
	/*! 
		\brief     Constructor parametrizado con valores por defecto
		\attention Función sobrecargada        
		\note      Función inline
		\param     nombre: valor por defecto ""
		\param     codigoPostal: valor por defecto 0.0
		\param     hombres: valor por defecto 0.0
		\param     mujeres: valor por defecto 0.0
		\pre       Ninguna
		\post      Ninguna
		\sa        setNombre(), setCodigoPostal(),setHombres(), setMujeres()
	*/
	inline Municipio(std::string nombre = "", int codigoPostal = 0,
                     int hombres = 0, int mujeres = 0)
	{
		this->setCodigoPostal(codigoPostal);
		this->setNombre(nombre);
		this->setHombres(hombres);
		this->setMujeres(mujeres);
	}

	/*! 
		\brief     Constructor de "copia" 
		\attention Función sobrecargada        
		\note      Función inline
		\warning   Se requiere que las funciones de acceso tengan el modificador const
		\param     objeto de la clase Municipio que proporciona los valores iniciales
		\pre       Ninguna
		\post      Ninguna
		\sa        setNombre(), setCodigoPostal(), setHombres(), setMujeres(), 
		\n		   getNombre(), getCodigoPostal(), getHombres(), getMujeres()
	*/
	inline Municipio(Municipio const &objeto)
	{
		this->setCodigoPostal(objeto.getCodigoPostal());
		this->setNombre(objeto.getNombre());
		this->setHombres(objeto.getHombres());
		this->setMujeres(objeto.getMujeres());
	}

	//! \name Observadores: funciones de consulta de Municipio

	/*! 
		\brief   Función que devuelve el nombre
		\attention Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
		\note    Función inline
		\return  Nombre del municipio
		\pre     Ninguna
		\post    Ninguna
		\sa      getCodigoPostal(), getHombres(), getMujeres(), getHabitantes()
	*/
	inline std::string getNombre()const
	{
		return this->_nombre;
	}

	/*! 
		\brief   Función que devuelve el código postal
		\attention Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
		\note    Función inline
		\return  Código postal del municipio (tipo int)
		\pre     Ninguna
		\post    Ninguna
		\sa      getNombre(), getHombres(), getMujeres(), getHabitantes() 
	*/
	inline int getCodigoPostal()const
	{
		return this->_codigoPostal;
	}

	/*! 
		\brief   Función que devuelve el número total de hombres
		\attention Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
		\note    Función inline
		\return  Número total de hombres del municipio (tipo int)
		\pre     Ninguna
		\post    Ninguna
		\sa      getCodigoPostal(), getNombre(), getMujeres(), getHabitantes()
	*/
	inline int getHombres() const
	{
		return this->_hombres;
	}


	/*! 
		\brief   Función que devuelve el número total de mujeres
		\attention Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
		\note    Función inline
		\return  Número total de mujeres del municipio (tipo int)
		\pre     Ninguna
		\post    Ninguna
		\sa      getCodigoPostal(), getNombre(), getHombres(), getHabitantes()
	*/
	inline int getMujeres() const
	{
		return this->_mujeres;
	}

	/*! 
		\brief   Función que devuelve el número total de habitantes
		\attention Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
		\note    Función inline
		\note 	 El número total de habitantes es un atributo "derivado" que se calcula mediante la suma del número de hombres y el número de mujeres
		\return  Número total de habitantes del municipio (tipo int)
		\pre     Ninguna
		\post    valorDevuelto == getHombres() + getMujeres()
		\sa      getCodigoPostal(), getNombre(), getHombres(), getMujeres()
	*/
	inline int getHabitantes() const
	{
		return this->getHombres() + this->getMujeres();
	}


	//! \name Funciones de modificación de Municipio

	/*! 
		\brief Función que asigna un nuevo valor al código postal
		\note    Función inline
		\param v: nuevo valor del código postal
		\pre   Ninguna
		\post  El valor del código postal debe ser "v"
		\sa    setNombre, setHombres, setMujeres
	*/
	inline void setCodigoPostal(int v) 
	{
		this->_codigoPostal = v;
	}


	/*! 
		\brief Función que asigna un nuevo valor al nombre 
		\note    Función inline
		\param v: nuevo valor del nombre
		\pre   Ninguna
		\post  El valor del nombre debe ser "v"
		\sa    setCodigoPostal
	*/
	inline void setNombre(std::string const &v) 
	{
		this->_nombre = v;
	}

	/*! 
		\brief Función que asigna un nuevo valor al número total de hombres
		\note    Función inline
		\param v: nuevo valor del número total de hombres
		\pre   Ninguna
		\post  El valor del número total de hombres debe ser "v"
		\sa    setNombre, setCodigoPostal, setMujeres
	*/
	inline void setHombres(int v) 
	{
		this->_hombres = v;
	}

	/*! 
		\brief Función que asigna un nuevo valor al número total de mujeres
		\note    Función inline
		\param v: nuevo valor del número total de mujeres
		\pre   Ninguna
		\post  El valor del número total de mujeres debe ser "v"
		\sa    setNombre, setCodigoPostal, setHombres
	*/
	inline void setMujeres(int v)
	{
		this->_mujeres = v;
	}


    //! \name Operadores
   
	/*! 
		\brief     Operador de asignación
		\attention Se sobrecarga el operador de asignación "="
		\note      Función inline
		\warning   Se requiere que las funciones de acceso tengan el modificador const
		\param     objeto de la clase Municipio pasado como referencia constante
		\pre       El Municipio "objeto" debe ser diferente del municipio actual
		\post      Ninguna
		\sa        setCodigoPostal, setNombre, setHombres, setMujeres, 
		\n		   getCodigoPostal, getNombre, getHombres, getMujeres
	*/
	inline Municipio & operator=(Municipio const &objeto)
	{
		// Se comprueba que no sean el mismo objeto
		if (this != &objeto) 
		{
			this->setCodigoPostal(objeto.getCodigoPostal());
			this->setNombre(objeto.getNombre());
			this->setHombres(objeto.getHombres());
			this->setMujeres(objeto.getMujeres());
		}

		// 
		return *this;
	}
 


	/*! 
		\brief     Operador de igualdad: compara si los dos municipios tiene el mismo nombre
		\attention Se sobrecarga el operador de igualdad "="
		\note      Función inline
		\param     objeto de la clase Municipio pasado como referencia constante
		\return	   true: si los municipios son iguales; false, en caso contrario
		\pre       Ninguna
		\post      Ninguna
		\sa        getNombre, operator<
	*/
	inline bool operator == (Municipio const &objeto) const
	{
    	return ( this->getNombre() == objeto.getNombre() );
	}

	/*! 
		\brief     Operador relacional "menor que": compara los nombres de los municipios
		\attention Se sobrecarga el operador de igualdad "<"
		\note      Función inline
		\param     objeto de la clase Municipio pasado como referencia constante
		\return	   true: si los municipios son iguales; false, en caso contrario
		\pre       Ninguna
		\post      Ninguna
		\sa        getNombre, operator=
	*/
	inline bool operator < (Municipio const &objeto) const
	{
    	return ( this->getNombre() < objeto.getNombre() );
	}



	//! \name Funciones lectura y escritura de la clase Municipio

	/*! 
		\brief   Asigna a un Municipio las conombres "x" e "y" leídas desde el teclado
		\pre     Ninguna
		\post    Deben ser numéricos los atributos de los atributos código postal, hombre y mujeres
		\sa      setCodigoPostal, setNombre, setHombres, setMujeres, escribirMunicipio
	*/
	void leerMunicipio();


	/*! 
		\brief Escribe por pantalla los valores de los atributos de un Municipio
		\note  Formato: código postal, nombre, habitantes, hombres, mujeres
		\pre   Ninguna
		\post  Ninguna
		\sa    getCodigoPostal, getNombre, getHombres, getMujeres, getHabitantes
	*/
	void escribirMunicipio() const;


}; // Fin de la definición de la clase Municipio


//! \name Funciones auxiliares del espacio de nombres ed

	/*! 
		\brief     Función de comparación relacional "menor que": compara el número de habitantes de los municipios
		\note      Función inline
		\param     objeto1 de la clase Municipio pasado como referencia constante
		\param     objeto2 de la clase Municipio pasado como referencia constante
		\return	   true: el objeto1 tiene menos habitatnes que objeto2; false, en caso contrario
		\pre       Ninguna
		\post      Ninguna
		\sa        operator<
	*/
	bool comparar (ed::Municipio const &objeto1, ed::Municipio const &objeto2) ;


    /*!
  		\brief     Sobrecarga del operador de salida o escritura "<<"
				   \n Se escriben los datos teniendo en cuenta el formato: CP Nombre; hombres; mujeres;
		\param     stream: flujo de salida
		\param     objeto de la clase Municipio pasado como referencia "constante"
		\pre       Ninguna
		\post      Ningguna
		\sa        operator>>()
    */
    ostream &operator<<(ostream &stream, ed::Municipio const &objeto);

    /*!
  		\brief     Sobrecarga del operador de entrada o lectura ">>"
				   \n  Se lee un minicipio con el formato: CP Nombre; hombres; mujeres;
		\attention Función amiga de la clase Municipio
		\param     stream: flujo de salida
		\param     objeto de la clase Municipio pasado como referencia
		\pre       Ninguna
		\post      Ninguna
		\sa        operator<<()
    */
    istream &operator>>(istream &stream, ed::Municipio &objeto);


} // \brief Fin de namespace ed.

//  _MUNICIPIO_HPP_
#endif 
