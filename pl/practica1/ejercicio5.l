/******* Ejercicio5 *******/
/* Descripcion:

Cifrado de vigenere

*/


/*** Zona de las declaraciones o definiciones ***/
%{

	/*VARIABLES GLOBALES*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

char abc[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char ABC[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

char clave[256];
char cifrado[256];

int contador=0;
int i,j;
int k=0;

int pos1;
int pos2;
int nuevaPos;
int flagMayusY=0;
int flagMayusC=0;
int flag;
%}
/***** Expresiones regulares *****/
espacio		[ \t\n]
espacios	{espacio}+
caracter	[a-zA-Z]
palabra		{caracter}+
digito		[0-9]
numeros		{digito}+
fin   		[\n]


/***** Zona de las reglas *****/
%%
{fin}	{k=0; printf(" \n");}
{espacios}	{printf(" ");}
{numeros}	{	;}
{palabra}	{

	if(flag==0)
	{
		for(i=0;i<strlen(yytext);i++)
		{
			if(isupper(yytext[i]))
			{
				char nuevoC=tolower(yytext[i]);
				yytext[i]=nuevoC;
				flagMayusC=1;
			}

			for(j=0;j<strlen(abc);j++)
			{
				if(abc[j]==yytext[i])
				{
					pos1=j;
				}
			}

			if(isupper(clave[k]))
			{
				char nuevoC=tolower(clave[k]);
				clave[k]=nuevoC;
				flagMayusY=1;
			}

			for(j=0;j<strlen(abc);j++)
			{
				if(abc[j]==clave[k])
				{
					pos2=j;	
				}
			}

			nuevaPos=pos1+pos2;
			if(nuevaPos<=strlen(abc))
			{
				if(flagMayusC==1)
				{
					char mC=toupper(abc[nuevaPos]);
					printf("%c",mC);
				}
				else
				{
					printf("%c",abc[nuevaPos]);
				}
				
			}
			else
			{

				if(flagMayusC==1)
				{
					int resto=nuevaPos%strlen(abc);
					char mC=toupper(abc[resto]);
					printf("%c",mC);
				}
				else
				{
					int resto=nuevaPos%strlen(abc);
					printf("%c",abc[resto]);
				}
				
			}
			flagMayusC=0;
			if(k<strlen(clave))
			{
				k++;
			}
			else
			{
				k=0;
			}
		}
	}
	else if(flag==1)
	{
		for(i=0;i<strlen(yytext);i++)
		{
			if(isupper(yytext[i]))
			{
				char nuevoC=tolower(yytext[i]);
				yytext[i]=nuevoC;
				flagMayusC=1;
			}

			for(j=0;j<strlen(abc);j++)
			{
				if(abc[j]==yytext[i])
				{
					pos1=j;
				}
			}

			if(isupper(clave[k]))
			{
				char nuevoC=tolower(clave[k]);
				clave[k]=nuevoC;
				flagMayusY=1;
			}

			for(j=0;j<strlen(abc);j++)
			{
				if(abc[j]==clave[k])
				{
					pos2=j;

				}
			}

			nuevaPos=pos1-pos2;
			if(nuevaPos<0)
			{
				if(flagMayusC==1)
				{
					nuevaPos=strlen(abc)-fabs(nuevaPos);
					char nuevoC=toupper(abc[nuevaPos]);
					printf("%c",nuevoC);

				}
				else
				{
					nuevaPos=strlen(abc)-fabs(nuevaPos);
					printf("%c",abc[nuevaPos]);
				}

			}
			else
			{

				if(flagMayusC==1)
				{
					char nuevoC=toupper(abc[nuevaPos]);
					printf("%c",nuevoC);

				}
				else
				{
					printf("%c",abc[nuevaPos]);
				}
			}

			flagMayusC=0;
			if(k<strlen(clave))
			{
				k++;
			}
			else
			{
				k=0;
			}
		}
	}
}


%%


/*** Zona de funciones auxiliares ***/

extern FILE *yyin, *yyout;
int  main(int argc, char *argv[])
{

	if(argc==3)
	{
		strcpy(clave,argv[1]);
		if(strcmp(argv[2],"d")==0)
		{
			flag=1;
		}
		else if(strcmp(argv[2],"c")==0)
		{
			flag=0;
		}
	}
	else
	{
		printf("1 Argumento->Clave, 2 Argumento-> 'c' Cifrar 'd' Descifrar \n");
		return 0;
	}
	yylex();
	return 0;
}