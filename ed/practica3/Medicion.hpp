/*! 
   \file Medicion.hpp
   \brief Fichero de la clase Medicion: medición de una estación meteorológica 
*/

#ifndef _MEDICION_HPP_
#define _MEDICION_HPP_

// Entrada y salida 
#include <iostream>

// Para controlar las precondiciones y postcondiciones mediante asertos
#include <cassert>

// Definición de la clase Fecha
#include "Fecha.hpp"


// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

#define COTA_ERROR   1.0e-6 //!< Cota de error para la comparación de números reales


// Se incluye la clase Medicion dentro del espacio de nombres de la asigantura: ed
namespace ed {

//!  Definición de la clase Medicion 
class Medicion
{
  //! \name Atributos privados de la clase Medicion
   private: 
   		Fecha _fecha;
   		float _precipitaciondelluvia;


   //! \name Funciones o métodos públicos de la clase Medicion
   public:

	//! \name Constructor de la clase Medicion
         
   		/*! 
         \brief     Constructor parametrizado que crea una medicion
         \attention Función sobrecargada        
         \note      Función inline
         \warning   Los parámetros tienen valores por defecto
         \pre       Ninguna
         \post      La fecha y la precipitacion deben ser iguales a los parametros recibidos
         \sa        getFecha(), getPrecipitacion()
          */
   		Medicion(Fecha fecha=Fecha(1,1,1),float precipitacion=0.0)
   		{
   			_fecha=fecha;
   			_precipitaciondelluvia=precipitacion;

               #ifndef NDEBUG
                  assert(getFecha()==fecha);
                  assert(getPrecipitacion()==precipitacion);
               #endif
   		}
   		//Constructor de copia
         /*! 
         \brief     Constructor de copia
         \attention Función sobrecargada        
         \note      Función inline
         \warning   El objeto que recibe se copia al actual
         \pre       Ninguna
         \post      La fecha y la precipitacion deben ser iguales a los parametros recibidos
         \sa        getFecha(), getPrecipitacion()
          */
   		Medicion(Medicion const &m)
   		{
   			setFecha(m.getFecha());
   			setPrecipitacion(m.getPrecipitacion());

               #ifndef NDEBUG
                  assert(getFecha()==m.getFecha());
                  assert(getPrecipitacion()==m.getPrecipitacion());
               #endif
   		}

	//! \name Observadores: funciones de consulta de la clase Medicion
         /*! 
         \brief     Devuelve una fecha       
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        Ninguna
          */
   		Fecha getFecha()const;
          /*! 
         \brief     Devuelve una precipitacion      
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa        Ninguna
          */
   		float getPrecipitacion()const;


	//! \name Funciones de modificación de la clase Medicion

          /*! 
         \brief     Modifica la fecha       
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      La fecha actual tiene que ser igual a la que se le pasa
         \sa        getFecha()
          */
   		void setFecha(Fecha f);

          /*! 
         \brief     Modifica la precipitacion     
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      La precipitacion actual tiene que ser igual a la que se le pasa
         \sa        getPrecipitacion
          */
   		void setPrecipitacion(float p);


	//! \name Operadores
   
         /*! 
         \brief     Comrpueba si dos mediciones son iguales    
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      La fecha actual y la que recibe que se le pasa deben ser iguales
         \return     True si se cumple la comparacion y false si no se cumple
         \sa        getFecha()
          */
   		bool operator==(Medicion const &m);
          /*! 
         \brief     Asigna a la medicion actual la que se le pasa   
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      La medicion actual es a que se le ha pasado
         \return    Puntero this con la medicion modificada
         \sa         setFecha(),setPrecipitacion(),getFecha(),getPrecipitacion()
          */
   		Medicion operator=(Medicion const &m);
   //! \name Operadores auxiliares realizados por el autor de manera independiente al enunciado de la practica

         /*! 
         \brief     Compara si una medicion es mayor que la que se le pasa   
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \return    True si se cumple la comparacion y false si no
         \sa        getPrecipitacion();
          */
         bool operator>(Medicion const &m);
         /*! 
         \brief     Compara si una medicion es menor que la que se le pasa   
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \return    True si se cumple la comparacion y false si no
         \sa        getPrecipitacion();
          */
         bool operator<(Medicion const &m);
           /*! 
         \brief     Compara si una medicion es menor o igual que la que se le pasa   
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \return    True si se cumple la comparacion y false si no
         \sa        getPrecipitacion();
          */
         bool operator<=(Medicion const &m);
            /*! 
         \brief     Compara si una medicion es mayor o igual que la que se le pasa   
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \return    True si se cumple la comparacion y false si no
         \sa        getPrecipitacion();
          */
         bool operator>=(Medicion const &m);
	//! \name Funciones de lectura y escritura de la clase Medicion

             /*! 
         \brief     Lee una medicion por teclado  
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \return    Nada
         \sa        setPrecipitacion(),leerFecha(),setFecha()
          */
   		void leerMedicion();
         /*! 
         \brief     Escribe una medicion por pantalla 
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \return    Nada
         \sa        getDia(),getMes(),getAgno(),getPrecipitacion()
          */
   		void escribirMedicion();


}; // Fin de la definición de la clase Medicion


   //! \name Funciones externas de la clase Medicion: sobrecarga de los operadores de flujo

   /*! 
         \brief     Sobrecarga de operador de flujo de salida
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \return    Nada
         \sa        getFecha(),getPrecipitacion()
          */
   ostream &operator<<(ostream &stream, ed::Medicion const &medicion);
   /*! 
         \brief     Sobrecarga de operador de flujo de entrada
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \return    Nada
         \sa        getLine(),atoi(),setFecha(),setPrecipitacion(),atof(),c_str(),
          */
   istream &operator>>(istream &stream, ed::Medicion &medicion);
		// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN



} // \brief Fin de namespace ed.

//  _MEDICION_HPP_
#endif 
