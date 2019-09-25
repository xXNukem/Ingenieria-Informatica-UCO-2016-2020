/*! 
   \file  combinatoria.cpp
   \brief Fichero que contiene las funciones de la clase combinatoria
*/

#include "combinatoria.hpp"

void Combinatoria::leerDatos()
{
	int valorMinimo,valorMaximo,incremento,repeticion;

	std::cout<<BIYELLOW<<"Introduce los valores para el experimento: "<<std::endl;
	std::cout<<BIBLUE<<"Minimo de N--> "<<BIGREEN;
	std::cin>>valorMinimo;
	setNMin(valorMinimo);
	std::cout<<BIBLUE<<"Maximo de N--> "<<BIGREEN;
	std::cin>>valorMaximo;
	setNMax(valorMaximo);
	std::cout<<BIBLUE<<"Numero de repeticiones--> "<<BIGREEN;
	std::cin>>repeticion;
	setRepeticiones(repeticion);
}

double Combinatoria::combinatoriaRecursiva(int n, int k)
{
       if(k==0 || n==k)
       {
       	return 1;
       }
       else
       {
       	return ((combinatoriaRecursiva(n-1,k-1))+(combinatoriaRecursiva(n-1,k)));
       }
}

double Combinatoria::combinatoriaTablaValores(int n, int k, std::vector<double> & _tablaValores)
{
	double resultado;

		if(k==0 || n==k)
       {
       	return 1;
       }
       else
       {
       		resultado=busquedaTablaValores(_tablaValores,n,k);
       		if(resultado==0)
       		{
	       		resultado=((combinatoriaTablaValores(n-1,k-1,_tablaValores))+(combinatoriaTablaValores(n-1,k,_tablaValores)));
	       		_tablaValores.push_back(n);
	       		_tablaValores.push_back(k);
	       		_tablaValores.push_back(resultado);

	       		return resultado;
	       	}
	       	else
	       	{
	       		return resultado;
	       	}
       }
}

double Combinatoria::busquedaTablaValores(std::vector<double> & v, int n, int k)
{
	for(int i=0;i<v.size();i=i+3)
	{
		if(v[i]==n && v[i+1]==k)
		{
			return v[i+2];
		}
	}
	return 0;
}

double Combinatoria::combinatoriaNoRecursiva(int n, int k)
{
	double resultado=calcularFactorial(n)/(calcularFactorial(k)*calcularFactorial(n-k));
	return resultado;
}

double Combinatoria::calcularFactorial(int x)
{
	double f=1,i;

		for(i=2;i<=x;i++)
		{
		  f=f*i;
		}
		return f;
}