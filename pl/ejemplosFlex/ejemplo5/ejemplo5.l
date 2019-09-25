/**************************** ejemplo5.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:

      * El analizador léxico reconoce algunos componentes léxicos de un lenguaje de programación

   */

/* Fichero que contiene la declaracion de los componentes lexicos o tokens */
#include "ejemplo5.h"   
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

if 	        {printf("\n Palabra reservada: %s --> token %d\n", yytext,IF);}

then            {printf("\n Palabra reservada: %s --> token %d\n", yytext,THEN);}

else	        {printf("\n Palabra reservada: %s --> token %d\n", yytext,ELSE);}

{identificador}	{printf("\n Identificador: %s --> token %d\n", yytext, ID);}

{numero}        {printf("\n Numero: %s --> token %d\n", yytext,NUMERO);}

">"             {printf("\n Operador relacional: %s --> token %d\n",
			 yytext,MAYOR_QUE);}
">=" 	        {printf("\n Operador relacional: %s --> token %d\n",
			 yytext,MAYOR_IGUAL);}

^#              {printf("\n Fin del programa \n"); return 0;}

.	        { ECHO; /* Se muestra por pantalla, pero no se indica nada */ }
%%


/***** Zona de funciones auxiliares *****/

