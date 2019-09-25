/*!
 \author   Nicolás Luis Fernández García
 \date     2018-3-7
 \version  1.0
*/


/*!

	\file pruebaMonticulo.cpp
	\brief Programa de prueba
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
	///PROGRAMA DE PRUEBA

	if (argc != 3)
	{
		std::cout << "Modo de ejecución" << std::endl;
		std::cout << argv[0] << "<fichero-de-mediciones>  <fichero-ordenado> "  << std::endl;

		return -1;
	}

	ed::MonticuloMediciones monticulo;

	std::string nombreFicheroEntrada(argv[1]);
	std::string nombreFicheroSalida(argv[2]);
	
	// 
	std::cout << "Se cargan las mediciones desde el fichero " << nombreFicheroEntrada << std::endl;
	std::cout << " Se crea un montículo de máximos " << std::endl;
	ed::cargarMonticuloDeFichero(nombreFicheroEntrada,monticulo);

	// QUITAR EL COMENTARIO CUANDO SE HAYA CODIFICADO LA FUNCIÓN 
	 std::cout << "Tamaño del montículo " << monticulo.size() << std::endl;
	 monticulo.print();
	// Se graba el montículo en el fichero: las mediciones son grabadas en orden descendente
	std::cout << "Se graba el montículo en el fichero " << nombreFicheroSalida << std::endl;
	std::cout << "Las mediciones son grabadas en orden descendente " << std::endl;

	ed::grabarMonticuloEnFichero(nombreFicheroSalida,monticulo);

  //
	return 0;


	///FIN DE PROGRAMA DE PRUEBA

}


