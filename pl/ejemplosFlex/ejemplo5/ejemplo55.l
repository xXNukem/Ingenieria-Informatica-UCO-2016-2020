/**************************** ejemplo55.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:

      * El analizador lexico reconoce elementos de un lenguaje de programacion
      * Permite leer desde un fichero y escribir la salida en otro fichero

   */
#include <stdio.h>
#include "ejemplo5.h"   /* declaracion de los componentes lexicos o tokens */
%}
/* Definiciones regulares */

espacio		[ \t\n]
espacios	{espacio}+
letra		[a-zA-Z]
digito		[0-9]
identificador	{letra}({letra}|{digito})*
numero		{digito}+(\.{digito}+)?(E[+\-]?{digito}+)?


/***** Zona de las reglas *****/
%%
{espacios}   { /* no se hace nada */ ; }

if 	     {fprintf(yyout,"\n Palabra reservada: %s --> token %d\n", yytext,IF);}

then         {fprintf(yyout,"\n Palabra reservada: %s --> token %d\n", yytext,THEN);}

else	     {fprintf(yyout,"\n Palabra reservada: %s --> token %d\n", yytext,ELSE);}

{identificador}	{fprintf(yyout,"\n Identificador: %s --> token %d\n", yytext, ID);}

{numero}     {fprintf(yyout,"\n Numero: %s --> token %d\n", yytext,NUMERO);}

">"          {fprintf(yyout,"\n Operador relacional: %s --> token %d\n",
			 yytext,MAYOR_QUE);}
">=" 	     {fprintf(yyout,"\n Operador relacional: %s --> token %d\n",
			 yytext,MAYOR_IGUAL);}

^#            {fprintf(yyout,"\n Fin del programa \n"); return 0;}

.            { ECHO; /* Se muestra por pantalla, pero no se indica nada */ }
%%


/***** Zona de funciones auxiliares *****/

extern FILE *yyin, *yyout;

int main(int argc, char *argv[])
{
 
 switch(argc)
  {
   case 2:  yyin=fopen(argv[1],"r"); 
            break;
   case 3:  yyin=fopen(argv[1],"r"); 
            yyout=fopen(argv[2],"w"); 
  }
  yylex();

  return 0;
}
