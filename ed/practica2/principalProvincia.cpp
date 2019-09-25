/*!

	\file principalProvincia.cpp
	\brief Programa principal de la práctica 2 de ED: provincia de municipios
	\author 
	\date 
	\version 1.0
*/

/*!
 \mainpage Implementación de una provincia utilizando una lista doblemente enlazada y ordenada de municipios
 \author   
 \date     
 \version  1.0
*/

// Para los flujos de entrada y salida y para usar locale
#include <iostream>


#include <string>

#include "Provincia.hpp"
#include "Municipio.hpp"

#include "funcionesAuxiliares.hpp"
#include "macros.hpp"



/*! 
	\brief   Programa principal de la práctica 1: provincia y municipios
	\return  int
*/
int main(){

	ed::Provincia provincia;

	int opcion;

	do{
		// Se elige la opción del menún
		opcion = ed::menu();		

		std::cout << CLEAR_SCREEN;
		PLACE(3,1);

		// Se ejecuta la opción del menú elegida
		switch(opcion)
		{
			case 0: 
					std::cout << INVERSE;
					std::cout << "Fin del programa" << std::endl;
					std::cout << RESET;
			break;

		   ///////////////////////////////////////////////////////////////////

			case 1: 
					std::cout << "[1] Comprobar si la provincia tiene municipios" << std::endl;
					ed::comprobarProvinciaVacia(provincia);
					break;

			//////////////////////////////////////////////////////////////////////////////
			case 2: 
					std::cout << "[2] Cargar la provincia desde un fichero" << std::endl;
					ed::cargarProvincia(provincia);
				break;

			case 3: 
					std::cout << "[3] Grabar la provincia en un fichero" << std::endl;
					ed::grabarProvincia(provincia);
					break;

			//////////////////////////////////////////////////////////////////////////////
			case 4: 
				  	std::cout << "[4] Consultar datos de la provincia: " << std::endl; 
					ed::consultarDatosDeProvincia(provincia);
					break;

			case 5: 
				  	std::cout << "[5] Mostrar municipios de la provincia: " << std::endl; 
					ed::mostrarMunicipiosDeProvincia(provincia);
					break;


			//////////////////////////////////////////////////////////////////////////////
			case 6: 
					std::cout << "[6] Modificar datos de la provincia: código o nombre" 
							  << std::endl;
				  	ed::modificarDatosDeProvincia(provincia);
					break;


			case 7: 
					std::cout << "[7] Borrar todos los municipios de una provincia" << std::endl;
				 	ed::borrarTodosLosMunicipiosDeProvincia(provincia);
					break;

			//////////////////////////////////////////////////////////////////////////////
			case 8: 
					std::cout << "[8] Consultar un municipio" << std::endl;
			    	ed::consultarMunicipioDeProvincia(provincia);
					break;

			case 9: 
					std::cout << "[9] Insertar un municipio" << std::endl;
				  	ed::insertarMunicipioEnProvincia(provincia);
					break;

			case 10: 
					std::cout << "[10] Borrar un municipio" << std::endl;
					ed::borrarMunicipioDeProvincia(provincia);
					break;

			//////////////////////////////////////////////////////////////////////////////
			default:
				std::cout << BIRED;
				std::cout << "Opción incorrecta ";
				std::cout << RESET;
				std::cout << "--> ";
			  	std::cout << ONIRED;
				std::cout << opcion << std::endl;
				std::cout << RESET;
     }
  
    if (opcion !=0)
    {
		PLACE(25,1);
		std::cout << "Pulse ";
		std::cout << BIGREEN;
		std::cout << "ENTER";
		std::cout << RESET;
		std::cout << " para mostrar el ";
		std::cout << INVERSE;
		std::cout << "menú"; 
		std::cout << RESET;

		// Pausa
		std::cin.ignore();

		std::cout << CLEAR_SCREEN;
    }
	  }while(opcion!=0);

	return 0;
}


