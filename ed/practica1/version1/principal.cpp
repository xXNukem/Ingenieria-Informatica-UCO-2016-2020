/*!
 \mainpage Implementación de un vector libre de tres dimensiones
 \brief		\f$ \vec{v} = (v_1, v_2, v_3) = v_1 \vec{i} + v_2 \vec{j} + v_3 \vec{k} \f$
 \author   Carlos de la Barrera Perez
 \date     2018-1-23
 \version  1.0
*/

/*!

	\file principal.cpp
	\brief Programa principal de la practica 1 de ED: vectores libres de tres dimensiones
*/

#include <iostream>

#include "funcionesAuxiliares.hpp"

#include "Vector3D.hpp"

#include "macros.hpp"

/*! 
	\brief   Función principal de la práctica 1
	\return  int
*/
int main()
{

 // QUITAR LOS "COMENTARIOS DE BLOQUE" CUANDO SE HAYA CODIFICADO LA CLASE Vector3D



	// Uso del constructor parametrizado con valores
	ed::Vector3D u(1,2,3);

	// Uso del constructor de copia
	ed::Vector3D v(u);

	// Uso del constructor sin argumentos: vector (0,0,0)
	ed::Vector3D w;

	double k = 2;

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
				PLACE(25,1);
				std::cout << BRED;
				std::cout << "[0] Fin del programa" << std::endl << std::endl;
				std::cout << RESET;
			break;

			case 1: 
			   	std::cout << BIBLUE;
				std::cout << "[1] Leer vectores" << std::endl;
				std::cout << RESET;

// QUITAR EL COMENTARIOS CUANDO SE HAYA CODIFICADO LA CLASE Vector3D
				ed::leerVectores(u,v,w);

				break;

			case 2: 
			   	std::cout << BIBLUE;
				std::cout << "[2] Leer número escalar " << std::endl;
				std::cout << RESET;

// QUITAR EL COMENTARIOS CUANDO SE HAYA CODIFICADO LA CLASE Vector3D
				std::cout << "k = "; 
				std::cin >> k;

				break;


			case 3: 
			   	std::cout << BIBLUE;
				std::cout << "[3] Escribir número y vectores " << std::endl;
				std::cout << RESET;

// QUITAR EL COMENTARIOS CUANDO SE HAYA CODIFICADO LA CLASE Vector3D
				// Número escalar
				std::cout  << BIYELLOW << "k = " << RESET << k << std::endl;

				// Vectores
				ed::escribirVectores(u,v,w);

				break;


			case 4: 
			   	std::cout << BIBLUE;
				std::cout << "[4] Observadores de los vectores: módulos y ángulos " << std::endl;
				std::cout << RESET;

// QUITAR EL COMENTARIOS CUANDO SE HAYA CODIFICADO LA CLASE Vector3D
				ed::observadoresDeVectores(u,v);

				break;

			case 5: 
			   	std::cout << BIBLUE;
			  	std::cout << "[5] Modificación del vector \"u\" usando v y k " << std::endl; 
				std::cout << RESET;

// QUITAR EL COMENTARIOS CUANDO SE HAYA CODIFICADO LA CLASE Vector3D
				ed::modificarVector(u,v,k);

				break;

			case 6: 
			   	std::cout << BIBLUE;
				std::cout << "[6] Producto escalar de u y v " << std::endl;
				std::cout << RESET;

// QUITAR EL COMENTARIOS CUANDO SE HAYA CODIFICADO LA CLASE Vector3D
			ed::mostrarProductoEscalar(u,v);

				break;


			case 7: 
			   	std::cout << BIBLUE;
				std::cout << "[7] Producto vectorial de u y v " << std::endl;
				std::cout << RESET;

// QUITAR EL COMENTARIOS CUANDO SE HAYA CODIFICADO LA CLASE Vector3D
			ed::mostrarProductoVectorial(u,v);

				break;


			case 8: 
			   	std::cout << BIBLUE;
			  	std::cout << "[8] Producto mixto de tres vectores  u * (v ^ w) " << std::endl; 
				std::cout << RESET;

// QUITAR EL COMENTARIOS CUANDO SE HAYA CODIFICADO LA CLASE Vector3D
				ed::mostrarProductoMixto(u,v,w);

				break;

			case 9: 
			   	std::cout << BIBLUE;
				std::cout << "[9] Mostrar el uso de los operadores con u y v (se modifica w)" << std::endl;
				std::cout << RESET;

// QUITAR EL COMENTARIOS CUANDO SE HAYA CODIFICADO LA CLASE Vector3D
			ed::mostrarOperadores(u,v,w,k);

				break;

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
		std::cout << INVERSE ;
		std::cout << "ENTER";
		std::cout << RESET;
		std::cout << " para mostrar el ";
		std::cout << BIGREEN ;
		std::cout << "menú: "; 
		std::cout << RESET;
		// Pausa
		std::cin.ignore();

		std::cout << CLEAR_SCREEN;
    }
	  }while(opcion!=0);

	return 0;
}


