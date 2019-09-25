/******* ejemplo0.l *******/

/*** Zona de las declaraciones o definiciones ***/
%{
   /* Descripcion:

	 El analizador léxico reproduce literalmente todo lo que se teclea
   */
%}

/***** Zona de las reglas *****/
%%
.|\n		ECHO; /* Equivalente a printf("%s",yytext); */
%%


/*** Zona de funciones auxiliares ***/

/*** No hay funciones auxiliares ***/
