/*** ejemplo2.l ***/

/*** Zona de las declaraciones o definiciones ***/
%{
   /*
      Descripción: el analizador léxico distingue entre verbos y no verbos
   */
%}

/***** Zona de las reglas *****/
%%

[\t ]+	;	/* Se ignoran los espacios en blanco */ 

es |
soy |
eres |
era |
ser |
siendo |
sido |
hacer |
hace |
hizo |
puede |
tiene |
tener |
ir			{ printf("%s: es un verbo\n", yytext); }

[a-zA-Z]+ 	{ printf("%s: no es un verbo\n", yytext); }

.|\n		{ ECHO; /* resto de cadenas */ }
%%


/*** Zona de funciones auxiliares ***/

int main()
{
	yylex();

	return 0;
}
