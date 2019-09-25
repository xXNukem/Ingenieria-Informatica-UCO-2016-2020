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
	std::cout << "[1] Suma de dos enteros grandes " << std::endl;

	PLACE(posicion++, 10);
	std::cout << "[2] Producto de dos enteros grandes " << std::endl;

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

	Entero e1;
	Entero e2;
	string resultado = "";
	int ceros = 0;
	int ndigitos = 0;

	if (opcion == 1)
	{
		cout << BIGREEN << "INTRODUCE LOS NUMEROS A SUMAR " << RESET << endl;

		cout << BIBLUE << "Introduce el entero 1 --> " << BIYELLOW << endl;
		cin >> e1;
		cout << BIBLUE << "Introduce el entero 2 --> " << BIYELLOW << endl;
		cin >> e2;
//-------Comprobamos el tamaño de los numeros para igualarlos
		string n1 = e1.getNumero();
		string n2 = e2.getNumero();

		ndigitos = obtenerTam(e1, e2);

		ceros = ndigitos - e1.getNumero().size();
		agregarCerosDelante(n1, ceros);


		ceros = ndigitos - e2.getNumero().size();
		agregarCerosDelante(n2, ceros);

		if (n2.size() % 2 != 0 || n1.size() % 2 != 0)
		{
			agregarCerosDelante(n1, 1);
			agregarCerosDelante(n2, 1);
		}

		e2.setNumero(n2);
		e1.setNumero(n1);
//---------------
		resultado = e1 + e2;
		cout << endl;
//volvemos a quitar los ceros que metimos para mostrarlos bien
		quitarCerosNoSignificativos(n1);
		quitarCerosNoSignificativos(n2);

		cout << BIYELLOW << n1 << endl;
		cout << BIBLUE << "+" << endl;
		cout << BIYELLOW << n2 << endl;

		cout << BIBLUE <<
		     "-----------------------------------------------------------------------------------" <<
		     RESET << endl;
		cout << BIGREEN << resultado << RESET << endl;

		getchar();

	}
	if (opcion == 2)
	{
		cout << BIGREEN << "INTRODUCE LOS NUMEROS A MULTIPLICAR" << endl;

		cout << BIBLUE << "Introduce el entero 1 --> " << BIYELLOW << endl;
		cin >> e1;
		cout << BIBLUE << "Introduce el entero 2 --> " << BIYELLOW << endl;
		cin >> e2;
//--------Comprobamos el tamaño de los numeros para igualarlos
		string n1 = e1.getNumero();
		string n2 = e2.getNumero();

		ndigitos = obtenerTam(e1, e2);

		ceros = ndigitos - e1.getNumero().size();
		agregarCerosDelante(n1, ceros);


		ceros = ndigitos - e2.getNumero().size();
		agregarCerosDelante(n2, ceros);

		if (n2.size() % 2 != 0 || n1.size() % 2 != 0)
		{
			agregarCerosDelante(n1, 1);
			agregarCerosDelante(n2, 1);
		}

		e2.setNumero(n2);
		e1.setNumero(n1);
//-----------------------------------------------------
		resultado = e1 * e2;

//Quitamos los ceros que metimos para nivelar los numeros y asi mostrarlos bonitos
		quitarCerosNoSignificativos(n1);
		quitarCerosNoSignificativos(n2);

		cout << BIYELLOW << n1  << endl;
		cout << BIBLUE << "X" << endl;
		cout << BIYELLOW << n2 << endl;

		cout << BIBLUE <<
		     "-----------------------------------------------------------------------------------" <<
		     RESET << endl;
		cout << BIGREEN << resultado << RESET << endl;

		getchar();

	}

}

int obtenerTam(Entero e1, Entero e2)
{
	if (e1.getNumero().size() > e2.getNumero().size())
	{
		return e1.getNumero().size();
	}
	else
	{
		return e2.getNumero().size();
	}
}