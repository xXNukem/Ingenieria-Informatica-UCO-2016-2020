#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

double contador = 0;

typedef unsigned char BOOLEAN;
typedef enum {
    PRIMERO, SEGUNDO
} TURNO;
#define TRUE 	1
#define FALSE 	0

BOOLEAN QuiereEntrar[2];
TURNO ProcesoFavorecido;

#define ITER	100


main()
{
    pthread_t hilos[2];
    int status, i, v[2];
    extern double contador;
    void *sumador(void *);
    pthread_attr_t atributos;
    extern BOOLEAN QuiereEntrar[2];
    extern TURNO ProcesoFavorecido;

    /* Ejecuta 2 hilos. */
    /* Fija la concurrencia inicial. */
    /*thr_setconcurrency (3); */
    pthread_attr_init(&atributos);

    QuiereEntrar[0] = QuiereEntrar[1] = FALSE;
    ProcesoFavorecido = PRIMERO;

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
    extern BOOLEAN QuiereEntrar[2];
    extern TURNO ProcesoFavorecido;

    id = (int *) p;

    for (i = 0; i < ITER; i++) {
	QuiereEntrar[*id] = TRUE;
	while (QuiereEntrar[(*id + 1) % 2])
	    if (ProcesoFavorecido == (*id + 1) % 2) {
		QuiereEntrar[*id] = FALSE;
		while (ProcesoFavorecido == (*id + 1) % 2);
		QuiereEntrar[*id] = TRUE;
	    }
	/* Inicio seccion critica. */
	l = contador;
	fprintf(stdout, "Hilo %d: %f\n", *id, contador);
	l += x;
	contador = l;
	/* Fin seccion critica. */

	ProcesoFavorecido = (*id + 1) % 2;
	QuiereEntrar[*id] = FALSE;
    }

    pthread_exit(NULL);
}
