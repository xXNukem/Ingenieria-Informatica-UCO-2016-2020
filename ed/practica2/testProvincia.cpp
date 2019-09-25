/*!

	\file testProvincia.cpp
	\brief Segundo programa de prueba de la práctica 2 de ED: provincia de municipios
	\author 
	\date 
	\version 1.0
*/

// Para los flujos de entrada y salida y para usar locale
#include <iostream>


#include <string>

#include "Provincia.hpp"
#include "Municipio.hpp"

#include "macros.hpp"



/*! 
	\brief   Programa principal de la práctica 1: provincia y municipios
	\return  int
*/
int main()
{

// SE DEBEN QUITAR LOS COMENTARIOS CUANDO SE HAYAN CODIFICADO LAS FUNCIONES DE LA CLASE Provincia

	ed::Provincia provincia;
	ed::Municipio municipio;

	std::cout << "Se insertan los municipios" << std::endl;

    std::cout << "Insertar Cabra" << std::endl;
	municipio.setNombre("Cabra");
	provincia.insertarMunicipio(municipio);
    std::cout << std::endl;

	provincia.escribirMunicipios();

    std::cout << "Insertar Baena" << std::endl;
	municipio.setNombre("Baena");
	provincia.insertarMunicipio(municipio);
    std::cout << std::endl;

	provincia.escribirMunicipios();

	std::cout << "Se borra un municipio para controlar otro caso: Baena" << std::endl;
	provincia.borrarMunicipio("Baena");
    std::cout << std::endl;

provincia.escribirMunicipios();

    std::cout << "Insertar Luque" << std::endl;
	municipio.setNombre("Luque");
	provincia.insertarMunicipio(municipio);
    std::cout << std::endl;

	provincia.escribirMunicipios();

    std::cout << "Insertar Bujalance" << std::endl;
	municipio.setNombre("Bujalance");
	provincia.insertarMunicipio(municipio);
    std::cout << std::endl;

	provincia.escribirMunicipios();

    std::cout << "Insertar Zuheros" << std::endl;
	municipio.setNombre("Zuheros");
	provincia.insertarMunicipio(municipio);
    std::cout << std::endl;

	provincia.escribirMunicipios();

    std::cout << "Insertar Santa Eufemia" << std::endl;
	municipio.setNombre("Santa Eufemia");
	provincia.insertarMunicipio(municipio);
    std::cout << std::endl;

	provincia.escribirMunicipios();

    std::cout << "Insertar Montilla" << std::endl;
	municipio.setNombre("Montilla");
	provincia.insertarMunicipio(municipio);
    std::cout << std::endl;

	std::cout << "##############################" << std::endl << std::endl<< std::endl;

	std::cout << "Se borran los municipios" << std::endl<< std::endl;

    std::cout << "Borrar Luque" << std::endl;
	provincia.borrarMunicipio("Luque");
    std::cout << std::endl;

	provincia.escribirMunicipios();

    std::cout << "Borrar Zuheros" << std::endl;
	provincia.borrarMunicipio("Zuheros");
    std::cout << std::endl;

	provincia.escribirMunicipios();

    std::cout << "Borrar Bujalance" << std::endl;
	provincia.borrarMunicipio("Bujalance");
    std::cout << std::endl;

	provincia.escribirMunicipios();

    std::cout << "Borrar Montilla" << std::endl;
	provincia.borrarMunicipio("Montilla");
    std::cout << std::endl;

	provincia.escribirMunicipios();

    std::cout << "Borrar Santa Eufemia" << std::endl;
	provincia.borrarMunicipio("Santa Eufemia");
    std::cout << std::endl;

	provincia.escribirMunicipios();

    std::cout << "Borrar Cabra" << std::endl;
	provincia.borrarMunicipio("Cabra");
    std::cout << std::endl;

	provincia.escribirMunicipios();

	return 0;
}


