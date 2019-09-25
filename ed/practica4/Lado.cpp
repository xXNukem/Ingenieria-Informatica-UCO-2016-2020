/*! 
   \file  Lado.cpp
   \brief Fichero que contiene el código de las funciones de la clase Lado
*/


// Ficheros de cabecera
#include <iostream>

// atoi
#include <stdlib.h>

#include "Lado.hpp"

namespace ed
{

//Observadores

	float ed::Lado::getPeso()const
	{
		return _peso;
	}

	Vertice ed::Lado::getVertice1()const
	{
		return _v1;
	}

	Vertice ed::Lado::getVertice2()const
	{
		return _v2;
	}


//Modificadores

	void ed::Lado::setVertice1(Vertice v1)
	{
		_v1=v1;
	}

	void ed::Lado::setVertice2(Vertice v2)
	{
		_v2=v2;
	}

	void ed::Lado::setPeso(float p)
	{
		_peso=p;
	}


float ed::Lado::calcularDistanciaEuclidea ( ed::Vertice v1, ed::Vertice v2 )
{
    float valorDevuelto = 0, x1, x2, y1, y2;
    //Obtenemos los valores de X e Y
    x1 = v1.getX();
    x2 = v2.getX();
    y1 = v1.getY();
    y2 = v2.getY();
    //Calculamos la distancia euclidea
    valorDevuelto = std::sqrt ( ( ( x2 - x1 ) * ( x2 - x1 ) ) + ( ( y2 - y1 ) * ( y2 - y1 ) ) );
    return valorDevuelto;
}

ed::Lado ed::Lado::operator=(Lado & l )
{
	setVertice1(l.getVertice1());
	setVertice2(l.getVertice2());
	setPeso(l.getPeso());

	return *this;
}

}