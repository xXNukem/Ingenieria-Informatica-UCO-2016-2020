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
	return v[0];
}

double ed::Vector3D::get2()const
{
	return v[1];
}

double ed::Vector3D::get3()const
{
	return v[2];
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

double ed::Vector3D::angulo(Vector3D const &w)const
{
		#ifndef NDEBUG
			assert(modulo()*w.modulo()>0);
		#endif 

	double angulo;

		angulo=acos((get1()*w.get1()+get2()*w.get2()+get3()*w.get3())/std::abs(modulo()*w.modulo()));

		#ifndef NDEBUG
			assert((angulo-acos(dotProduct(w)/std::abs(modulo()*w.modulo())))<COTA_ERROR);
		#endif

	return angulo;
}

double ed::Vector3D::alfa()const
{

		#ifndef NDEBUG
			assert(modulo()>0);
		#endif

	Vector3D w;
	double alfa;

		w.set1(1);
		w.set2(0);
		w.set3(0);

	alfa=angulo(w);

		#ifndef NDEBUG
			assert(alfa==angulo(w));
		#endif

	return alfa;
}

double ed::Vector3D::beta()const
{

		#ifndef NDEBUG
			assert(modulo()>0);
		#endif

	Vector3D w;
	double beta;

		w.set1(0);
		w.set2(1);
		w.set3(0);

	beta=angulo(w);

		#ifndef NDEBUG
			assert(beta==angulo(w));
		#endif

	return beta;
}

double ed::Vector3D::gamma()const
{
		#ifndef NDEBUG
			assert(modulo()>0);
		#endif

	Vector3D w;
	double gamma;

		w.set1(0);
		w.set2(0);
		w.set3(1);

	gamma=angulo(w);

		#ifndef NDEBUG
			assert(gamma==angulo(w));
		#endif

	return gamma;
}

double ed::Vector3D::dotProduct(Vector3D const &v)const
{
	double productoEscalar;

		productoEscalar=get1()*v.get1()+get2()*v.get2()+get3()*v.get3();

		#ifndef NDEBUG
			assert(productoEscalar==get1()*v.get1()+get2()*v.get2()+get3()*v.get3());
		#endif

	return productoEscalar;
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

double ed::Vector3D::productoMixto(Vector3D v1, Vector3D v2)const
{
	double prodMixto=dotProduct(v1.crossProduct(v2));

		#ifndef NDEBUG
			assert((dotProduct(v1.crossProduct(v2)))<COTA_ERROR);
		#endif

	return prodMixto;
}
// COMPLETAR


////////////////////////////////////////////////////////////////

// MODIFICADORES
void ed::Vector3D::set1(double x)
{
	v[0]=x;

		#ifndef NDEBUG
			assert(get1()==x);
		#endif
}

void ed::Vector3D::set2(double y)
{
	v[1]=y;

		#ifndef NDEBUG
			assert(get2()==y);
		#endif
}

void ed::Vector3D::set3(double z)
{
	v[2]=z;

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
	this->v[0]=v.get1();
	this->v[1]=v.get2();
	this->v[2]=v.get3();

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
	std::cin>>v[0];
	std::cout<<"Y: ";
	std::cin>>v[1];
	std::cout<<"Z: ";
	std::cin>>v[2];
}

void ed::Vector3D::escribirVector3D()const
{
	std::cout<<"("<<get1()<<","<<get2()<<","<<get3()<<")"<<"\n";
}

// COMPLETAR


////////////////////////////////////////////////////////////////////////////////


// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed{


// Producto "por un" escalar (prefijo): k * v
ed::Vector3D & operator* (double k, ed::Vector3D const &v)
{

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
		stream<<objeto.get1();
		stream<<",";
		stream<<objeto.get2();
		stream<<",";
		stream<<objeto.get3();

  return stream;

  return stream;
}

// Sobrecarga del operador de entrada
istream &operator>>(istream &stream, ed::Vector3D &objeto)
{
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
