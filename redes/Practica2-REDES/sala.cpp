#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "usuario.hpp"
#include "sala.hpp"


int sala::contarBombas(int f, int c)
{
	int bomba = 0;

	for (int i = f - 1; i < f + 2; i++) {
		for (int j = c - 1; j < c + 2; j++) {
			if (i >= 0 && i < 10 && j >= 0 && j < 10) {
				if (_mPOculta[i][j] == "*") {
					bomba++;
				}
			}
		}
	}
	return bomba;
}

int sala::comprobarDerrota(int i, int j, string bandera)
{
	/*
		Pierde = 0
		Gana = 1
		Continua = 2
	*/
	int c = 0;

	if (_mPOculta[i][j] == "*") {
		descubrirTablero();
		//printMatriz(0);
		//El jugador pierde
		return 0;
	} else {
		for (int v = 0; v < 10; v++) {
			for (int k = 0; k < 10; k++) {
				if (_mPOculta[v][k] == "0") {
					c++;
				}
			}
		}



		if (c == 1) {
			if (_mPOculta[i][j] == "0") {
				//cout << "HAS GANADO!!!" << endl;
				descubrirTablero();
				return 1;
			} else if (_mPOculta[i][j] == "*") {
				descubrirTablero();
				//printMatriz(0);
				return 0;
			}

		}

	}
	return 2;
}

void sala::buscarMinas(int fila, int col)
{

	int bombas = 0;
	if (fila >= 0 && fila < 10 && col >= 0 && col < 10) {
		bombas = contarBombas(fila, col);

		char str[10] ;
		sprintf(str , "%d" , bombas);

		if (bombas > 0) {
			_mPOculta[fila][col] = str;
			_mPublica[fila][col] = str;

		} else {

			for (int i = fila - 1; i < fila + 2; i++) {
				for (int j = col - 1; j < col + 2; j++) {
					if (i >= 0 && i < 10 && j >= 0 && j < 10) {
						if (_mPOculta[i][j] != "J" && _mPOculta[i][j] == "0") {

							_mPOculta[i][j] = "J";
							_mPublica[i][j] = "0";
							buscarMinas(i, j);
						}

					}
				}
			}
		}

	}
}
string sala::printMatriz(int opt)
{
	string cadena, aux;
	if (opt == 0) {
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				if (j == 9) {
					cadena += _mPublica[i][j];
					cadena += "; ";
				} else {
					cadena += _mPublica[i][j];
					cadena += ",";
				}
			}
		}
	} else {
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				cout << _mPOculta[i][j] << " - ";
			}
			cout << endl;
		}
	}
	return cadena;
}
void sala::descubrirTablero()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (_mPOculta[i][j] == "*") {
				_mPublica[i][j] = "*";
			}
		}
	}
}

void sala::ponerBandera(int fila, int col, string bandera)
{
	if (_mPublica[fila][col] == "-")
	{
		_mPublica[fila][col] = bandera;
	}
	else if (_mPublica[fila][col] == "A" || _mPublica[fila][col] == "B")
	{
		_mPublica[fila][col] = "AB";
	}
}

bool sala::comprobarBanderas(string bandera)
{
	int b = 0;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if ((_mPublica[i][j] == bandera || _mPublica[i][j] == "AB") && _mPOculta[i][j] == "*")
			{
				b++;
			}
		}
	}

	if (b == 10)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool sala::comprobarCasillas(int fila, int col)
{
	if (_mPublica[fila][col].compare("-") == 0 || _mPublica[fila][col].compare("A") == 0
	        || _mPublica[fila][col].compare("B") == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}