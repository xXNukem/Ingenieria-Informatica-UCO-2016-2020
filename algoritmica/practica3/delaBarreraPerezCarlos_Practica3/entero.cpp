/*!
   \file  entero.cpp
   \brief Fichero con las funciones de la clase entero y sus operadores
*/

#include "entero.hpp"
#include <string>

//FUNCIONES DE OPERACIONES

string Entero::sumarNumero(string numero1, string numero2)
{
	int dimension; //DIMENSION
	int x, y, aux, aux2 = 0; //Variables necesarias para sumar

	int n1 = numero1.size();
	int n2 = numero2.size();
	if (n1 > n2)
	{
		agregarCerosDelante(numero2, n1 -
		                    n2); // Tenemos que contemplar el sobreflujo al final
		dimension = numero1.size();
	}
	else
	{
		agregarCerosDelante(numero1, n2 - n1);
		dimension = numero2.size();
	}

	string total = "";
	string total2 = "";
	for (int i = dimension - 1; i >= 0; i--)
	{
		x = numero1[i] - '0'; //Pasamos los digitos a entero
		y = numero2[i] - '0';

		aux = x + y +
		      aux2; //aux 2 controla valdra 1 cuando haya desbordamiento


		if (aux >= 10)
		{
			aux2 = 1;
			aux = aux % 10;
		}
		else
		{
			aux2 = 0;
		}

		total2 = '0' + aux;
		total.insert(0, total2);
		if (i == 0 and aux2 == 1)
		{
			total.insert(0, "1");
			quitarCerosNoSignificativos(total);
			return total;
		}


	}
	quitarCerosNoSignificativos(total);

	return total;
}

string Entero::multiplicaNumeros(string const &numero1, string const &numero2, int limite)
{
	//Tamaño del numero 1
	int n = numero1.size();


	int s;
	string w, x, y, z; //almacena digitos que quedan


	string final1, final2,
	       final3; //La operacion se divide en 3 finales

	//operación de multiplicación

	if (n <= limite)//Caso base
	{
		string total;
		int numeroInt1, numeroInt2, aux; //En aux pasamos el numero a cadena
		numeroInt1 = stoi(numero1);
		numeroInt2 = stoi(numero2);

		aux = numeroInt1 *
		      numeroInt2; //Los numeros se multiplican en el caso base, y luego se pasan a cadena
		total = to_string(aux);
		quitarCerosNoSignificativos(total);
		return total;
	}
	else
	{
		s = n / 2;
		partirCadena(numero1, w, x);
		partirCadena(numero2, y, z);

		//DIVISION DEL ALGORITMO EN 3 FINALES
		string aux1 = multiplicaNumeros(w, y, limite);

		final1 = multiplicarPotencia10(aux1, 2 * s);

		string aux2 = multiplicaNumeros(w, z, limite);
		string aux3 = multiplicaNumeros(x, y, limite);
		string aux4 = sumarNumero(aux2 , aux3);

		final2 = multiplicarPotencia10(aux4, s);
		final3 = multiplicaNumeros(x, z, limite);

		string aux5 = sumarNumero(final1, final2);

		return (sumarNumero(aux5, final3));

		//return total;
	}
}

//SOBRECARGA DE OPERADORES

ostream &operator<<(ostream &stream, Entero &e)
{
	stream << e.getNumero();

	return stream;
}

istream &operator>>(istream &stream, Entero &e)
{
	string aux;
	stream >> aux;
	e.setNumero(aux);

	return stream;
}

string Entero::operator+(Entero &e)
{
	string aux;
	string n1 = this->getNumero();
	string n2 = e.getNumero();
	aux = sumarNumero(n1, n2);

	return aux;
}

string Entero::operator*(Entero &e)
{
	int maxDigitos;
	string aux;
	string n1 = this->getNumero();
	string n2 = e.getNumero();

	cout << BIBLUE << "Introduce el máximo de digitos hasta la multiplicacion directa --> " <<
	     BIYELLOW;
	cin >> maxDigitos;
	cout << RESET << endl;

	aux = multiplicaNumeros(n1, n2, maxDigitos);

	return aux;
}