#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <math.h>

#include "funcionesbajonivel.hpp"

char * reservarCadena(int n)
{
	return new char [n];
}

void partirCadena(char *c, char* &c1, char* &c2)
{
	int n;
	int n1, n2;
	int i;
	
	n = strlen(c);
	
	if (n % 2 == 0) //n es par
	{
		n1 = n / 2;
		n2 = n1;
	}
	else
	{
		n1 = (n + 1) / 2;
		n2 = n1 - 1;
	}
	
	c1 = reservarCadena(n1 + 1); //Se reserva uno mas para el caracter fin de cadena
	c2 = reservarCadena(n2 + 1); //Se reserva uno mas para el caracter fin de cadena
	
	for(i = 0; i < n1; i++) //Se rellena la primera cadena
		c1[i] = c[i];
	c1[i] = '\0';
	
	for(i = n1; i < n; i++) //Se rellena la segunda cadena
		c2[i - n1] = c[i];
	c2[i - n1] = '\0';
}

void agregarCerosFinal(char* &c, int nCeros)
{
	int n, numeroCaracteres;
	char *nuevaCadena = NULL;
	int i;
	
	n = strlen(c);
	numeroCaracteres = n + nCeros;
	
	nuevaCadena = reservarCadena(numeroCaracteres + 1);
	
	for(i = 0; i < n; i++) //Se rellena la primera cadena
		nuevaCadena[i] = c[i];
	
	for(i = n; i < numeroCaracteres; i++) //Se rellena con los ceros al final
		nuevaCadena[i] = '0';
	nuevaCadena[i] = '\0';
	
	delete [] c; //Se libera la cadena antigua
	
	c = nuevaCadena;
}

void agregarCerosDelante(char* &c, int nCeros)
{
	int n, numeroCaracteres;
	char *nuevaCadena;
	int i;
	
	n = strlen(c);
	numeroCaracteres = n + nCeros;
	
	nuevaCadena = reservarCadena(numeroCaracteres + 1);
	
	for(i = 0; i < n; i++) //Se desplazan los caracteres iniciales para dejar espacio a los ceros
		nuevaCadena[i + nCeros] = c[i];
	nuevaCadena[i + nCeros] = '\0'; //Se cierra la cadena
	
	for(i = 0; i < nCeros; i++) //Se rellena con los ceros al principio
		nuevaCadena[i] = '0';
	
	delete []c; //Se libera la cadena antigua
	c = nuevaCadena;
}

void quitarCerosNoSignificativos(char* &c)
{
	char *aux;
	int l, i = 0;
	int numeroCeros = 0;
	
	l = strlen(c);
	//Contamos ceros no significativos
	while(c[i] == '0' && i < l)
	{
		i++;
		numeroCeros++;
	}

	//Reservamos nueva cadena
	aux = reservarCadena(l - numeroCeros + 1);
	
	//Copiamos la cadena sin los ceros no significativos
	for(i = numeroCeros; i < l; i++)
		aux[i - numeroCeros] = c[i];
	
	aux[l - numeroCeros] = '\0'; //Cerramos la cadena
	delete []c;
	c = aux;
}

char * multiplicarPotencia10(char *c, int potencia)
{
	char *aux;
	
	aux = reservarCadena(strlen(c) + 1);
	strcpy(aux, c);
	agregarCerosFinal(aux, potencia);
	return aux;
}
