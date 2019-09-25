/*! 
   \file Fecha.hpp
   \brief Fichero de la clase Fecha
*/

#ifndef _FECHA_HPP_
#define _FECHA_HPP_

// Entrada y salida 
#include <iostream>

// Para controlar las precondiciones y postcondiciones mediante asertos
#include <cassert>

// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

// Se incluye la clase Fecha dentro del espacio de nombres de la asigantura: ed
namespace ed {

//!  Definición de la clase Fecha
class Fecha 
{
  //! \name Atributos privados de la clase Fecha
   private: 
      	int _dia;  //!< día de la fecha  
		int _mes;  //!< mes de la fecha
		int _agno; //!< año de la fecha

	//! \name Funciones o métodos privados de la clase Fecha

	/*! 
		\brief     Función que comprueba si un año es bisiesto, es decir, si es múltiplo de 4 pero si es divisible por 100 también debe ser divisible por 400
		\attention Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
		\return    bool: true, si es bisiesto; false, en caso contrario
		\pre       Ninguna
		\post      Ninguna
		\sa        getAgno()
	*/
	bool esBisiesto() const;


   //! \name Funciones o métodos públicos de la clase Fecha
   public:

	//! \name Constructores de la clase Fecha
	/*! 
		\brief     Constructor que crea una fecha
		\attention Función sobrecargada        
		\note      Función inline
	 	\warning   Los parámetros tienen valores por defecto
		\param     dia: día de la fecha; valor por defecto: 1
		\param     mes: mes de la fecha; valor por defecto: 1
		\param     agno: año de la fecha; valor por defecto: 1
		\pre       Ninguna
		\post      La fecha debe ser correcta
		\sa        setDia, setMes(), setAgno(), esCorrecta
	*/
	inline Fecha(int dia=1, int mes=1, int agno=1)
	{
		this->setDia(dia);
		this->setMes(mes);
		this->setAgno(agno);

		#ifndef NDEBUG
  		// Se comprueba la postcondición
//		assert(this->esCorrecta() == true);
		#endif //NDEBUG
	}

	/*! 
		\brief     Constructor de "copia" que crea una fecha a partir de otra fecha
		\attention Función sobrecargada        
		\note      Función inline
		\warning   Se requiere que las funciones de acceso getDia(), getMes y getAgno tengan el modificador const
		\param     objeto de la clase Fecha utilizado para proporcionar los valores iniciales de la nueva fecha
		\pre       La fecha del objeto es correcta 
		\post      Los atributos _dia, _mes y _agno deben tener los valores de los atributos del objeto pasado como argumento
		\sa        getDia(), getMes(), setDia(), setMes()
	*/
	inline Fecha(Fecha const &objeto)
	{
		#ifndef NDEBUG
  		// Se comprueba la precondición
//		assert(objeto.esCorrecta() == true);
		#endif //NDEBUG

		this->setDia(objeto.getDia());
		this->setMes(objeto.getMes());
		this->setAgno(objeto.getAgno());

		#ifndef NDEBUG
  		// Se comprueba la postcondición
		assert(this->_dia == objeto.getDia());
		assert(this->_mes == objeto.getMes());
		assert(this->_agno == objeto.getAgno());
		#endif //NDEBUG
	}

	//! \name Observadores: funciones de consulta de la clase Fecha

	/*! 
		\brief   Función que devuelve el díade una fecha
		\attention Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
		\note    Función inline y redefinida de la clase padre FechaInterfaz
		\return  Valor del atributo que representa el día (tipo int)
		\pre     Ninguna
		\post    Ninguna
		\sa      getMes(), getAgno()
	*/
	inline int getDia() const
	{
		return _dia;
	}

	/*! 
		\brief     Función que devuelve el mes de una fecha
		\attention Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
		\note      Función inline y redefinida de la clase padre FechaInterfaz
		\return    Valor del atributo que representa el mes (tipo int)
		\pre       Ninguna
		\post      Ninguna
		\sa        getDia(), getAgno()
	*/
	inline int getMes() const
	{
		return 	this->_mes;
	}

	/*! 
		\brief     Función que devuelve el año de una fecha
		\attention Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
		\note      Función inline y redefinida de la clase padre FechaInterfaz
		\return    Valor del atributo que representa el año (tipo int)
		\pre       Ninguna
		\post      Ninguna
		\sa        getDia(), getMes()
	*/
	inline int getAgno() const
	{
		return 	this->_agno;
	}

	/*! 
		\brief     Función que comprueba si una fecha es correcta
		\attention Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
		\return    bool: true, si la fecha es correcta; false, en caso contrario
		\pre       Ninguna
		\post      Ninguna
		\sa        getDia(), getMes(), getAgno()
	*/
	bool esCorrecta() const;


	//! \name Funciones de modificación de la clase Fecha

	/*! 
		\brief Función que asigna un nuevo valor al día de una fecha
		\note  Función inline y redefinida de la clase padre FechaInterfaz
		\param v: nuevo valor del día de una Fecha
		\pre   El valor de v debe estar en los límites establecidos por el mes y año
		\post  El atributo _dia de Fecha debe tener el valor "v"
		\sa    setMes(), setAgno()
	*/
	inline void setDia(int v)
	{
		this->_dia = v;

		#ifndef NDEBUG
  		// Se comprueba la postcondición
		assert(this->_dia == v);
		#endif //NDEBUG
	 }


	/*! 
		\brief Función que asigna un nuevo valor al mes de una fecha
		\note  Función inline y redefinida de la clase padre FechaInterfaz
		\param v: nuevo valor del mes de una fecha
		\pre   ninguna
		\post  El atributo _mes de Fecha debe tener el valor "v" 
		\sa    setDia, setAgno
	*/
	inline void setMes(int v)
	{
		this->_mes = v;

		#ifndef NDEBUG
  		// Se comprueba la postcondición
		assert(this->_mes == v);
		#endif //NDEBUG
	}


	/*! 
		\brief Función que asigna un nuevo valor al año de una fecha
		\note  Función inline y redefinida de la clase padre FechaInterfaz
		\param v: nuevo valor del año de una fecha
		\pre   ninguna
		\post  El atributo _agno de Fecha debe tener el valor "v" 
		\sa    setDia, setMes
	*/
	inline void setAgno(int v)
	{
		this->_agno = v;

		#ifndef NDEBUG
  		// Se comprueba la postcondición
		assert(this->_agno == v);
		#endif //NDEBUG
	}


    //! \name Operadores
   
	/*! 
		\brief     Operador de asignación: operador que "copia" una fecha en otra fecha
		\attention Se sobrecarga el operador de asignación "="
		\note      Función inline
		\warning   Se requiere que las funciones de acceso getDia y getMes tengan el modificador const
		\param     objeto de la clase Fecha pasado como referencia constante
		\pre       El objeto es distinto del objeto actual
		\pre	   El objeto representa una fecha correcta
		\post      Los atributos _dia, _mes y _agno deben tener los valores de los atributos del objeto pasado como argumento
		\sa        getDia(), getMes(), setDia(), setMes()
	*/
	inline Fecha & operator=(Fecha const &objeto)
	{
/*
		#ifndef NDEBUG
  		// Se comprueba la precondición
//		assert(objeto.esCorrecta() == true);
		#endif //NDEBUG
*/
		// Se comprueba que no sean el mismo objeto
		if (this != &objeto) 
		{
			this->setDia(objeto.getDia());
			this->setMes(objeto.getMes());
			this->setAgno(objeto.getAgno());

			#ifndef NDEBUG
	  		// Se comprueba la postcondición
			assert(this->_dia == objeto.getDia());
			assert(this->_mes == objeto.getMes());
			assert(this->_agno == objeto.getAgno());
			#endif //NDEBUG
		}

		return *this;
	}
 

	/*! 
		\brief     Operador de igualdad: compara si dos fechaes son iguales
		\attention Se sobrecarga el operador de asignación "=="
		\note      Función inline
		\param     objeto: Fecha pasada como referencia constante
		\pre       Ninguna
		\post      Ninguna
		\sa        getDia(), getMes(), getAgno(), esCorrecta
	*/
	inline bool operator == (Fecha const &objeto) const
	{
	  return (
            	  ( this->getDia() == objeto.getDia() ) 
              and ( this->getMes() == objeto.getMes() )
              and ( this->getAgno() == objeto.getAgno() )
             );
	}


	//! \name Funciones de lectura y escritura de la clase Fecha

	/*! 
		\brief Escribe por pantalla los valores de los atributos de una fecha
		\pre   La fecha debe ser correcta
		\post  Ninguna
		\sa    getDia(), getMes(), getAgno()
	*/
	void escribirFecha()const;

	/*! 
		\brief   Lee desde el teclado los nuevos valores de los atributos de una fecha
		\warning Se deben teclear números
		\pre     ninguna
		\post    La fecha debe ser correcta
		\sa      setDia, setMes(), setAgno()
	*/
	void leerFecha();


}; // Fin de la definición de la clase Fecha


   //! \name Funciones externas de la clase Fecha: sobrecarga de los operadores de flujo

    /*!
  		\brief     Sobrecarga del operador de salida o escritura "<<"
				   \n Se escribe la fecha por pantalla con el formato (d)d-(m)m--aaaa
		\param     stream Flujo de salida
		\param     fecha pasada como referencia constante
		\pre       Ninguna
		\post      Ninguna
		\sa        operator>>()
    */
    ostream &operator<<(ostream &stream, Fecha const &fecha);

    /*!
  		\brief     Sobrecarga del operador de entrada o lectura ">>"
		\param     stream Flujo de entrada
		\param     fecha pasada como referencia 
		\pre       Ninguna
		\post      Ninguna
		\sa        operator<<()
    */
    istream &operator>>(istream &stream, Fecha &fecha);




} // \brief Fin de namespace ed.

//  _FECHA_HPP_
#endif 
