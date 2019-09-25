/******* Ejercicio1 *******/
/* Descripcion:

 Recibe un numero N y el nombre de un fichero compuesto por numeros enteros
 Devuelve un fichero con los enteros que no sean multiplos de N
*/


/*** Zona de las declaraciones o definiciones ***/
%{

	/*VARIABLES GLOBALES*/
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

char usuario[256];
char fecha[256]="No especificada";
char usuarioEnc[256];
char fechaEnc[256];
int contador;
int x;
	
%}
/***** Expresiones regulares *****/
espacio		[ \t\n]
espacios	{espacio}+
digito		[0-9]
letra		[a-zA-Z]
caracter	{letra}|{digito}

usuario 	{caracter}+[\@]{caracter}+
documento	{caracter}+[\.]txt
hora	{digito}{2}[\:]{digito}{2}
fecha	{digito}{2}[\/]{digito}{2}[\/]{digito}{4}


%x ESTADO_COMPROBAR
/***** Zona de las reglas *****/
%%



{usuario}	{
	if(strcmp(usuario,yytext)==0)
	{
		BEGIN ESTADO_COMPROBAR;
		strcpy(usuarioEnc,yytext);
	}
}

<ESTADO_COMPROBAR>{documento}	{

}

<ESTADO_COMPROBAR>{fecha}	{
	BEGIN 0;
	strcpy(fechaEnc,yytext);
	if(x==1)
	{
		if(strcmp(usuarioEnc, usuario)==0 && strcmp(fechaEnc, fecha)==0)
		{
			contador++;
		}
	}
	else if(x==0)
	{
		if(strcmp(usuarioEnc, usuario)==0)
		{
			contador++;
		}
	}
}


.	;
%%


/*** Zona de funciones auxiliares ***/

extern FILE *yyin, *yyout;
int  main(int argc, char *argv[])
{

	if(argc>=3)
	{
		yyin=fopen(argv[1],"r");
		if(argv[2])
		{
			strcpy(usuario,argv[2]);
			x=0;
		}
		if(argv[3])
		{
			strcpy(fecha,argv[3]);
			x=1;
		}
		
	}
	else
	{
		printf("Se deben pasar los argumentos 1-Fichero, 2-Usuario, 3-Fecha \n");
	}
	
	yylex();
	fclose(yyin);
	printf("El usuario %s en la fecha %s ha imprimido %d \n",usuario,fecha,contador);
	return 0;
}

