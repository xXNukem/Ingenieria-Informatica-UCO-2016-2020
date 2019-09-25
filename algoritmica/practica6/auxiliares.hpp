/*!
	\file auxiliares.hpp
	\brief fichero hpp para las funciones auxiliares
	\author Carlos de la Barrera Perez
*/

#ifndef _AUXILIARES_HPP_
#define _AUXILIARES_HPP_
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <vector>
#include <unistd.h>
#include "macros.hpp"
#include "reinas.hpp"
#include "estadistica.hpp"
#include "sistemaEcuaciones.hpp"
#include "sistemaMatrices.hpp"
#include "ClaseTiempo.cpp"
#include "estadistica.hpp"


using namespace std;



int menu();

void ejecutarOperacion(int opcion);

std::vector<double> calcularTiempoTeorico(std::vector<std::vector<double> > & _matrizSoluciones,
        std::vector<double> & n);

void grabarFichero(std::vector<double> const &n, std::vector<double> const &t_practico,
                   std::vector<double> const &t_teorico);

int calcularFactorial(int n);

#endif