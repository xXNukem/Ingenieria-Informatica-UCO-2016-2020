/*! 
   \file  Lado.cpp
   \brief Fichero que contiene el código de las funciones de la clase Vertice
*/


#include "Vertice.hpp"

#include <iostream>

using namespace std;

namespace ed
{
//Modificadores

void ed::Vertice::setX(float x)
{
	_x=x;

		#ifndef NDEBUG
			assert(_x==x);
		#endif
}

void ed::Vertice::setY(float y)
{
	_y=y;

		#ifndef NDEBUG
			assert(_y==y);
		#endif
}

void ed::Vertice::setLabel(int label)
{
	_label=label;

		#ifndef NDEBUG
			assert(_label==label);
		#endif
}

void ed::Vertice::setData(Vertice v)
{
	setX(v.getX());
	setY(v.getY());
	setLabel(v.getLabel());

			#ifndef NDEBUG
						assert(_x==v.getX());
						assert(_y==v.getY());
						assert(_label==v.getLabel());
					#endif
}


//Observadores

float ed::Vertice::getX()const
{
	return _x;
}

float ed::Vertice::getY()const
{
	return _y;
}

int ed::Vertice::getLabel()const
{
	return _label;
}


//Sobrecarga de operadores de entrada

	std::ostream &operator<<(std::ostream &stream, ed::Vertice const &v)
	{
		stream<<"("<<v.getX()<<","<<v.getY()<<")";

		return stream;	
	}

	std::istream &operator>>(std::istream &stream, ed::Vertice &v)
	{
		std::string x,y;

		std::getline(stream,x,' ');
		std::getline(stream,y,'\n');

		v.setX(atof(x.c_str()));
		v.setY(atof(y.c_str()));

		return stream;

	}

//Operadores de comparacion y asignacion

	ed::Vertice &ed::Vertice::operator=(const ed::Vertice &v)
	{
		this->setX(v.getX());
		this->setY(v.getY());
		this->setLabel(v.getLabel());

		return *this;
	}

	bool ed::Vertice::operator==(const ed::Vertice & v)const
	{
		if(this->getX()==v.getX() && this->getY()==v.getY())
		{
			return true;
		}
		else
		{
			return false;
		}
	}


}