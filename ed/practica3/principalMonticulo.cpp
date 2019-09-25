/*!
 \mainpage Implementación de un montículo de mediciones
 \author   Carlos de la Barrera Perez
 \date     2018-3-7
 \version  1.0
*/


/*!

	\file principalMonticulo.cpp
	\brief Programa principal de la practica 3 de Estructuras de Datos
*/

#include <iostream>

#include <string>

#include "funcionesAuxiliares.hpp"

#include "MonticuloMediciones.hpp"
#include "Medicion.hpp"

#include "macros.hpp"

/*! 
		\brief   Programa principal de la práctica 2: montículo de mediciones
		\return  int
*/
int main(int argc, char *argv[])
{
	

	int opcion;
	ed::MonticuloMediciones monticulo;


	do{
		// Se elige la opción del menún
		opcion = ed::menu();		
		bool correcto;
		std::cout << CLEAR_SCREEN;
		PLACE(3,1);

		// Se ejecuta la opción del menú elegida
		switch(opcion)
		{
			case 0:
			{ 
					std::cout << INVERSE;
					std::cout << "Fin del programa" << std::endl;
					std::cout << RESET;
			}
			break;

		   ///////////////////////////////////////////////////////////////////

			case 1: 
			{
					std::cout <<BIYELLOW<< "[1] Introduce fichero de monticulo:" << RESET<<std::endl;
					std::string nombreFicheroEntrada;
					std::getline(std::cin,nombreFicheroEntrada);
					correcto=ed::cargarMonticuloDeFichero(nombreFicheroEntrada,monticulo);
					if(correcto==true)
					{
						std::cout<<BIGREEN<<"Exito al cargar el fichero"<<RESET<<"\n";
					}
					else
					{
						std::cout<<BIRED<<"Error al cargar el fichero"<<RESET<<"\n";
					}
					break;
			}

			//////////////////////////////////////////////////////////////////////////////
			case 2: 
			{
					std::cout <<BIYELLOW<< "[2] Introduce el nombre del fichero a guardar:" <<RESET<< std::endl;
					std::string nombreFicheroSalida;
					std::getline(std::cin,nombreFicheroSalida);
					if(nombreFicheroSalida.size()==0 || nombreFicheroSalida==" ")
					{
						std::cout<<BIYELLOW<<"Asignando nombre por defecto al fichero: Guardado.txt"<<RESET<<"\n";
						nombreFicheroSalida="guardado.txt";
					}
					ed::grabarMonticuloEnFichero(nombreFicheroSalida,monticulo);
				break;
			}
				
			case 3: 
			{
					std::cout <<BIYELLOW<< "[3] Datos del monticulo:" <<RESET<< std::endl;
					ed::datosMonticulo(monticulo);
					break;
			}

			//////////////////////////////////////////////////////////////////////////////
			case 4: 
			{
				  	std::cout <<BIYELLOW<< "[4] Monticulo ordenado: " <<RESET<< std::endl; 
					monticulo.print();
					break;
			}

			case 5: 
			{
				  	std::cout << "[5] Escribe la fecha y la precipitacion " << std::endl; 
					ed::insertarPrecipitacion(monticulo);
					break;
			}

			//////////////////////////////////////////////////////////////////////////////
			case 6: 
			{
					std::cout << "[6] Arbol generado en HTML" << std::endl;
				  	ed::generarArbolGrafico(monticulo);
					break;

			}
			case 7:
			{
					std::cout << "[7] Arbol generado en HTML" << std::endl;
				  	ed::generarArbolGrafico2(monticulo);
					break;
			}
			case 8: 
			{
					std::cout << "[8] Vaciar monticulo" << std::endl;
				 	ed::vaciarMonticulo(monticulo);
					break;
			}
			//////////////////////////////////////////////////////////////////////////////
			case 9: 
			{
					std::cout << "[9] Escribe el numero de mediciones a borrar" << std::endl;
			    	ed::borrarMediciones(monticulo);
					break;
			}

			case 10: 
			{
					std::cout << "[10] Escribe la fecha a buscar:" << std::endl;
			    	ed::buscarFecha(monticulo);
					break;
			}
		
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


