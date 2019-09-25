/*! 
   \file Vector3D.hpp
   \brief Fichero de definición de la clase Vector3D: vector libre de tres dimensiones
*/

#ifndef _VECTOR3D_HPP_
#define _VECTOR3D_HPP_

// Entrada y salida 
#include <iostream>

// Para usar abs
#include <cmath>

// Para controlar las pre y post condiciones mediante asertos
#include <cassert>

// COMPLETAR, SI ES PRECISO


// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

#define COTA_ERROR   1.0e-6 //!< Cota de error para la comparación números reales


// Se incluye la clase Vector3D dentro del espacio de nombre de la asigantura: ed
namespace ed {

//!  Definición de la clase Vector3D:  \f$ \vec{v} = (v_1, v_2, v_3) = v_1 \vec{i} + v_2 \vec{j} + v_3 \vec{k} \f$ 
class Vector3D
{
  //! \name Atributos privados de la clase Vector3D
   private: 

	// COMPLETAR
   	double x_;
   	double y_;
   	double z_;

   //! \name Funciones o métodos públicos de la clase Vector3D
   public:

	//! \name Constructores de la clase Vector3D
   		Vector3D()
   		{
   			x_=0;
   			y_=0;
   			z_=0;

   				#ifndef NDEBUG
   					assert(get1()==0 && get2()==0 && get3()==0);
   				#endif
   		}
   		Vector3D(double x,double y,double z)
   		{
   			x_=x;
   			y_=y;
   			z_=z;

   				#ifndef NDEBUG
   					assert(get1()==x_ && get2()==y_ && get3()==z_);
   				#endif
   		}
   		Vector3D(const Vector3D &v)
   		{
   			x_=v.get1();
   			y_=v.get2();
   			z_=v.get3();

   				#ifndef NDEBUG
   					assert(get1()==v.get1() && get2()==v.get2() && get3()==v.get3());
   				#endif
   		}
	// COMPLETAR	

	//! \name Observadores: funciones de consulta de Vector3D
   		double get1()const;
   		double get2()const;
   		double get3()const;
   		double modulo()const;
   		double angulo(Vector3D v)const;
   		double dotProduct(Vector3D const &v)const;
   		Vector3D crossProduct(Vector3D const &v)const;
   		double alfa()const;
   		double beta()const;
   		double gamma()const;
   		double productoMixto(Vector3D v1,Vector3D v2)const;
	// COMPLETAR

	//! \name Modificadores: funciones de modificación de Vector3D
   		void set1(double x);
   		void set2(double y);
   		void set3(double z);
   		void sumConst(double k);
   		void sumVect(Vector3D v);
   		void multConst(double k);
   		void multVect(Vector3D v);
	// COMPLETAR


    //! \name Operadores de la clase
   Vector3D & operator+(Vector3D const &v)const;
   Vector3D & operator-(Vector3D const &v)const;

   Vector3D & operator+()const;
   Vector3D & operator-()const;

   Vector3D & operator*(double k)const;
   //Vector3D & operator*(double k, Vector3D const &v)const;
   double operator*(Vector3D const &v)const;


   Vector3D & operator^(Vector3D const &v)const;

	// COMPLETAR COMENTARIOS DE DOXYGEN
	Vector3D & operator=(Vector3D const &objeto);


	// COMPLETAR COMENTARIOS DE DOXYGEN
	bool operator == (Vector3D const &objeto) const;

	// COMPLETAR EL RESTO DE OPERADORES


	//! \name Funciones lectura y escritura de la clase Vector3D
		void leerVector3D();
   		void escribirVector3D()const;
	// COMPLETAR

}; // Fin de la definición de la clase Vector3D


//////////////////////////////////////////////////////////////////////////////////////

//! \name Funciones que utilizan un objetos de la clase Vector3D, pero que no pertenecen a la clase Vector3D

	// COMPLETAR COMENTARIOS DE DOXYGEN
    Vector3D & operator* (double k, Vector3D const &objeto);


	// COMPLETAR COMENTARIOS DE DOXYGEN
    istream &operator>>(istream &stream, Vector3D &objeto);

	// COMPLETAR COMENTARIOS DE DOXYGEN    
	ostream &operator<<(ostream &stream, Vector3D const &objeto);


} // \brief Fin de namespace ed.

//  _VECTOR3D_HPP_
#endif 
