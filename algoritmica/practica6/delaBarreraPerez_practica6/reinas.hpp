#ifndef _REINAS_HPP_
#define _REINAS_HPP_
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <vector>
#include <unistd.h>
#include "macros.hpp"

using namespace std;

class Reinas
{
private:
	std::vector<std::vector<int> > _soluciones;
	int _n;

public:

	inline int getN() {return _n;};

	inline void setN(int x) { _n = x;};

	bool verificarLugar(int k, std::vector<int> &c);

	void nReinasBackTracking(int n);

	void nReinasBackTrackingMOD(int n);

	void nReinasLasVegas(int n, bool & exito);

	void mostrarSolucion();

};



#endif