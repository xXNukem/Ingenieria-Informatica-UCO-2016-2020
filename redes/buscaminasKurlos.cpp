#include <cstdlib>
#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <time.h>
//#include "unistd.h"
#include "macros.hpp"

using namespace std;

string jugadas[10][10];
string ocultas[10][10];

void rellenarMatriz()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			jugadas[i][j] = " - ";
			ocultas[i][j] = " 0 ";
		}
	}

	ocultas[0][3] = " * ";
	ocultas[0][9] = " * ";

	ocultas[1][0] = " * ";
	ocultas[1][1] = " * ";

	ocultas[2][5] = " * ";
	ocultas[2][0] = " * ";

	ocultas[3][0] = " * ";
	ocultas[3][8] = " * ";
	ocultas[3][9] = " * ";

	ocultas[4][3] = " * ";

	ocultas[5][5] = " * ";

	ocultas[6][7] = " * ";

	ocultas[8][0] = " * ";
	ocultas[8][2] = " * ";
	ocultas[8][3] = " * ";
	ocultas[8][5] = " * ";
	ocultas[8][9] = " * ";

	ocultas[9][3] = " * ";
}

void printMatriz(string m[10][10])
{
	cout << "     0  1  2  3  4  5  6  7  8  9" << endl;
	cout << "    -----------------------------" << endl;
	for (int i = 0; i < 10; ++i)
	{
		cout << "[" << i << "] ";
		for (int j = 0; j < 10; ++j)
		{
			cout << m[i][j];
		}
		cout << endl;
	}
}
int contarBombas(int f, int c)
{
	int bomba = 0;

	for (int i = f - 1; i < f + 2; i++)
	{
		for (int j = c - 1; j < c + 2; j++)
		{
			if (i >= 0 && i < 10 && j >= 0 && j < 10)
			{
				if (ocultas[i][j] == " * ")
				{
					bomba++;
				}
			}
		}
	}
	return bomba;
}

bool comprobarDerrota(int i, int j)
{
	if (ocultas[i][j] == " * ")
	{
		return true;
	}
	else
	{
		return false;
	}
}

void buscarMinas(int fila, int col)
{

	int bombas = 0;
	if (fila >= 0 && fila < 10 && col >= 0 && col < 10)
	{
		bombas = contarBombas(fila, col);

		char str[10] ;
		sprintf(str , " %d " , bombas);

		if (bombas > 0)
		{
			ocultas[fila][col] = str;
			jugadas[fila][col] = str;

		}
		else
		{

			for (int i = fila - 1; i < fila + 2; i++)
			{
				for (int j = col - 1; j < col + 2; j++)
				{
					if (i >= 0 && i < 10 && j >= 0 && j < 10)
					{
						if (ocultas[i][j] != " J " && ocultas[i][j] == " 0 ")
						{

							ocultas[i][j] = " J ";
							jugadas[i][j] = " 0 ";
							buscarMinas(i, j);


						}

					}
				}
			}
		}

	}


}


int main(int argc, char const *argv[])
{
	rellenarMatriz();
	printMatriz(ocultas);
	bool result = false;
	int fila, col;
	while (result == false) {
		cout << "Inserta la fila " << endl;
		cin >> fila;
		cout << "Inserta la columna " << endl;
		cin >> col;
		result = comprobarDerrota(fila, col);
		if (result == true)
		{
			cout << "ADIOS" << endl;
			break;
		}
		buscarMinas(fila, col);
		printMatriz(jugadas);
		printMatriz(ocultas);
	}

	return 0;
}