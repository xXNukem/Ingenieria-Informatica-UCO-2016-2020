#ifndef _MEDICIONMETODO_HPP_
#define _MEDICIONMETODO_HPP_
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include "macros.hpp"
#include "ClaseTiempo.cpp"
#include "sistemaEcuaciones.hpp"


struct datos
{
	int _tam;
	double _time;
	double _time_est;
};

class MedicionMetodo
{
	private:
		int _minElementos;
		int _maxElementos;
		int _incremento;
		int _repeticion;
		std::vector<int> v;
		std::vector<datos> _vectorDatos;
		std::vector<std::vector<double> > _matrizCoeficientes;
		std::vector<std::vector<double> > _matrizIndependientes;
		std::vector<std::vector<double> > _matrizSoluciones;



	public:

		void setMinElementos(int x);
		void setMaxElementos(int x);
		void setIncremento(int x);
		void setRepeticion(int x);

		int getMinElementos();
		int getMaxElementos();
		int getIncremento();
		int getRepeticion();

		void leerDatosMedicion();
		bool estaOrdenado(std::vector<int> &v);

		void setVector(std::vector<int> &v,int i);
		void getVector(std::vector<int> &v);

		void metodoInsercionBinaria();
		void ordenarInsercionBinaria(std::vector<int> &v,int i);

		void metodoMonticulo();
		void ordenarMonticulo(std::vector<int> &v,int pos);
		void shiftRight(std::vector<int> &v, int low, int high);
		void heapify(std::vector<int> &v, int low, int high);


		double sumatorio(std::vector<datos> &v,int a, int b);
		void generarMatriz(int nFil, int nCol);//segun el metodo donde se llame se le pasa un tamaño distinto
		void tiempoEstimado(std::vector<datos> &_vectorDatos,bool sofisticado,std::vector<std::vector<double> > _soluciones);
		double getCoeficienteDeterminacion(std::vector <datos>const &_vectorDatos);
		void mostrarSoluciones();
		void calcularDias(std::vector<std::vector<double> > _matrizSoluciones, bool sofisticado);

};

#endif