/*! 
   \file  Medicion.cpp
   \brief Fichero que contiene el código de las funciones de la clase Medicion
*/


// Ficheros de cabecera
#include <iostream>

// atoi, atof
#include <stdlib.h>

#include "Medicion.hpp"

#include "macros.hpp"
// COMPLETAR

ed::Fecha ed::Medicion::getFecha()const
{
	return _fecha;
}

float ed::Medicion::getPrecipitacion()const
{
	return _precipitaciondelluvia;
}

void ed::Medicion::setFecha(Fecha f)
{
	_fecha=f;

		#ifndef NDBUG
			assert(getFecha()==_fecha);
		#endif
}

void ed::Medicion::setPrecipitacion(float p)
{
		#ifndef NDEBUG
			assert(p>=0.0);
		#endif

	_precipitaciondelluvia=p;

		#ifndef NDEBUG
			assert(getPrecipitacion()==_precipitaciondelluvia);
		#endif
}

bool ed::Medicion::operator==(Medicion const &m)
{
	if(getFecha()==m.getFecha())
	{
		return true;

			#ifndef NDEBUG
				assert(true==(getFecha()==m.getFecha()));
			#endif
	}
	else
	{
		return false;
			#ifndef NDEBUG
				assert(false==(getFecha()==m.getFecha()));
			#endif
	}
}

ed::Medicion ed::Medicion::operator=(Medicion const &m)
{
	setFecha(m.getFecha());
	setPrecipitacion(m.getPrecipitacion());

			#ifndef NDEBUG
				assert(getFecha()==m.getFecha());
				assert(getPrecipitacion()==m.getPrecipitacion());
			#endif

	return *this;
}

bool ed::Medicion::operator>(Medicion const &m)
{
	if(getPrecipitacion()>m.getPrecipitacion())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ed::Medicion::operator<(Medicion const &m)
{
	if(getPrecipitacion()<m.getPrecipitacion())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ed::Medicion::operator>=(Medicion const &m)
{
	if(getPrecipitacion()>=m.getPrecipitacion())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool ed::Medicion::operator<=(Medicion const &m)
{
	if(getPrecipitacion()<=m.getPrecipitacion())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ed::Medicion::leerMedicion()
{
	float p;
	Fecha f;
	std::cout<<"Escribe los datos de la medición"<<"\n";
	std::cout<<"Precipitacion: ";
	std::cin>>p;
	setPrecipitacion(p);
	std::cout<<"Escribe la fecha de la precipitacion: "<<"\n";
	f.leerFecha();
	setFecha(f);

}

void ed::Medicion::escribirMedicion()
{
	std::cout<<BIGREEN<<"Fecha: "<<BIBLUE<<_fecha.getDia()<<"-"<<_fecha.getMes()<<"-"<<_fecha.getAgno()<<BIGREEN<<"\t"<<" Precipitacion: "<<BIBLUE<<getPrecipitacion()<<RESET<<"\n";
}
////////////////////////////////////////////////////////////////////////////////


// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed{

// Sobrecarga del operador de salida
ostream &operator<<(ostream &stream, ed::Medicion const &medicion)
{

    stream<<medicion.getFecha();
    stream<<medicion.getPrecipitacion();

  return stream;
}

// Sobrecarga del operador de entrada
istream &operator>>(istream &stream, ed::Medicion &medicion)
{
	//DD-MM-AA P
	//DD-MM-AA P
 std::string dia, mes, agno;
  std:: string precip;

   std::getline(stream,dia,'-');
   
   std::getline(stream,mes,'-');

   std::getline(stream,agno,' ');

   std::getline(stream,precip,'\n');

   Fecha f(atoi(dia.c_str()), atoi(mes.c_str()), atoi(agno.c_str()));
   medicion.setFecha(f);
   medicion.setPrecipitacion(atof(precip.c_str()));
   
   return stream;
 
}

} // Fin del espacio de nombres ed
