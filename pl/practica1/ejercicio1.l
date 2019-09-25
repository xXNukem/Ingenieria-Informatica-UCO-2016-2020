/******* Ejercicio1 *******/
/* Descripcion:

 Recibe un numero N y el nombre de un fichero compuesto por numeros enteros
 Devuelve un fichero con los enteros que no sean multiplos de N
*/


/*** Zona de las declaraciones o definiciones ***/
%{

	/*VARIABLES GLOBALES*/
#include <stdlib.h>
	int n;

	
%}
/***** Expresiones regulares *****/

espacio		[ \t\n]
espacios	{espacio}+
digito		[0-9]
numeros		{digito}+
fin 		[numeros\n]

/***** Zona de las reglas *****/
%%

{numeros}	{
	if(atoi(yytext)%n!=0)
	{
		fprintf(yyout, "%s\t", yytext);
	}
}

{fin}	{
		fprintf(yyout, "\n");
}
{espacios}   { /* no se hace nada */ ; } 
%%


/*** Zona de funciones auxiliares ***/

extern FILE *yyin, *yyout;
int  main(int argc, char *argv[])
{

	if (argc == 4)
	{
		n = atoi(argv[1]);
		yyin = fopen(argv[2], "r");
		yyout = fopen(argv[3], "w");

		if(strcmp(argv[2],argv[3])==0)
		{
			printf("El fichero de entrada y de salida no pueden ser el mismo \n");
			return 0;
		}

		if (yyin == NULL)
		{
			printf("Fichero de entrada incorrecto \n");
			return 0;
		}

	}
	else
	{
		printf("Ficheros o argumentos incorrectos \n");
		printf("Argumentos: 1-Numero entero 2-Fichero de numeros enteros de entrada 3-Fichero de salida \n");
		return 0;
	}

	yylex();
	fclose(yyin);
	fclose(yyout);
	return 0;
}

