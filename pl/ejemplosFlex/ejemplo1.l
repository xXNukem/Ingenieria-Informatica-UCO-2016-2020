/*** ejemplo1.l ***/

/*** Zona de las declaraciones o definiciones ***/
%{
   /* Descripción
    	El analizador léxico 
            - convierte la letras mayúsculas en minúsculas,
            - elimina blancos al final de la línea 
            - y sustituye una serie de blancos por uno solo.
   */
%}

/***** Zona de las reglas *****/
%%
[A-Z]		putchar(yytext[0]+'a'-'A');
"À"			printf("á");
"É"			printf("é");
"Í"			printf("í");
"Ó"			printf("ó");
"Ú"			printf("ú");
[ ]+$       ;
[ ]+		putchar(' ');
%%

/*** Zona de funciones auxiliares ***/

/*** No hay funciones auxiliares ***/
