/*!
   \file  sistemaMonetario.cpp
   \brief Archivo cpp para la clase sistema monetario
*/
#include "sistemaMonetario.hpp"

void SistemaMonetario::mostrarSistemaMonetario()
{
	cout << BIGREEN << "SISTEMA MONETARIO LEIDO" << BIYELLOW << endl;

	for (int i = 0; i < _d.size(); i++)
	{
		cout << BIYELLOW << "VALOR: " << BIBLUE << (float)_d[i].getValor() / 100 << "\t" << BIYELLOW <<
		     " TIPO: "
		     <<
		     BIBLUE << _d[i].getTipo() << RESET << endl;
	}
}

void SistemaMonetario::setDinero()
{
	ifstream f("dinero.txt", ios::in);

	if (!f.good())
	{
		cout << "El fichero no existe\n" << endl;
	}
	else
	{
		int valor;
		string tipo;
		while (f >> valor >> tipo)
		{
			Dinero aux;

			aux.setValor(valor);
			aux.setTipo(tipo);

			_d.push_back(aux);
		}

	}

	f.close();

}

