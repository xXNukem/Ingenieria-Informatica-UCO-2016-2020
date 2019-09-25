/*! 
   \file Lado.hpp
   \brief Fichero de la clase Lado
*/

#ifndef _LADO_HPP_
#define _LADO_HPP_

// Entrada y salida 
#include <iostream>

// Para controlar las precondiciones y postcondiciones mediante asertos
#include <cassert>

#include <cmath>

#include "Vertice.hpp"

// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

using namespace std;
// Se incluye la clase Lado dentro del espacio de nombres de la asigantura: ed
namespace ed {

//!  Definición de la clase Lado
class Lado 
{
  //! \name Atributos privados de la clase Lado
   private: 
	//! \name Funciones o métodos privados de la clase Lado

   		float _peso; //peso del lado
   		ed::Vertice _v1;
   		ed::Vertice _v2;

   //! \name Funciones o métodos públicos de la clase Lado
   public:

	//! \name Constructores de la clase Lado
	Lado()
	{

	}

	Lado(Vertice const &v1, Vertice const &v2, double const &peso)
	{
		_v1=v1;
		_v2=v2;
		_peso=peso;
	}
	//! \name Observadores: funciones de consulta de la clase Lado

	float getPeso()const;
	Vertice getVertice1()const;
	Vertice getVertice2()const;
	float calcularDistanciaEuclidea ( ed::Vertice v1, ed::Vertice v2 ) ;

	//! \name Funciones de modificación de la clase Lado
	void setVertice1(Vertice v1);
	void setVertice2(Vertice v2);
	void setPeso(float p);
    //! \name Operadores
   Lado operator=(Lado & l);

	//! \name Funciones de lectura y escritura de la clase Lado


}; // Fin de la definición de la clase Lado


} // \brief Fin de namespace ed.

//  _LADO_HPP_
#endif 
