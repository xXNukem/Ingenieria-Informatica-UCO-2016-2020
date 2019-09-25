/******* Ejercicio2 *******/
/* Descripcion:

Reemplaza una palabra por otra en un fichero de entrada que recibe por argumento

*/


/*** Zona de las declaraciones o definiciones ***/
%{

	/*VARIABLES GLOBALES*/
#include <stdlib.h>
#include <string.h>
	char *palabra;
	char *nueva;
	int contador=0;

	
%}
/***** Expresiones regulares *****/
espacio		[ \t\n]
espacios	{espacio}+
caracter	[a-zA-Z]
palabra		{caracter}+


/***** Zona de las reglas *****/
%%
{palabra}	{
	if(strcmp(palabra,yytext)==0)
	{
		fprintf(yyout, "%s",nueva);
		contador++;
	}
	else
	{
		fprintf(yyout, "%s ", yytext);
	}

}

%%


/*** Zona de funciones auxiliares ***/

extern FILE *yyin, *yyout;
int  main(int argc, char *argv[])
{

	if (argc == 4)
	{
		palabra = argv[1];
		nueva=argv[2];
		yyin = fopen(argv[3], "r");
		if (yyin == NULL)
		{
			return 0;
		}
		yyout = fopen("salida.txt", "w");

	}
	else
	{
		printf(" Argumentos: 1-Palabra a sustituir 2-Palabra nueva 3-Fichero entrada \n");
	}

	yylex();
	fclose(yyin);
	fclose(yyout);
	rename("salida.txt", argv[3]);
	remove("salida.txt");
	printf("Se han sustituido %d palabras \n",contador);
	return 0;
}

