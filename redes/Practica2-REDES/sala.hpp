#ifndef _SALA_HPP_
#define _SALA_HPP_
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
#include <algorithm>
#include <arpa/inet.h>
#include "usuario.hpp"
#include <boost/algorithm/string.hpp>
//#include "macros.hpp"
using namespace std;

class sala
{
private:
	usuario _user1;
	usuario _user2;
	int _capacidad;
	string _mPublica[10][10];
	string _mPOculta[10][10];

public:
	sala()
	{
		srand(time(NULL));
		int numBombas = 20;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				_mPublica[i][j] = "-";
				_mPOculta[i][j] = "0";
			}
		}
		for (int i = 0; i < numBombas; i++) {
			int x = rand() % 10;
			int y = rand() % 10;
			if (_mPOculta[x][y] == "*") {
				numBombas++;
			} else {
				_mPOculta[x][y] = "*";
			}

		}
	};
	inline void setJugador1(usuario user) {_user1 = user;}
	inline usuario getJugador1()const {return _user1;}

	inline void setJugador2(usuario user) {_user2 = user;}
	inline usuario getJugador2()const {return _user2;}

	inline void setCapacidad(int num) {if (_capacidad < 2) _capacidad = num;}
	inline int getCapacidad()const {return _capacidad;}

	int contarBombas(int f, int c);
	int comprobarDerrota(int i, int j, string bandera);

	void buscarMinas(int fila, int col);
	string printMatriz(int opt);
	void descubrirTablero();
	void ponerBandera(int fila, int col, string bandera);

	bool comprobarBanderas(string bandera);
	bool comprobarCasillas(int fila, int col);
};
#endif