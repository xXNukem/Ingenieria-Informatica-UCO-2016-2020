/*! 
   \file Vector3D.cpp
   \brief Fichero que contiene el código de las funciones de la clase Vector3D
*/


// Ficheros de cabecera
#include <iostream>

// Para usar sqrt, acos
#include <cmath>

// Para controlar las pre y post condiciones mediante asertos
#include <cassert>

#include "Vector3D.hpp"


// OBSERVADORES
double ed::Vector3D::get1()const
{
	return x_;
}

double ed::Vector3D::get2()const 
{
	return y_;
}

double ed::Vector3D::get3()const
{
	return z_;
}

double ed::Vector3D::modulo()const
{
	double modulo;
	modulo=sqrt(get1()*get1()+get2()*get2()+get3()*get3());

		#ifndef NDEBUG
			assert(modulo==sqrt(get1()*get1()+get2()*get2()+get3()*get3()));
		#endif

	return modulo;
}

double ed::Vector3D::angulo(Vector3D v)const 
{

		#ifndef NDEBUG
			assert(modulo()*v.modulo()>0);
		#endif 

	double angulo;
	angulo=acos(dotProduct(v)/std::abs(modulo()*v.modulo()));

	
		#ifndef NDEBUG
			assert((angulo-acos(dotProduct(v)/std::abs(modulo()*v.modulo())))<COTA_ERROR);
		#endif
	
	return angulo;
}

double ed::Vector3D::dotProduct(Vector3D const &v)const
{
	double pe;
	pe=get1()*v.get1()+get2()*v.get2()+get3()*v.get3();

		#ifndef NDEBUG
			assert(pe==get1()*v.get1()+get2()*v.get2()+get3()*v.get3());
		#endif

	return pe;
}

ed::Vector3D ed::Vector3D::crossProduct(Vector3D const &v)const
{
	double w1,w2,w3;
	
		w1=get2()*v.get3()-get3()*v.get2();
		w2=-get1()*v.get3()+get3()*v.get1();
		w3=get1()*v.get2()-get2()*v.get1();

	Vector3D a(w1,w2,w3);


			#ifndef NDEBUG
				assert(dotProduct(a)<COTA_ERROR);
				assert(v.dotProduct(a)<COTA_ERROR);
				assert(std::abs(a.modulo()-modulo()*v.modulo()*sin(angulo(v)))<COTA_ERROR);
			#endif

	return a;
	
}

double ed::Vector3D::alfa()const
{
		#ifndef NDEBUG
			assert(modulo()>0);
		#endif

	double alfa;
	Vector3D v;
	v.set1(1);
	v.set2(0);
	v.set3(0);

	alfa=angulo(v);

		#ifndef NDEBUG
			assert(alfa==angulo(v));
		#endif

	return alfa;
}

double ed::Vector3D::beta()const
{

		#ifndef NDEBUG
			assert(modulo()>0);
		#endif

	double beta;
	Vector3D v;
	v.set1(0);
	v.set2(1);
	v.set3(0);

	beta=angulo(v);


		#ifndef NDEBUG
			assert(beta==angulo(v));
		#endif

	return beta;
}

double ed::Vector3D::gamma()const
{
		#ifndef NDEBUG
			assert(modulo()>0);
		#endif

	double gamma;
	Vector3D v;
	v.set1(0);
	v.set2(0);
	v.set3(1);

	gamma=angulo(v);

		#ifndef NDEBUG
			assert(gamma==angulo(v));
		#endif

	return gamma;
}

double ed::Vector3D::productoMixto(Vector3D v1, Vector3D v2)const
{ 
	double prodmixto=dotProduct(v1.crossProduct(v2));

	
		#ifndef NDEBUG
			assert((dotProduct(v1.crossProduct(v2)))<COTA_ERROR);
		#endif

	
	return prodmixto;

}
// COMPLETAR


////////////////////////////////////////////////////////////////

// MODIFICADORES
void ed::Vector3D::set1(double x)
{
	x_=x;

		#ifndef NDEBUG
			assert(get1()==x);
		#endif
}

void ed::Vector3D::set2(double y)
{
	y_=y;

		#ifndef NDEBUG
			assert(get2()==y);
		#endif
}

void ed::Vector3D::set3(double z)
{
	z_=z;

		#ifndef NDEBUG
			assert(get3()==z);
		#endif
}

void ed::Vector3D::sumConst(double k)
{
	Vector3D old;
		old.set1(get1());
		old.set2(get2());
		old.set3(get3());

	set1(get1()+k);
	set2(get2()+k);
	set3(get3()+k);

		#ifndef	NDEBUG
			assert(get1()==old.get1()+k && get2()==old.get2()+k && get3()==old.get3()+k);
		#endif
}

void ed::Vector3D::sumVect(Vector3D v)
{
	Vector3D old;
		old.set1(get1());
		old.set2(get2());
		old.set3(get3());

	set1(get1()+v.get1());
	set2(get2()+v.get2());
	set3(get3()+v.get3());

		#ifndef NDEBUG
			assert((get1()==old.get1()+v.get1())&&(get2()==old.get2()+v.get2())&&(get3()==old.get3()+v.get3()));
		#endif
}

void ed::Vector3D::multConst(double k)
{
	Vector3D old;
		old.set1(get1());
		old.set2(get2());
		old.set3(get3());

	set1(get1()*k);
	set2(get2()*k);
	set3(get3()*k);

		#ifndef	NDEBUG
			assert(get1()==old.get1()*k && get2()==old.get2()*k && get3()==old.get3()*k);
		#endif
}

void ed::Vector3D::multVect(Vector3D v)
{

	Vector3D old;
		old.set1(get1());
		old.set2(get2());
		old.set3(get3());

	set1(get1()*v.get1());
	set2(get2()*v.get2());
	set3(get3()*v.get3());

		#ifndef NDEBUG
			assert((get1()==old.get1()*v.get1())&&(get2()==old.get2()*v.get2())&&(get3()==old.get3()*v.get3()));
		#endif
}
// COMPLETAR



////////////////////////////////////////////////////////////////////////////////

// OPERADORES

ed::Vector3D & ed::Vector3D::operator+(Vector3D const &v)const
{
	double x, y, z;

		x=get1()+v.get1();
		y=get2()+v.get2();
		z=get3()+v.get3();

	Vector3D *a=new Vector3D(x,y,z);

		#ifndef NDEBUG
			assert(a->get1()-get1()-v.get1()<COTA_ERROR);
			assert(a->get2()-get2()-v.get2()<COTA_ERROR);
			assert(a->get3()-get3()-v.get3()<COTA_ERROR);
		#endif

	return *a;

}

ed::Vector3D & ed::Vector3D::operator-(Vector3D const &v)const
{
	double x, y, z;

		x=get1()-v.get1();
		y=get2()-v.get2();
		z=get3()-v.get3();

	Vector3D *a=new Vector3D(x,y,z);

		#ifndef NDEBUG
			assert(a->get1()-get1()-v.get1()<COTA_ERROR);
			assert(a->get2()-get2()-v.get2()<COTA_ERROR);
			assert(a->get3()-get3()-v.get3()<COTA_ERROR);
		#endif

	return *a;
}

ed::Vector3D & ed::Vector3D::operator+()const
{
	double x, y, z;

		x=get1();
		y=get2();
		z=get3();

	Vector3D *a=new Vector3D(x,y,z);

		#ifndef NDEBUG
			assert((a->get1()==get1())&&(a->get2()==get2())&&(a->get3()==get3()));
		#endif

	return *a;
}

ed::Vector3D & ed::Vector3D::operator-()const
{
	double x, y, z;

		x=-get1();
		y=-get2();
		z=-get3();

	Vector3D *a=new Vector3D(x,y,z);

		#ifndef NDEBUG
			assert((a->get1()==-get1())&&(a->get2()==-get2())&&(a->get3()==-get3()));
		#endif

	return *a;
}

ed::Vector3D & ed::Vector3D::operator=(Vector3D const &v)
{
	this->x_=v.get1();
	this->y_=v.get2();
	this->z_=v.get3();

		#ifndef NDEBUG
			assert(get1()==v.get1()&&get2()==v.get2()&&get3()==v.get3());
		#endif

	return *this;
}

bool ed::Vector3D::operator==(Vector3D const &v)const
{
	if(get1()==v.get1() && get2()==v.get2() && get3()==v.get3())
	{
		return true;
	}
	else
	{
		return false;
	}
		#ifndef NDEBUG
			assert(true==(get1()==v.get1()&&get2()==v.get2()&&get3()==v.get3()));
		#endif 
}

ed::Vector3D & ed::Vector3D::operator*(double k)const 
{
	double x,y,z;

		x=k*get1();
		y=k*get2();
		z=k*get3();

	Vector3D *a=new Vector3D(x,y,z);

		#ifndef NDEBUG
			assert((a->get1()==get1()*k)&&(a->get2()==get2()*k)&&(a->get3()==get3()*k));
		#endif

	return *a;
}

double ed::Vector3D::operator*(Vector3D const &v)const
{
	double prodEscalar;

	prodEscalar=get1()*v.get1()+get2()*v.get2()+get3()*v.get3();

		#ifndef NDEBUG
			assert(prodEscalar==get1()*v.get1()+get2()*v.get2()+get3()*v.get3());
		#endif

	return prodEscalar;
}

ed::Vector3D & ed::Vector3D::operator^(Vector3D const &v)const
{

	double w1,w2,w3;

		w1=get2()*v.get3()-get3()*v.get2();
		w2=-get1()*v.get3()+get3()*v.get1();
		w3=get1()*v.get2()-get2()*v.get1();

	Vector3D *a=new Vector3D(w1,w2,w3);

	Vector3D o;
		o.set1(a->get1());
		o.set2(a->get2());
		o.set3(a->get3());


		#ifndef NDEBUG
			assert(dotProduct(o)<COTA_ERROR);
				assert(v.dotProduct(o)<COTA_ERROR);
				assert(std::abs(o.modulo()-modulo()*v.modulo()*sin(angulo(v)))<COTA_ERROR);
		#endif

	return *a;
}


// COMPLETAR



////////////////////////////////////////////////////////////////////////////////

// FUNCIONES DE LECTURA Y ESCRITURA

void ed::Vector3D::leerVector3D()
{
	std::cout<<"X: ";
	std::cin>>x_;
	std::cout<<"Y: ";
	std::cin>>y_;
	std::cout<<"Z: ";
	std::cin>>z_;
}

void ed::Vector3D::escribirVector3D()const
{

	std::cout<< " X: "<<get1()<<" Y: "<<get2()<<" Z: "<<get3()<<"\n";

}
// COMPLETAR


////////////////////////////////////////////////////////////////////////////////


// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed{


// Producto "por un" escalar (prefijo): k * v
ed::Vector3D & operator* (double k, ed::Vector3D const &v)
{

	// COMPLETAR
	double x, y,z;

		x=k*v.get1();
		y=k*v.get2();
		z=k*v.get3();

	Vector3D *a=new Vector3D(x,y,z);

	return *a;

}


// Sobrecarga del operador de salida
// Se escriben por pantalla las coordenadas del vector 3D  de la forma (v1, v2, v3)
ostream &operator<<(ostream &stream, ed::Vector3D const &objeto)
{
	// COMPLETAR
		stream<<objeto.get1();
		stream<<",";
		stream<<objeto.get2();
		stream<<",";
		stream<<objeto.get3();

  return stream;
}

// Sobrecarga del operador de entrada
istream &operator>>(istream &stream, ed::Vector3D &objeto)
{
  // COMPLETAR
	double n;
	stream>>n;
	objeto.set1(n);

	stream>>n;
	objeto.set2(n);

	stream>>n;
	objeto.set3(n);

  return stream;
} 

} // Fin del espacio de nombres ed
