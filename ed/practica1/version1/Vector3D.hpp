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
#include <vector>
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

   	double v[3];//!<Array donde v[0] es x, v[1] es y, y v[2] es z

   //! \name Funciones o métodos públicos de la clase Vector3D
   public:

	//! \name Constructores de la clase Vector3D
	        /*! 
  \brief   Constructor vacio
  \warning Ninguna
  \note    Se realizará en el .hpp
  \return  Ninguna
  \pre     Ninguna
  \post    get1()==0 && get2()==0 && get3()==0
  \sa      get1(),get2(),get3()
 */
   	Vector3D()
   	{
   		v[0]=0;
   		v[1]=0;
   		v[2]=0;

   		
   			#ifndef NDEBUG
   				assert(get1()==0 && get2()==0 && get3()==0);
   			#endif
		
   	}
   		
	        /*! 
  \brief   Constructor parametrizado
  \warning Ninguna
  \note    Se realizará en el .hpp
  \return  Ninguna
  \pre     Ninguna
  \post    get1()==x && get2()==y && get3()==z
  \sa      get1(),get2(),get3()
 */
   	Vector3D(double x,double y,double z)
   	{
   		v[0]=x;
   		v[1]=y;
   		v[2]=z;
   			
   			#ifndef NDEBUG
   				assert(get1()==x && get2()==y && get3()==z);
   			#endif
   			
   	}

   	
	        /*! 
  \brief   Constructor de copia
  \warning Ninguna
  \note    Se realizará en el .hpp
  \return  Ninguna
  \pre     Ninguna
  \post    get1()==v.get1() && get2()==v.get2() && get3()==v.get3()
  \sa      get1(),get2(),get3()
 */
   	Vector3D(const Vector3D &v)
   	{
   		this->v[0]=v.get1();
   		this->v[1]=v.get2();
   		this->v[2]=v.get3();
   		
   			#ifndef NDEBUG
   				assert(get1()==v.get1() && get2()==v.get2() && get3()==v.get3());
   			#endif
   		
   	}
	// COMPLETAR

	//! \name Observadores: funciones de consulta de Vector3D
		        /*! 
  \brief   Observador de X
  \warning Ninguna
  \note    Se realizará en el .hpp
  \return  Componente X
  \pre     Ninguna
  \post    Ninguna
  \sa     Ninguna
 */
   	double get1()const;
   	 /*! 
  \brief   Observador de Y
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Componente Y
  \pre     Ninguna
  \post    Ninguna
  \sa     Ninguna
 */
   	double get2()const;
   	/*! 
  \brief   Observador de Z
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Componente Z
  \pre     Ninguna
  \post    Ninguna
  \sa     Ninguna
 */
   	double get3()const;
   		/*! 
  \brief   Calcula el modulo
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Modulo del vector
  \pre     Ninguna
  \post    Ninguna
  \sa     sqrt(),get1(),get2(),get3(),abs()
 */
   	double modulo()const;
   	/*! 
  \brief   Calcula el angulo
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Angulo del vector
  \pre     Ninguna
  \post    modulo==sqrt(get1()*get1()+get2()*get2()+get3()*get3())
  \sa     acos(),get1(),get2(),get3(),abs(),assert()
 */
   	double angulo(Vector3D const &w)const;
   	/*! 
  \brief   Calcula el vector alfa
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Vector alfa
  \pre     modulo()*w.modulo()>0
  \post    alfa==angulo(w)
  \sa     set1(),set2(),set3(),angulo(),assert(),angulo()
 */
   	double alfa()const;
   	/*! 
  \brief   Calcula el vector beta
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Vector beta
  \pre     modulo()*w.modulo()>0
  \post    beta==angulo(w)
  \sa     set1(),set2(),set3(),angulo(),assert(),angulo()
 */
   	double beta()const;
   	/*! 
  \brief   Calcula el vector gamma
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Vector gamma
  \pre     modulo()*w.modulo()>0
  \post    gamma==angulo(w)
  \sa     set1(),set2(),set3(),angulo(),assert(),angulo()
 */
   	double gamma()const;
   	/*! 
  \brief   Calcula el producto escalar
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Producto escalar
  \pre     Ninguna
  \post    productoEscalar==get1()*v.get1()+get2()*v.get2()+get3()*v.get3()
  \sa     get1(),get2(),get3(),assert()
 */
   	double dotProduct(Vector3D const &v)const;
   	/*! 
  \brief   Calcula el producto vectorial
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Producto vectorial
  \pre     Ninguna
  \post    	dotProduct(a)==0;
			v.dotProduct(a)==0;
			abs(a.modulo()-modulo()*v.modulo()*sin(angulo(v)))<COTA_ERROR
  \sa     get1(),get2(),get3(),assert(),abs(),modulo(),angulo()
 */
   	Vector3D crossProduct(Vector3D const &v)const;
   		/*! 
  \brief   Calcula el producto mixto
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Producto mixto
  \pre     Ninguna
  \post    productoEscalar==get1()*v.get1()+get2()*v.get2()+get3()*v.get3()
  \sa     get1(),get2(),get3(),assert()
 */
   	double productoMixto(Vector3D v1, Vector3D v2)const;

	// COMPLETAR



	//! \name Modificadores: funciones de modificación de Vector3D
	/*! 
  \brief   Asigna un valor a X
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Nada
  \pre     Ninguna
  \post    get1()==x
  \sa     get1(),assert()
 */
   	void set1(double x);
   	/*! 
  \brief   Asigna un valor a Y
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Nada
  \pre     Ninguna
  \post    get2()==y
  \sa     get2(),assert()
 */
   	void set2(double y);
   	/*! 
  \brief   Asigna un valor a Z
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Nada
  \pre     Ninguna
  \post    get3()==z
  \sa     get4(),assert()
 */
   	void set3(double z);
   	/*! 
  \brief   Suma una constante K al vector
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Nada
  \pre     Ninguna
  \post    get1()==old.get1()+k && get2()==old.get2()+k && get3()==old.get3()+k
  \sa     get1(),get2(),get3(),assert()
 */
   	void sumConst(double k);
   	/*! 
  \brief   Suma un vector a otro vector
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Nada
  \pre     Ninguna
  \post    get1()==old.get1()+v.get1())&&(get2()==old.get2()+v.get2())&&(get3()==old.get3()+v.get3()
  \sa     get1(),get2(),get3(),assert()
 */
   	void sumVect(Vector3D v);
   		/*! 
  \brief   Multiplica una constante K por el vector
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Nada
  \pre     Ninguna
  \post    get1()==old.get1()*k && get2()==old.get2()*k && get3()==old.get3()*k
  \sa     get1(),get2(),get3(),assert()
 */
   	void multConst(double k);
   		/*! 
  \brief   Multiplica un vector por otro
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Nada
  \pre     Ninguna
  \post    get1()==old.get1()*v.get1())&&(get2()==old.get2()*v.get2())&&(get3()==old.get3()*v.get3()
  \sa     get1(),get2(),get3(),assert()
 */
   	void multVect(Vector3D v);
	// COMPLETAR


    //! \name Operadores de la clase
    /*! 
  \brief   Operador suma binario
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Vector con la suma resultado
  \pre     Ninguna
  \post    a->get1()==get1()+v.get1())&&(a->get2()==get2()+v.get2())&&(a->get3()==get3()+v.get3()
  \sa     get1(),get2(),get3(),assert()
 */
   
   Vector3D & operator+(Vector3D const &v)const;
   /*! 
  \brief   Operador resta binario
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Vector con la resta resultado
  \pre     Ninguna
  \post    a->get1()==get1()-v.get1())&&(a->get2()==get2()-v.get2())&&(a->get3()==get3()-v.get3()
  \sa     get1(),get2(),get3(),assert()
 */
   Vector3D & operator-(Vector3D const &v)const;
/*! 
  \brief   Operador suma unario
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Vector con a copia del vector actual
  \pre     Ninguna
  \post    a->get1()==get1())&&(a->get2()==get2())&&(a->get3()==get3()
  \sa     get1(),get2(),get3(),assert()
 */
   Vector3D & operator+()const;
   /*! 
  \brief   Operador resta unario
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Vector opuesto al actual
  \pre     Ninguna
  \post    a->get1()==-get1())&&(a->get2()==-get2())&&(a->get3()==-get3()
  \sa     get1(),get2(),get3(),assert()
 */
   Vector3D & operator-()const;
   /*! 
  \brief   Operador que multiplica una constante K por el vector
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Vector con el producto de K * v
  \pre     Ninguna
  \post    a->get1()==get1()*k)&&(a->get2()==get2()*k)&&(a->get3()==get3()*k
  \sa     get1(),get2(),get3(),assert()
 */

   Vector3D & operator*(double k)const;

   /*! 
  \brief   Operador que realiza el producto escalar
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Vector con el producto escalar del vector actual y v
  \pre     Ninguna
  \post   a->get1()==get1()*k)&&(a->get2()==get2()*k)&&(a->get3()==get3()*k
  \sa     get1(),get2(),get3(),assert()
 */

 	double operator*(Vector3D const &v)const;
 /*! 
  \brief   Operador que realiza el producto vectorial
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Producto vectorial
  \pre     Ninguna
  \post  dotProduct(o)==0
		v.dotProduct(o)==0
		std::abs(o.modulo()-modulo()*v.modulo()*sin(angulo(v)))<COTA_ERROR
  \sa     get1(),get2(),get3(),assert(),modulo(),abs(),angulo(),sin()
 */

   Vector3D & operator^(Vector3D const &v)const;
	// COMPLETAR COMENTARIOS DE DOXYGEN
 /*! 
  \brief   Operador que asigna un vector a otro
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Vector asignado
  \pre     Ninguna
  \post   get1()==v.get1()&&get2()==v.get2()&&get3()==v.get3()
  \sa     get1(),get2(),get3(),assert()
 */

	Vector3D & operator=(Vector3D const &objeto);

	// COMPLETAR COMENTARIOS DE DOXYGEN
	/*! 
  \brief   Operador que compara dos vectores
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  True si son iguales, false si son distintos
  \pre     Ninguna
  \post   true==(get1()==v.get1()&&get2()==v.get2()&&get3()==v.get3())
  \sa     get1(),get2(),get3(),assert()
 */
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

   /*! 
  \brief   Operador que realiza el producto de una constante K por un vector
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Vector con el producto escalar del vector actual y v
  \pre     Ninguna
  \post   prodEscalar==get1()*v.get1()+get2()*v.get2()+get3()*v.get3()
  \sa     get1(),get2(),get3(),assert()
 */
    Vector3D & operator* (double k, Vector3D const & objeto);


	// COMPLETAR COMENTARIOS DE DOXYGEN
	/*! 
  \brief   Sobrecarga del operador >>
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Nada
  \pre     Ninguna
  \post   Nada
  \sa     get1(),get2(),get3()
 */
    istream &operator>>(istream &stream, Vector3D &objeto);

	// COMPLETAR COMENTARIOS DE DOXYGEN 
	/*! 
  \brief   Sobrecarga del operador <<
  \warning Ninguna
  \note    Codificada en el Vectores3D.cpp
  \return  Nada
  \pre     Ninguna
  \post   Nada
  \sa     set1(),set2(),set3()
 */   
	ostream &operator<<(ostream &stream, Vector3D const &objeto);


} // \brief Fin de namespace ed.

//  _VECTOR3D_HPP_
#endif 
