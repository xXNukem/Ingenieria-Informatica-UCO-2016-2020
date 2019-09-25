/*!
  \file   funcionesAuxiliares.cpp
  \brief  Código de las funciones auxiliares del programa principal de la provincia
  \author 
  \date   
*/

#include <iostream>
#include <string>  

// Para usar atoi
#include <stdlib.h>

#include "Provincia.hpp"

#include "Municipio.hpp"

#include "funcionesAuxiliares.hpp"


#include "macros.hpp"

int ed::menu()
{
	int opcion;
	int posicion;

	// Se muestran las opciones del menú
	posicion=2;

	// Se borra la pantalla
	std::cout << CLEAR_SCREEN;

	PLACE(1,10);
	std::cout << BIBLUE;
	std::cout << "Programa principial | Opciones del menú";
	std::cout << RESET;

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout <<  "[1] Comprobar si la provincia tiene municipios";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << "[2] Cargar la provincia desde un fichero";

	PLACE(posicion++,10);
	std::cout << "[3] Grabar la provincia en un fichero";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;
 
	PLACE(posicion++,10);
	std::cout << "[4] Consultar datos de la provincia";

	PLACE(posicion++,10);
	std::cout <<  "[5] Mostrar municipios de la provincia";

	PLACE(posicion++,10);
	std::cout << "[6] Modificar datos de la provincia: código o nombre";

	PLACE(posicion++,10);
	std::cout << "[7] Borrar todos los municipios de una provincia";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << "[8] Consultar un municipio";

	PLACE(posicion++,10);
	std::cout << "[9] Insertar un municipio";

	PLACE(posicion++,10);
	std::cout << "[10] Borrar un municipio";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << BIRED << "[0] Salir";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << BIGREEN;
	std::cout << "Opción: ";
	std::cout << RESET;

	// Se lee el número de opción
	std::cin >> opcion;

    // Se elimina el salto de línea del flujo de entrada
    std::cin.ignore();

	return opcion;
}


//////////////////////////////////////////////////////////////////////////////

void ed::comprobarProvinciaVacia(ed::Provincia &provincia)
{
	if(provincia.hayMunicipios()==true)
	{
		std::cout << BIGREEN << "Hay municipios en la provincia" << "\n";
	}
	else
	{
		std::cout << BIRED << "No hay municipios en la provincia" << "\n";
	}

	return;
}

//////////////////////////////////////////////////////////////////////////////

void ed::cargarProvincia(ed::Provincia &provincia)
{
	
	if(provincia.getNombre()!="")
	{
		std::cout<<BIRED<<"Ya hay un fichero "<<"\n";
	}
	else
	{
		std::string cadena;
		std::cin>>cadena;
		provincia.cargarFichero(cadena);
	}


	return;
}

void ed::grabarProvincia(ed::Provincia  &provincia)
{
	if(provincia.getNombre()=="")
	{
		std::cout<<BIRED<<"Hay que cargar antes un fichero de provincia"<<"\n";
	}
	else
	{
		std::string cadena;
		std::cin>>cadena;
		provincia.grabarFichero(cadena);
	}

	return;
}

//////////////////////////////////////////////////////////////////////

void ed::consultarDatosDeProvincia(ed::Provincia &provincia)
{

	if(provincia.getNombre()=="")
	{
		std::cout<<BIRED<<"No se ha cargado ninguna provincia"<<"\n";
	}
	else
	{
		std::cout<< BIRED << "Nombre: "<< provincia.getNombre() << "\n";
		std::cout <<BIYELLOW << "Codigo: "<< provincia.getCodigo()<< "\n";
		std::cout <<BIYELLOW<< "Numero de municipios: "<< provincia.getNumeroMunicipios()<<"\n";
		std::cout <<BIYELLOW<< "Hombres: "<<provincia.getTotalHombres()<<"\n";
		std::cout <<BIYELLOW<< "Mujeres: "<<provincia.getTotalMujeres()<<"\n";
		std::cout <<BIGREEN<< "Total de Habitantes: "<<provincia.getTotalHabitantes()<<"\n";
	}

	return;
}


//
void ed::mostrarMunicipiosDeProvincia(ed::Provincia & provincia)
{
	if(provincia.hayMunicipios()==true)
	{
		provincia.escribirMunicipios();

		std::cout<<BIGREEN<< "Todos los municipios listados "<<"\n";

	}
	else
	{
		std::cout<<BIRED<< "La provincia no tiene municipios "<<"\n";
	}

	return;
}


////////////////////////////////////////////////////////////////////////
void ed::modificarDatosDeProvincia(ed::Provincia &provincia)
{


	if(provincia.getNombre()=="")
	{
		std::cout<<BIRED<<"No se ha cargado ninguna provincia"<<"\n";
	}
	else
	{
		int opcion, codigo;
		std::string nombre; 

		do{
			std::cout << BIYELLOW  << "Nombre de la provincia: "  << RESET 
					  << provincia.getNombre() << std::endl; 
			std::cout << BIYELLOW << "Código de la provincia: " << RESET
					  << provincia.getCodigo() << std::endl  << std::endl;

			std::cout << "Indique qué dato desea modificar: " << std::endl;
			std::cout << BIBLUE << "(1) Nombre " << std::endl;
			std::cout << BIBLUE << "(2) Código" << std::endl  << std::endl;
			std::cout << BIRED << "(0) Salir" << std::endl << std::endl  << std::endl;
			std::cout << BIGREEN;
			std::cout << "Opción: ";
			std::cout << RESET;

			// Se lee el número de opción
			std::cin >> opcion;

	    	// Se elimina el salto de línea del flujo de entrada
		    std::cin.ignore();

			std::cout << std::endl;
				
			switch(opcion)
			{
				case 0: 
						// Fin de las modificaciones
						break;
				case 1:
						std::cout << BIGREEN;
						std::cout << "Nuevo nombre de la provincia: ";
						std::cout << RESET;
						std::getline(std::cin,nombre);
						provincia.setNombre(nombre);
						break;

				case 2:
						std::cout << BIGREEN;
						std::cout << "Nuevo código de la provincia: ";
						std::cout << RESET;
						std::cin >> codigo;
						provincia.setCodigo(codigo);
						break;
				default:
						std::cout << BIRED << "Opción incorrecta:" << RESET 
								  << opcion << std::endl;
			}
		}while (opcion != 0);
	}

		return;
}


void ed::borrarTodosLosMunicipiosDeProvincia(ed::Provincia &provincia)
{
	if(provincia.hayMunicipios()==false)
	{
		std::cout<<BIRED<<"No hay municipios que borrar"<<"\n";
	}
	else
	{
		provincia.borrarTodosLosMunicipios();

		std::cout<< BIGREEN << "Se han borrado todos los municipios"<<"\n";

		return;
	}
}


void ed::consultarMunicipioDeProvincia(ed::Provincia &provincia)
{

std::string nMunicipio;

	if(provincia.hayMunicipios()==true)
	{
		std::cout<<"Escribe el municipio a consultar"<<"\n";
		std::getline(std::cin,nMunicipio);

			if(provincia.existeMunicipio(nMunicipio)==true)
			{
				Municipio m=provincia.getMunicipio(nMunicipio);

					std::cout<<BIGREEN<<"Nombre: "<<m.getNombre()<<"\n";
					std::cout<<BIYELLOW<<"Codigo Postal: "<<m.getCodigoPostal()<<"\n";
					std::cout<<BIYELLOW<<"Hombres: "<<m.getHombres()<<"\n";
					std::cout<<BIYELLOW<<"Mujeres: "<<m.getMujeres()<<"\n";
					std::cout<<BIRED<<"Total Habitantes: "<<m.getHombres()+m.getMujeres()<<"\n";
			}
			else
			{
				std::cout<<BIRED<<"El municipio no existe"<<"\n";
			}
	}
	else
	{
		std::cout<< BIRED <<"La provincia no tiene municipios"<< "\n";
	}	

	return;
}

void ed::insertarMunicipioEnProvincia(ed::Provincia &provincia)
{
	if(provincia.getNombre()=="")
	{
		std::cout<<BIRED<<"No hay provincia a la que meter municipios"<<"\n";
	}
	else
	{
		std::string nMunicipio;
		std::cout<<"Escribe el nombre del municipio a insertar"<<"\n";
		std::getline(std::cin,nMunicipio);

			if(provincia.existeMunicipio(nMunicipio)==true)
			{
				std::cout<<BIRED<<"El municipio ya existe"<<"\n";
			}
			else
			{
				Municipio m;
				m.setNombre(nMunicipio);
				std::cout<<BIYELLOW<<"Escribe el codigo postal: "<<"\n";
				int cp;
				std::cin>>cp;
				m.setCodigoPostal(cp);
				std::cout<<BIYELLOW<<"Escribe el numero de hombres: "<<"\n";
				int hombres;
				std::cin>>hombres;
				m.setHombres(hombres);
				std::cout<<BIYELLOW<<"Escribe el numero de mujeres: "<<"\n";
				int mujeres;
				std::cin>>mujeres;
				m.setMujeres(mujeres);

					provincia.insertarMunicipio(m);
					std::cout<<BIGREEN<<"Municipio insertado"<<"\n";
			}
		}	

	return;
}

  


void ed::borrarMunicipioDeProvincia(ed::Provincia &provincia)
{
	std::string nMunicipio;

	if((provincia.getNombre()=="") || (provincia.getNumeroMunicipios()==0))
	{
		std::cout<<BIRED<<"No hay provincia o no hay municipios"<<"\n";
	}
	else
	{
		std::cout<<"Escribe el nombre del municipio a borrar"<<"\n";
		std::getline(std::cin,nMunicipio);

			if(provincia.existeMunicipio(nMunicipio)==true)
			{
				provincia.borrarMunicipio(nMunicipio);
				std::cout<<BIGREEN<<"Municipio borrado"<<"\n";
			}
			else
			{
				std::cout<<BIRED<<"El municipio a borrar no existe"<<"\n";
			}
	}

	return;
}




