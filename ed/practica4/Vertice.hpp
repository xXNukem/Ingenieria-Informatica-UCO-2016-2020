/*!
	\file Vertice.hpp
	\brief Se define el TAD Vertice.
	\author Carlos de la Barrera Perez
	\date
*/
#ifndef _VERTICE_HPP_
#define _VERTICE_HPP_
#define COTA_ERROR   1.0e-6
   
#include <iostream>

#include <stdlib.h>

#include <fstream>

#include <string>

#include <cassert>

#include "macros.hpp"


namespace ed
{
//!  Definición de la clase Vertice
	class Vertice
	{
	//! \name Atributos privados de la clase vertice
		private:
			float _x;
			float _y;
			int _label;
	//! \name Funciones o métodos públicos de la clase vertice
		public:

			//! \name Constructores
		/*! 
         \brief    Constructor vacio
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa       Ninguna
          */
			Vertice()
			{

			}

			/*! 
         \brief    Constructor parametrizado
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Todos los parametros deben ser iguales a los que se le han pasado
         \sa       Ninguna
          */

			Vertice(float x,float y, int label)
			{
				_x=x;
				_y=y;
				_label=label;

					#ifndef NDEBUG
						assert(_x==x);
						assert(_y==y);
						assert(_label==label);
					#endif
			}
			
			//! \name Funciones de modificación de la clase vertice
				/*! 
         \brief    Modificador punto X
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      El valor de la variable debe ser igual al valor que se le pasa
         \sa       Ninguna
          */
			void setX(float x);
					/*! 
         \brief    Modificador punto X
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      El valor de la variable debe ser igual al valor que se le pasa
         \sa       Ninguna
          */
			void setY(float y);
					/*! 
         \brief    Modificador etiqueta
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      El valor de la variable debe ser igual al valor que se le pasa
         \sa       Ninguna
          */
			void setLabel(int label);

					/*! 
         \brief    Se le pasa un vertice y asigna al actual
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      El valor de la variable debe ser igual al valor que se le pasa
         \sa       Ninguna
          */
			void setData(Vertice v);

			//! \name Observadores: funciones de consulta de la clase vertice

							/*! 
         \brief    Devuelve la etiqueta del vertice
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa       Ninguna
          */
			int getLabel()const;
								/*! 
         \brief    Devuelve el punto X
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa       Ninguna
          */
			float getX()const;
								/*! 
         \brief    Devuelve el punto y
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa       Ninguna
          */
			float getY()const;

			//! \name Operadores de comparacion y asignacion
									/*! 
         \brief    Asigna un vertice a otro
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa       setX(),setY(),setLabel(),getLabel()
          */

			Vertice &operator=(const Vertice &v);
										/*! 
         \brief    Comprueba que dos vertices son iguales
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa       getX(),getY()
          */
			bool operator==(const Vertice &v)const;
			
	};

	//! \name Operadores de flujo
								/*! 
         \brief    Operador de flujo de salida
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa       getX(),getY()
          */
	std::ostream &operator<<(std::ostream &stream, const ed::Vertice &v);
								/*! 
         \brief    Operador de flujo de entrada
         \note      Codificada en el cpp
         \pre       Ninguna
         \post      Ninguna
         \sa       setX(),setY()
          */
	std::istream &operator>>(std::istream &stream, ed::Vertice &v);

}// \brief Fin de namespace ed.

#endif 