/******* Ejercicio3 *******/
/* Descripcion:

Analizador léxico que reconozca u psudocodigo

*/


/*** Zona de las declaraciones o definiciones ***/
%{

	/*VARIABLES GLOBALES*/
#include <stdlib.h>
#include <string.h>
#include "ejercicio3.h"


	
%}
/***** Expresiones regulares *****/
espacio		[ \t\n]
espacios	{espacio}+
digito		[0-9]
letra		[a-zA-Z]
caracter	{letra}|{digito}

identificador	{letra}{caracter}*([\_]?{caracter}+)*
identificadorIncorrecto1	 (([\_]+{caracter}*)|({caracter}+[\_]+{caracter}*))

numero	{digito}+(\.{digito}+)?(E[+\-]?{digito}+)?

suma	[\+]
resta	[\-]
producto	[\*]
division	[\/]


%x ESTADO_CADENA
%x ESTADO_COMENTARIO
%x ESTADO_COMENTARIOSIMPLE

/***** Zona de las reglas *****/
%%
{espacios}   { /* no se hace nada */ ; } 

(?:inicio)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,inicio);}
(?:fin)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,fin);}
(?:leer)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,leer);}
(?:escribir)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,escribir);}
(?:si)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,si);}
(?:entonces)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,entonces);}
(?:si_no)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,si_no);}
(?:fin_si)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,fin_si);}
(?:mientras)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,mientras);}
(?:hacer)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,hacer);}
(?:fin_mientras)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,fin_mientras);}
(?:hasta_que)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,hasta_que);}
(?:para)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,para);}
(?:desde)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,desde);}
(?:hasta)	{printf("Palabra reservada %s TOKEN: %d \n",yytext,hasta);}
(?:paso)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,paso);}
(?:fin_para)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,fin_para);}
(?:repetir)	{printf(" Palabra reservada %s TOKEN: %d \n",yytext,repetir);}

{identificador}	{printf(" Identificador: %s TOKEN: %d \n ",yytext,identificador);}

{suma}	{printf(" Operador suma %s TOKEN: %d \n",yytext,suma);}
{resta}	{printf(" Operador resta %s TOKEN: %d \n",yytext,resta);}
{producto}	{printf(" Operador producto %s TOKEN: %d \n",yytext,producto);}
{division}	{printf(" Operador division %s TOKEN: %d \n",yytext,division);}
"__mod" {printf(" Operador modulo: %s  TOKEN: %d \n", yytext, modulo);}
"**"	{printf(" Operador potencia: %s  TOKEN: %d \n", yytext, potencia);}
"||"	{printf(" Operador concatenacion %s TOKEN: %d \n",yytext, potencia);}

">"	{printf(" Oeprador mayor que %s TOKEN: %d \n",yytext,mayorque );}
"<"	{printf(" Operador menor que %s TOKEN: %d \n",yytext,menorque );}
">="	{printf(" Operador mayor o igual que %s TOKEN: %d \n",yytext,mayorigualque );}
"<="	{printf(" Operador menor o igual que %s TOKEN: %d \n",yytext,menorigualque );}
"=="	{printf(" Operador igual %s TOKEN: %d \n",yytext,igual );}
"<>"	{printf(" Operador distinto %s TOKEN: %d \n",yytext,distinto );}

".o."	{printf(" Operador disyuncion %s TOKEN: %d \n",yytext,disyuncion );}
".y."	{printf(" Operador conjuncion %s TOKEN: %d \n",yytext,conjuncion );}
".no."	{printf(" Operador negacion %s TOKEN: %d \n",yytext, negacion );}

";"	{printf(" Fin de sentencia ; %s TOKEN: %d \n",yytext,finsentencia );}
"("	{printf(" Parentesis izquierdo %s TOKEN: %d \n",yytext,parentesisizquierdo );}
")"	{printf(" Parentesis derecho %s TOKEN: %d \n",yytext,parentesisderecho );}

{numero}	{printf(" Numero: %s TOKEN: %d \n",yytext,numero);}

"'"	{
	/* Se activa el reconocimiento de la cadena */
	BEGIN ESTADO_CADENA; 
	}
<ESTADO_CADENA>"'"  { /* Fin de la cadena: se vuelve al estado por defecto */
			         BEGIN 0; 
			         yytext[yyleng-1]='\0';
					 printf("\t Cadena reconocida = %s TOKEN: %d \n",yytext,cadena);
					}      
<ESTADO_CADENA>"\\\'"     {yymore();}
<ESTADO_CADENA>.          {yymore();}
<ESTADO_CADENA>\n         {yymore();}

"(*"	{
	/* Se activa el reconocimiento de comentario*/
	BEGIN ESTADO_COMENTARIO; 
	}
<ESTADO_COMENTARIO>"*)"  { /* Fin de la cadena: se vuelve al estado por defecto */
			         BEGIN 0; 
			         yytext[yyleng-2]='\0';
					 printf("\t Comentario reconocido = %s TOKEN: %d \n",yytext,comentario);
					}      
<ESTADO_COMENTARIO>"\\\'"     {yymore();}
<ESTADO_COMENTARIO>.          {yymore();}
<ESTADO_COMENTARIO>\n         {yymore();}

"#"	{
	/* Se activa el reconocimiento de comentario*/
	BEGIN ESTADO_COMENTARIOSIMPLE; 
	}
<ESTADO_COMENTARIOSIMPLE>"\n"  { /* Fin de la cadena: se vuelve al estado por defecto */
			         BEGIN 0; 
			         yytext[yyleng-1]='\0';
					 printf("\t Comentario simple reconocido = %s TOKEN: %d \n",yytext,comentariosimple);
					}      
<ESTADO_COMENTARIOSIMPLE>"\\\'"     {yymore();}
<ESTADO_COMENTARIOSIMPLE>.          {yymore();}


{identificadorIncorrecto1}	{printf(" Identificador incorrecto %s\n",yytext);}
.	{printf("Carácter no reconocido: %c\n",yytext[0]);}

%%


/*** Zona de funciones auxiliares ***/

extern FILE *yyin, *yyout;
int  main(int argc, char *argv[])
{

	if(argc==2)
	{
		yyin=fopen(argv[1],"r");
	}
	else
	{
		printf("Se requiere un fichero de pseudocodigo por argumento \n");
		return 0;
	}

	yylex();
	fclose(yyin);

	return 0;
}

