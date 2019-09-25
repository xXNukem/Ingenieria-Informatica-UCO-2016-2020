/*!
   \file  auxiliares.cpp
   \brief Fichero que contiene las funciones auxiliares para lanzar los algoritmos
*/


#include "auxiliares.hpp"

int menu()
{
	int opcion, posicion;

	// Se muestran las opciones del menú
	posicion = 2;

	// Se borra la pantalla
	std::cout << CLEAR_SCREEN;

	PLACE(posicion++, 10);
	std::cout << BIBLUE;
	std::cout << "Programa principal | Opciones del menú   ";
	std::cout << RESET;

	posicion++;
	PLACE(posicion++, 10);
	std::cout << "[1] Algoritmo del cambio " << std::endl;

	PLACE(posicion++, 10);
	std::cout << "[2] Algoritmo de la mochila " << std::endl;

	posicion++;
	PLACE(posicion++, 20);
	std::cout << BIYELLOW;
	std::cout << "Opción: ";
	std::cout << RESET;
	std::cin >> opcion;

	std::cin.ignore();

	return opcion;
}

void ejecutarOperacion(int opcion)
{

	Mochila m;
	if (opcion == 1) //Algoritmo del cambio
	{
		SistemaMonetario s;
		float cambio;

		s.setDinero();
		s.mostrarSistemaMonetario();
		cout << BIBLUE << "INTRODUCE LOS EUROS --> " << BIYELLOW;
		cin >> cambio;
		cambio = cambio * 100;
		std::vector<Dinero> aux;
		aux = s.getDinero();
		algoritmoCambio(aux, (int)cambio);

		getchar();
	}
	if (opcion == 2) //Algoritmo de la mochila
	{

		Mochila m;
		int volumenMochila;
		cout << BIBLUE << "Introduce el volumen de la mochila -->" << BIYELLOW;
		cin >> volumenMochila;
		cout << RESET << endl;
		m.getMateriales().clear();
		m.setMateriales();
		m.mostrarMateriales(m.getMateriales());
		std::vector<Materiales> aux;
		aux = m.getMateriales();
		algoritmoMochila(m.getMateriales().size(), volumenMochila, aux);
		//m.recuentoMateriales(aux, volumenMochila);
		getchar();
	}
}

