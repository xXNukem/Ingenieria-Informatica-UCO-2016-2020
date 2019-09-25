#include <stdio.h>
#include <string.h>

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
/* Se define el tipo de lista enlazada de palabras y tipos */
struct Ficha_palabra {
	char *palabra_nombre;
	int palabra_tipo;
	struct Ficha_palabra *siguiente;
};

/* Se declara lista_palabra como una variable global que contendra 
   las palabras que se declaren */
static struct Ficha_palabra *lista_palabra;

extern void *malloc();
int yylex();

int poner_palabra(int tipo, char *palabra);
int buscar_palabra(char *palabra);

int main()
{
	yylex();

	return 0;
}

/***************************************************************/

int poner_palabra(int tipo, char *palabra)
{
	struct Ficha_palabra *p;	

	if(buscar_palabra(palabra) != BUSCAR) {
		printf("---> : la palabra %s ya está definida\n", palabra);
		return 0;
	}
	
	/* Se introduce la palabra en la lista de palabras*/

	p = (struct Ficha_palabra *) malloc(sizeof(struct Ficha_palabra));

	p->siguiente = lista_palabra;
	p->palabra_nombre = (char *) malloc(strlen(palabra)+1);
	strcpy(p->palabra_nombre, palabra);
	p->palabra_tipo = tipo;
	lista_palabra = p;
	return 1;	/* palabra definida */
}

int buscar_palabra(char *palabra)
{
	struct Ficha_palabra *p = lista_palabra;

	/* se busca la palabra recorriendo la lista simple */
	for(; p; p = p->siguiente) {
		if(strcmp(p->palabra_nombre, palabra) == 0)
			return p->palabra_tipo;
	}

	return BUSCAR;	/* no encontrada */
}
