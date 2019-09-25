/* Algoritmo de Peterson. */
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

double contador = 0;

typedef unsigned char BOOLEAN;
typedef enum {
    PRIMERO, SEGUNDO
} TURNO;
#define TRUE 	1
#define FALSE 	0

BOOLEAN WishToEnter[2];
TURNO FavouredProcess;

#define ITER	1000


main()
{
    pthread_t hilos[2];
    int status, i, v[2];
    extern double contador;
    void *sumador(void *);
    pthread_attr_t atributos;
    extern BOOLEAN WishToEnter[2];
    extern TURNO FavouredProcess;

    WishToEnter[0] = WishToEnter[1] = FALSE;
    FavouredProcess = PRIMERO;

    /* Ejecuta 2 hilos. */
    /* Fija la concurrencia inicial. */
    /* thr_setconcurrency (3); */
    pthread_attr_init(&atributos);

    for (i = 0; i < 2; i++) {
	v[i] = i;
	if (status =
	    pthread_create(&hilos[i], &atributos, sumador, (void *)
			   &v[i]))
	    exit(status);
    }

    /* Espera a que finalicen. */
    for (i = 0; i < 2; i++)
	pthread_join(hilos[i], NULL);

    /* Resultado final. */
    fprintf(stdout, "%f\n", contador);
}

void *sumador(void *p)
{
    double x = 1.0, l;
    extern double contador;
    int *id, i;
    extern BOOLEAN WishToEnter[2];
    extern TURNO FavouredProcess;

    id = (int *) p;

    for (i = 0; i < ITER; i++) {
	WishToEnter[*id] = TRUE;
	FavouredProcess = (*id + 1) % 2;
	while (WishToEnter[(*id + 1) % 2]
	       && (FavouredProcess == (*id + 1) % 2));

	/* Inicio seccion critica. */
	l = contador;
	fprintf(stdout, "Hilo %d: %f\n", *id, contador);
	l += x;
	contador = l;
	/* Fin seccion critica. */

	WishToEnter[*id] = FALSE;
    }

    pthread_exit(NULL);
}
