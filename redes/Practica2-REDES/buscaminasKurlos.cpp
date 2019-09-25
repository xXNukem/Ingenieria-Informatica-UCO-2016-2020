#include <cstdlib>
#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <time.h>
//#include "unistd.h"
#include "macros.hpp"

using namespace std;

string _mPublica[10][10];
string _mPOculta[10][10];

void rellenarMatriz()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			_mPublica[i][j] = " - ";
			_mPOculta[i][j] = " 0 ";
		}
	}

	_mPOculta[0][3] = " * ";
	_mPOculta[0][9] = " * ";

	_mPOculta[1][0] = " * ";
	_mPOculta[1][1] = " * ";

	_mPOculta[2][5] = " * ";
	_mPOculta[2][0] = " * ";

	_mPOculta[3][0] = " * ";
	_mPOculta[3][8] = " * ";
	_mPOculta[3][9] = " * ";

	_mPOculta[4][3] = " * ";

	_mPOculta[5][5] = " * ";

	_mPOculta[6][7] = " * ";

	_mPOculta[8][0] = " * ";
	_mPOculta[8][2] = " * ";
	_mPOculta[8][3] = " * ";
	_mPOculta[8][5] = " * ";
	_mPOculta[8][9] = " * ";

	_mPOculta[9][3] = " * ";
}

void printMatriz(string m[10][10])
{
	cout << "     0  1  2  3  4  5  6  7  8  9" << endl;
	cout << "    -----------------------------" << endl;
	for (int i = 0; i < 10; ++i) {
		cout << "[" << i << "] ";
		for (int j = 0; j < 10; ++j) {
			cout << m[i][j];
		}
		cout << endl;
	}
}
int contarBombas(int f, int c)
{
	int bomba = 0;

	for (int i = f - 1; i < f + 2; i++) {
		for (int j = c - 1; j < c + 2; j++) {
			if (i >= 0 && i < 10 && j >= 0 && j < 10) {
				if (_mPOculta[i][j] == " * ") {
					bomba++;
				}
			}
		}
	}
	return bomba;
}

bool comprobarDerrota(int i, int j)
{
	if (_mPOculta[i][j] == " * ") {
		return true;
	} else {
		return false;
	}
}

void buscarMinas(int fila, int col)
{

	int bombas = 0;
	if (fila >= 0 && fila < 10 && col >= 0 && col < 10) {
		bombas = contarBombas(fila, col);

		char str[10] ;
		sprintf(str , " %d " , bombas);

		if (bombas > 0) {
			_mPOculta[fila][col] = str;
			_mPublica[fila][col] = str;

		} else {

			for (int i = fila - 1; i < fila + 2; i++) {
				for (int j = col - 1; j < col + 2; j++) {
					if (i >= 0 && i < 10 && j >= 0 && j < 10) {
						if (_mPOculta[i][j] != " J " && _mPOculta[i][j] == " 0 ") {

							_mPOculta[i][j] = " J ";
							_mPublica[i][j] = " 0 ";
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
	printMatriz(_mPOculta);
	bool result = false;
	int fila, col;
	while (result == false) {
		/*cout << "Inserta la fila " << endl;
		cin >> fila;
		cout << "Inserta la columna " << endl;
		cin >> col;*/
		result = comprobarDerrota(fila, col);
		if (result == true) {
			cout << "ADIOS" << endl;
			break;
		}
		buscarMinas(fila, col);
		printMatriz(_mPublica);
		printMatriz(_mPOculta);
	}

	return 0;
}