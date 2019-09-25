/*** ejemplo4.l ***/

/*** Zona de las declaraciones o definiciones ***/
%{
   /* Descripción
       El analizador léxico reconoce las palabras y las almacena en una tabla.

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
\n	{ estado = BUSCAR; } /* Fin de línea: vuelve al estado por defecto */

^verbo	{ estado = VERBO; }
^adj	{ estado = ADJETIVO; }
^adv	{ estado = ADVERBIO; }
^nombre	{ estado = NOMBRE; }
^prep	{ estado = PREPOSICION; }
^pron	{ estado = PRONOMBRE; }
^conj	{ estado = CONJUNCION; }

[a-zA-Z]+  {
			/* palabra normal: la define o la busca */
			if(estado != BUSCAR)
			{
			    /* define la palabra actual */
			 	poner_palabra(estado, yytext);
			}
			else
			{
				switch(buscar_palabra(yytext))
				{
					case VERBO: printf("%s: verbo\n", yytext); break;
					case ADJETIVO: printf("%s: adjetivo\n", yytext); break;
					case ADVERBIO: printf("%s: adverbio\n", yytext); break;
					case NOMBRE: printf("%s: nombre\n", yytext); break;
					case PREPOSICION: printf("%s: preposición\n", yytext); break;
					case PRONOMBRE: printf("%s: pronombre\n", yytext); break;
					case CONJUNCION: printf("%s: conjunción\n", yytext); break;
					default:
						printf("%s:  no reconocida \n", yytext);
						break;
				}
			}
          }

.    ; 	/* Se ignora el resto de cadenas */

%%

/* Se define el tipo de lista enlazada de palabras y tipos */
struct Ficha_palabra {
	char *palabra_nombre;
	int palabra_tipo;
	struct Ficha_palabra  *siguiente;
};

/* Se declara lista_palabra como una variable global que contendra
   las palabras que se declaren */
static struct Ficha_palabra  *lista_palabra;

extern void *malloc();

int main()
{
	yylex();

	return 0;
}

/******************************************************/

int poner_palabra(int tipo, char *palabra)
{
	struct Ficha_palabra  *p;

	if(buscar_palabra(palabra) != BUSCAR)
	{
		printf("---> : la palabra %s ya está definida\n", palabra);
		return 0;
	}

	/* Se introduce la palabra en la lista de palabras*/

	p = (struct Ficha_palabra  *) malloc(sizeof(struct Ficha_palabra ));

	p->siguiente = lista_palabra;
	p->palabra_nombre = (char *) malloc(strlen(palabra)+1);
	strcpy(p->palabra_nombre, palabra);
	p->palabra_tipo = tipo;
	lista_palabra = p;
	return 1;	/* palabra definida */
}

int buscar_palabra(char *palabra)
{
	struct Ficha_palabra  *p = lista_palabra;

	/* se busca la palabra recorriendo la lista simple */
	for(; p; p = p->siguiente)
	{
		if(strcmp(p->palabra_nombre, palabra) == 0)
			return p->palabra_tipo;
	}

	return BUSCAR;	/* no encontrada */
}
