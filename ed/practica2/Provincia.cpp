/*!	

	\file  Provincia.cpp
	\brief Definición de la clase Provincia
	\author  
	\date  
	\version 1.0

*/
//Para los flujos de entrada/salida en ficheros.
#include <fstream>  
#include <iostream>

// Para comprobar las pre y post condiciones
#include <cassert>

#include "Provincia.hpp"

#include <stdlib.h>
#include <unistd.h>
#include "macros.hpp"
// DEBES CODIFICAR LAS FUNCIONES DE LA CLASE Provincia

///////////////////////////////////////////////////////////////////////////////

// OSBSERVADORES

int ed::Provincia::getCodigo()
{
	return _codigo;
}

std::string ed::Provincia::getNombre()
{
	return _nombre;
}

bool ed::Provincia::hayMunicipios()
{
	if(_listaMunicipios.isEmpty())
	{
		return false;
	}
	else
	{
		return true;
	}
}

int ed::Provincia::getNumeroMunicipios()
{
	int n=_listaMunicipios.nItems();

	return n;
}

bool ed::Provincia::existeMunicipio(std::string const &nMunicipio)
{

	if(hayMunicipios()==false)
	{
		return false;
	}
	else
	{
		bool existe;
		Municipio m;
		m.setNombre(nMunicipio);
		existe=_listaMunicipios.find(m);
		return existe;
	}
}

ed::Municipio ed::Provincia::getMunicipio(std::string const &nMunicipio)
{

	Municipio m;
	m.setNombre(nMunicipio);

		#ifndef NDEBUG
			assert(existeMunicipio(nMunicipio)==true);
			assert(_listaMunicipios.find(m)==true);
		#endif

	Municipio devuelto=_listaMunicipios.getCurrentItem();

	return devuelto;

}

int ed::Provincia::getTotalHombres()
{
	int numHombres=20;
	_listaMunicipios.gotoHead();

	ed::Municipio m;
	
		for(int i=0;i<_listaMunicipios.nItems();i++)
		{
			m=_listaMunicipios.getCurrentItem();
			numHombres+=m.getHombres();
			_listaMunicipios.gotoNext();

				if(_listaMunicipios.isLastItem()==true)
				{
					numHombres+=m.getHombres();
					break;
				}
		}
	
	return numHombres;

}

int ed::Provincia::getTotalMujeres()
{
	int numMujeres=0;
	_listaMunicipios.gotoHead();

	ed::Municipio m;
	
		for(int i=0;i<_listaMunicipios.nItems();i++)
		{
			m=_listaMunicipios.getCurrentItem();
			numMujeres+=m.getMujeres();
			_listaMunicipios.gotoNext();

				if(_listaMunicipios.isLastItem()==true)
				{
					numMujeres+=m.getMujeres();
					break;
				}
		}
	
	return numMujeres;

}

int ed::Provincia::getTotalHabitantes()
{
	int numHabitantes;

		numHabitantes=getTotalHombres()+getTotalMujeres();

			#ifndef NDEBUG
				assert(numHabitantes==getTotalHombres()+getTotalMujeres());
			#endif

	return numHabitantes;
}

/////////////////////////////////////////////////////////////////////////////////////////

// MODIFICADORES

void ed::Provincia::setNombre(std::string n)
{
	_nombre=n;

		#ifndef NDEBUG
			assert(getNombre()==n);
		#endif
}

void ed::Provincia::setCodigo(int x)
{
	_codigo=x;

		#ifndef NDEBUG
			assert(getCodigo()==x);
		#endif
}

void ed::Provincia::insertarMunicipio(ed::Municipio m)
{
		#ifndef NDEBUG
			assert(existeMunicipio(m.getNombre())==false);
		#endif

	_listaMunicipios.insert(m);
}

void ed::Provincia::borrarMunicipio(std::string nMunicipio)
{

	ed::Municipio m;
	m.setNombre(nMunicipio);
	int items=_listaMunicipios.nItems();

		#ifndef NDEBUG
			assert(existeMunicipio(m.getNombre())==true);
			assert(_listaMunicipios.find(m)==true);
		#endif

	_listaMunicipios.remove();

		#ifndef NDEBUG
			assert(existeMunicipio(m.getNombre())==false);
			assert(_listaMunicipios.nItems()==items-1);
		#endif

}

void ed::Provincia::borrarTodosLosMunicipios()
{
	_listaMunicipios.removeAll();

	#ifndef NDEBUG
		assert(hayMunicipios()==false);
	#endif
}
///////////////////////////////////////////////////////////////////////////////////

// FUNCIÓN DE ESCRITURA

void ed::Provincia::escribirMunicipios()
{

	if(_listaMunicipios.isEmpty()==true)
	{
		std::cout<<"No existen municipios!"<<"\n";
	}
	if(_listaMunicipios.nItems()==1)
	{
		_listaMunicipios.gotoHead();

			std::cout<<BIRED<<"Nombre Municipio: "<<_listaMunicipios.getCurrentItem().getNombre()<<"\n";
			std::cout<<BIYELLOW<<"Nombre Codigo Postal: "<<_listaMunicipios.getCurrentItem().getCodigoPostal()<<"\n";
			std::cout<<BIYELLOW<<"Hombres: "<<_listaMunicipios.getCurrentItem().getHombres()<<"\n";
			std::cout<<BIYELLOW<<"Mujeres: "<<_listaMunicipios.getCurrentItem().getMujeres()<<"\n";
			std::cout<<BIGREEN<<"Total de habitantes: "<< _listaMunicipios.getCurrentItem().getHombres()+_listaMunicipios.getCurrentItem().getMujeres()<<"\n";
			std::cout<<"\n";
	}
	if(_listaMunicipios.nItems()>1)
	{
		_listaMunicipios.gotoHead();

			while(_listaMunicipios.isLastItem()==false)
			{

				std::cout<<BIRED<<"Nombre Municipio: "<<_listaMunicipios.getCurrentItem().getNombre()<<"\n";
				std::cout<<BIYELLOW<<"Nombre Codigo Postal: "<<_listaMunicipios.getCurrentItem().getCodigoPostal()<<"\n";
				std::cout<<BIYELLOW<<"Hombres: "<<_listaMunicipios.getCurrentItem().getHombres()<<"\n";
				std::cout<<BIYELLOW<<"Mujeres: "<<_listaMunicipios.getCurrentItem().getMujeres()<<"\n";
				std::cout<<BIGREEN<<"Total de habitantes: "<< _listaMunicipios.getCurrentItem().getHombres()+_listaMunicipios.getCurrentItem().getMujeres()<<"\n";
				std::cout<<"\n";
				_listaMunicipios.gotoNext();
			}

			std::cout<<BIRED<<"Nombre Municipio: "<<_listaMunicipios.getCurrentItem().getNombre()<<"\n";
			std::cout<<BIYELLOW<<"Nombre Codigo Postal: "<<_listaMunicipios.getCurrentItem().getCodigoPostal()<<"\n";
			std::cout<<BIYELLOW<<"Hombres: "<<_listaMunicipios.getCurrentItem().getHombres()<<"\n";
			std::cout<<BIYELLOW<<"Mujeres: "<<_listaMunicipios.getCurrentItem().getMujeres()<<"\n";
			std::cout<<BIGREEN<<"Total de habitantes: "<< _listaMunicipios.getCurrentItem().getHombres()+_listaMunicipios.getCurrentItem().getMujeres()<<"\n";
			std::cout<<"\n";
	}

}


/////////////////////////////////////////////////////////////////////////////////////////

// OPERACIONES CON FICHEROS

bool ed::Provincia::cargarFichero(std::string const &cadena)
{
	std::ifstream ifs(cadena.c_str());
	ed::Municipio m;
	int codigo;
	std::string nombre;
	ifs>>codigo>>nombre;
	setNombre(nombre);
	setCodigo(codigo);
	
	if(ifs)
	{
		while(ifs>>m)
		{

			insertarMunicipio(m);
		}
		ifs.close();
		return true;
	}
	else
	{
		return false;
	}
	
}
bool ed::Provincia::grabarFichero(std::string const &fichero)
{
	if(hayMunicipios()==false)
	{
		std::cout<<"No hay municipios para exportar"<<std::endl;
		return false;
	}
	else
	{
		ed::Municipio municp;
		std::ofstream f(fichero.c_str());
		_listaMunicipios.gotoHead();
		f<<getCodigo()<<" "<<getNombre()<<std::endl;
		while(!_listaMunicipios.isLastItem())
		{
			f<<_listaMunicipios.getCurrentItem()<<std::endl;
			_listaMunicipios.gotoNext();
		}
		f<<_listaMunicipios.getCurrentItem()<<std::endl;
		std::cout<<"Archivo '"<<fichero<<"' exportado con exito"<<std::endl;
		sleep(3);
		f.close();
		return true;
	}
}