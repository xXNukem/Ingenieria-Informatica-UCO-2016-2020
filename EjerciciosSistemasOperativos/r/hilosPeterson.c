#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
typedef unsigned char BOOLEAN;
BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
typedef enum{

PRIMERO, SEGUNDO
}TURNO;
TURNO TurnoProceso;
double counter = 0;

#define ITER	10
#define NHILOS	2

int main()
{
    pthread_t hilos[NHILOS];
    int status, i, v[NHILOS];
    extern double counter;
    double *r_value;
    void *Proceso1(void *);
    void *Proceso2(void *);

	extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;

	P1QuiereEntrar=FALSE;
	P2QuiereEntrar=FALSE;

	TurnoProceso=PRIMERO;

	v[0] = 0;
	if ((status = pthread_create(&hilos[0], NULL, Proceso1, (void *) &v[0])))
	    exit(status);

	v[1]=1;
	if ((status = pthread_create(&hilos[1], NULL, Proceso2, (void *) &v[1])))
	    exit(status);
	

    // Wait threads
    for (i = 0; i < NHILOS; i++) {
	pthread_join(hilos[i], (void **) &r_value);
	printf("Value returned by %lu thread: %lf\n", hilos[i], *r_value);
    }

    // Final result
    fprintf(stdout, "%f\n", counter);

    return 0;
}

void *Proceso1(void *p)
{
	extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
	extern TURNO TurnoProceso;
	extern double counter;
	double l, *to_return;
	int i,*id;
	
	id=(int *)p;

	while(TRUE)
	{
		P1QuiereEntrar=TRUE;
		TurnoProceso=SEGUNDO;
		while(P2QuiereEntrar && TurnoProceso==SEGUNDO);

		//Entrada a sección crítica

		for (i = 0; i < ITER; i++) 
		{
			l = counter;
			fprintf(stdout, "Hilo %d: %f\n", *id, counter);
			l++;
			counter = l;
    		}

		to_return = malloc(sizeof(double));

    		*to_return = counter;

		P1QuiereEntrar=FALSE;

		//Salida sección crítica

		pthread_exit((void *) to_return);
			
	}
}

void *Proceso2(void *p)
{
	extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
	extern TURNO TurnoProceso;
	extern double counter;
	double l, *to_return;
	int i,*id;
	
	id=(int *)p;

	while(TRUE)
	{
		P2QuiereEntrar=TRUE;
		TurnoProceso=PRIMERO;
		while(P1QuiereEntrar && TurnoProceso==PRIMERO);

		//Entrada a sección crítica

		for (i = 0; i < ITER; i++) 
		{
			l = counter;
			fprintf(stdout, "Hilo %d: %f\n", *id, counter);
			l++;
			counter = l;
    		}

		to_return = malloc(sizeof(double));

    		*to_return = counter;

		P2QuiereEntrar=FALSE;

		//Salida sección crítica

		pthread_exit((void *) to_return);
			
	}
}
