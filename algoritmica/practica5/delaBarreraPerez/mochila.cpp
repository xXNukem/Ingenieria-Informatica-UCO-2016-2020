/*!
   \file  mochila.cpp
   \brief Archivo cpp para la clase mochila
*/
#include "mochila.hpp"


void Mochila::setMateriales()
{
	_m.clear();
	ifstream f("mochila.txt", ios::in);

	if (!f.good())
	{
		cout << "El fichero no existe\n" << endl;
	}
	else
	{
		int i = 0;
		int etiqueta, volumen, precio;

		while (f >> etiqueta >> volumen >> precio)
		{
			Materiales aux;
			aux.setID(etiqueta);
			aux.setVOL(volumen);
			aux.setPRE(precio);

			_m.push_back(aux);
		}

	}

	f.close();

}

void Mochila::mostrarMateriales()
{
	cout << BIGREEN << "MATERIALES LEIDOS" << RESET << endl;

	for (int i = 0; i < _m.size(); i++)
	{
		cout << BIBLUE << "ETIQUETA: " << BIYELLOW << _m[i].getID() << "\t" << BIBLUE
		     <<
		     " VOLUMEN: " << BIYELLOW
		     <<
		     _m[i].getVOL() << "\t" << BIBLUE << " PRECIO UNIDAD: " << BIYELLOW << _m[i].getPRE() << RESET <<
		     endl;
	}
}

void Mochila::setTablaMochila(int volumen)
{
	int filas = _m.size();
	int columnas = volumen;

	_tabla = std::vector<std::vector<int> >(filas + 1, std::vector< int >(columnas + 1));

	//Ponemos la primera fila y columna de la tabla a full de ceros
	for (int i = 0; i < filas; i++)
	{
		_tabla[i][0] = 0;
	}
	for (int i = 0; i < columnas; i++)
	{
		_tabla[0][i] = 0;
	}

	//Recorremos la matriz claculando los valores
	//Si un material no cabe en su totalidad no aparece en las filas de la matriz
	for (int i = 1; i < filas; i++)
	{
		for (int j = 1; j < columnas; j++)
		{
			if (j < _m[i].getVOL())
			{
				_tabla[i][j] = _tabla[i - 1][j];
			}
			else
			{
				int precio = _m[i].getPRE();
				int volumen = _m[i].getVOL();
				int a = _tabla[i - 1][j];
				int b = precio * volumen + _tabla[i - 1][j - volumen];
				_tabla[i][j] = max(a, b);
			}
		}
	}

	//mostrarTablaMochila(filas,columnas);

	//obtenerSolucion();
}

void Mochila::mostrarTablaMochila(int filas, int columnas)
{
	cout << BIGREEN << "Tabla de valores construida: " << RESET << endl;

	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			cout << BIBLUE << "[" << BIYELLOW << _tabla[i][j] << BIBLUE << "]" << "\t" << RESET;
		}
		cout << RESET << endl;
	}
}


void Mochila::obtenerSolucion()
{
	int i = _m.size() - 1;
	int j = _volumenMochila - 1;
	int volumenUtilizado = 0;

	cout << BIGREEN << "MATERIALES UTILIZADOS: " << RESET << endl;

	do {
		if (_tabla[i][j] != _tabla[i - 1][j] && _m[i].getUSADO() == "nada")
		{
			_m[i].setUSADO("Total");

			cout << BIBLUE << "ID Material --> " << BIYELLOW << _m[i].getID() << endl;
			cout << BIBLUE << "Volumen --> " << BIYELLOW << _m[i].getVOL() << endl;
			cout << BIBLUE << "Precio --> " << BIYELLOW << _m[i].getPRE() << endl;
			cout << BIBLUE << "Uitlizado --> " << BIYELLOW << _m[i].getUSADO() << endl;
			cout << RESET << endl;
			volumenUtilizado = volumenUtilizado + _m[i].getVOL();
			j = j - _m[i].getVOL();
		}
		else
		{
			i--;
		}
	} while (i > 0 && j > 0);

	//El coste total esta en la ultima posicion de la matriz
	cout << BIGREEN << "COSTE DE LA MOCHILA: " << BIYELLOW << _tabla[_m.size() - 1][_volumenMochila - 1]
	     << RESET << endl;
	cout << BIGREEN << "VOLUMEN UTILIZADO: " << BIYELLOW << volumenUtilizado << RESET << endl;

}