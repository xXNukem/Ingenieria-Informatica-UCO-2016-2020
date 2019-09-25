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
	_d.clear();
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

void SistemaMonetario::setTablaDinero(int cambio)
{
	int filas = _d.size();
	int columnas = cambio;

	_tabla = std::vector<std::vector<int> >(filas + 1, std::vector< int >(columnas + 1));

	//Ponemos la primera fila y columna de la tabla a full de ceros
	for (int i = 0; i < filas; i++)
	{
		_tabla[i][0] = 0;
	}
	for (int i = 0; i < columnas; i++)
	{
		_tabla[0][1] = 0;
	}

	for (int i = 1; i <= filas; i++)
	{
		for (int j = 1; j <= columnas; j++)
		{
			if (i == 1 && j < _d[i - 1].getValor())
			{
				_tabla[i][j] = INT_MAX;
			}
			else
			{
				if (i == 1)
				{
					_tabla[i][j] = 1 + _tabla[i][j - _d[0].getValor()];
				}
				else if (j < _d[i - 1].getValor())
				{
					_tabla[i][j] = _tabla[i - 1][j];
				}
				else
				{
					_tabla[i][j] = min(_tabla[i - 1][j], 1 + _tabla[i][j - _d[i - 1].getValor()]);
				}
			}
		}
	}

//mostrarTablaDinero(filas, columnas);
	//obtenerSolucion();

}

void SistemaMonetario::mostrarTablaDinero(int filas, int columnas)
{
	for (int i = 0; i <= filas; i++)
	{
		for (int j = 0; j <= columnas; j++)
		{
			cout << BIBLUE << "[" << BIYELLOW << _tabla[i][j] << BIBLUE << "]" << "\t" << RESET;
		}
		cout << RESET << endl;
	}
}

void SistemaMonetario::obtenerSolucion()
{
	int i = _d.size();
	int j = _cambio;
	int c = _cambio;
	cout << BIGREEN << "CAMBIO UTILIZADO: " << RESET << endl;

	do {
		if (_tabla[i][j] != _tabla[i - 1][j])
		{
			_d[i - 1].setCantidadUsada(_d[i - 1].getCantidadUsada() + 1);
			c = c - _d[i - 1].getValor();
			j -= j - c;
		}
		else
		{
			i--;
		}
	} while (i > 0 && j > 0);

	for (int i = 0; i < _d.size(); i++)
	{
		if (_d[i].getCantidadUsada() > 0)
		{
			cout << BIYELLOW << "Cantidad: " << BIBLUE << _d[i].getCantidadUsada() << RESET << endl;
			cout << BIYELLOW << "VALOR: " << BIBLUE << (float)_d[i].getValor() / 100 << "\t" << BIYELLOW <<
			     " TIPO: "
			     <<
			     BIBLUE << _d[i].getTipo() << RESET << endl;

			cout << endl;
		}
	}
}

