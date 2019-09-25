/**************************** ejemplo44.l ***********************************/

/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:
       El analizador lexico reconoce las palabras y las almacena en una tabla.
       Se utiliza un fichero auxiliar "p44.c" para codificar las funciones de la tabla
       
	Permite definir el tipo de cada palabra. 
        Por ejemplo, si se teclea al principio de la línea
            verbo amar luchar
        define las palabras "amar" y "luchar" como verbos
   */

enum {
	BUSCAR = 0, /* Estado por defecto. */
	VERBO,
	ADJETIVO,
	ADVERBIO,
	NOMBRE,
	PREPOSICION,
	PRONOMBRE,
	CONJUNCION
};

int estado; 

int poner_palabra(int tipo, char *palabra);
int buscar_palabra(char *palabra);
%}

%%
\n	{ estado = BUSCAR; } /* Fin de linea: vuelve al estado por defecto */

^verbo	{ estado = VERBO; }
^adj	{ estado = ADJETIVO; }
^adv	{ estado = ADVERBIO; }
^nombre	{ estado = NOMBRE; }
^prep	{ estado = PREPOSICION; }
^pron	{ estado = PRONOMBRE; }
^conj	{ estado = CONJUNCION; }

[a-zA-Z]+  {
		/* palabra normal: la define o la busca */
	     if(estado != BUSCAR) {
	        /* define la palabra actual */
	     	poner_palabra(estado, yytext);
	     } else {
		switch(buscar_palabra(yytext)) {
		case VERBO: printf("%s: verbo\n", yytext); break;
		case ADJETIVO: printf("%s: adjetivo\n", yytext); break;
		case ADVERBIO: printf("%s: adverbio\n", yytext); break;
		case NOMBRE: printf("%s: nombre\n", yytext); break;
		case PREPOSICION: printf("%s: preposicion\n", yytext); break;
		case PRONOMBRE: printf("%s: pronombre\n", yytext); break;
		case CONJUNCION: printf("%s: conjuncion\n", yytext); break;
		default:
			printf("%s:  no reconocida \n", yytext);
		}
            }
          }

.    ; 	/* Se ignora el resto de cadenas */ 

%%
