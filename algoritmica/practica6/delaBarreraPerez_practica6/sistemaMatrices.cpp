/*!
   \file  estadistica.cpp
   \brief Fichero que contiene las funciones de matrices
*/
#include "sistemaMatrices.hpp"

double SistemaMatrices::sumatorio(std::vector<double> n, std::vector<double> t_practico, int a,
                                  int b)
{
	double resultado = 0;

	for (int i = 0; i < (int)n.size(); i++)
	{
		resultado += (pow(n[i], a)) * (pow(t_practico[i], b));
	}

	return resultado;
}

void SistemaMatrices::setSistema(std::vector<double> n, std::vector<double> t_practico, int nFil,
                                 int nCol)
{
	//Reserva de memoria para las matrizes
	_matrizCoeficientes = std::vector<std::vector<double> >(nFil, std::vector< double >(nCol));
	_matrizIndependientes = std::vector<std::vector<double> >(nFil, std::vector< double >(1));
	_matrizSoluciones = std::vector<std::vector<double> >(nFil, std::vector< double >(1));


	for (int i = 0; i < nFil; i++)
	{
		for (int j = 0; j < nCol; j++)
		{
			_matrizCoeficientes[i][j] = sumatorio(n, t_practico, i + j, 0);
		}
	}

	for (int i = 0; i < nFil; i++)
	{
		_matrizIndependientes[i][0] = sumatorio(n, t_practico, i, 1);
	}
}

void SistemaMatrices::mostrarMatriz(std::vector<std::vector<double> > m)
{
	for (int i = 0; i <= 1; i++)
	{
		for (int j = 0; j <= 1; j++)
		{
			std::cout << " " << m[i][j] << " ";
		}
		std::cout << std::endl;
	}
}