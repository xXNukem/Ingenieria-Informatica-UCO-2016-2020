/* Algoritmo de Lamport. */
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

double contador = 0;

#define ITER	1000
#define NHILOS	4

#define FALSE 0
#define TRUE  1

typedef unsigned char BOOLEAN;
BOOLEAN Choosing[NHILOS];
int Number[NHILOS];

int main()
{
    pthread_t hilos[NHILOS];
    int status, i, v[NHILOS];
    extern double contador;
    void *sumador(void *);
    extern BOOLEAN Choosing[NHILOS];
    extern int Number[NHILOS];
    pthread_attr_t atributos;

    /* Fija la concurrencia inicial. */
    /* thr_setconcurrency (NHILOS + 1); */
    pthread_attr_init(&atributos);

    /* Se inicializan las variables globales. */
    for (i = 0; i < NHILOS; i++) {
	Choosing[i] = FALSE;
	Number[i] = 0;
    }

    /* Ejecuta NHILOS hilos. */
    for (i = 0; i < NHILOS; i++) {
	v[i] = i;
	if (status =
	    pthread_create(&hilos[i], &atributos, sumador, (void *) &v[i]))
	    exit(status);
    }

    /* Espera a que finalicen. */
    for (i = 0; i < NHILOS; i++)
	pthread_join(hilos[i], NULL);

    /* Resultado final. */
    fprintf(stdout, "%f\n", contador);
}

void *sumador(void *p)
{
    double x = 1.0, l;
    extern double contador;
    int I, i, j, max;
    extern BOOLEAN Choosing[NHILOS];
    extern int Number[NHILOS];

    I = *(int *) p;

    for (i = 0; i < ITER; i++) {
	Choosing[I] = TRUE;
	/*  number[I] = max (number[0], number[1],..., number[N - 1]) + 1;
	 */
	max = Number[0];
	for (j = 0; j < NHILOS; j++)
	    if (Number[j] > max)
		max = Number[j];
	Number[I] = max + 1;
	Choosing[I] = FALSE;

	/* Espera su turno. */
	for (j = 0; j < NHILOS; j++) {
	    while (Choosing[j]);
	    while ((Number[j] != 0) &&
		   ((Number[j] < Number[I]) ||
		    (Number[j] == Number[I] && j < I)));
	}

	/* Inicio sección crítica. */
	l = contador;
	fprintf(stdout, "Hilo %d: %f\n", I, contador);
	l += x;
	contador = l;
	/* Fin seccion critica. */

	Number[I] = 0;
    }

    pthread_exit(NULL);
}
