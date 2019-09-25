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

#define ITER	100
#define NHILOS	2

int main()
{
    pthread_t hilos[NHILOS];
    int status, i, v[NHILOS];
    extern double counter;
    double *r_value;
    void *Proceso1(void *);
    void *Proceso2(void *);

	P1QuiereEntrar=FALSE;
	P2QuiereEntrar=FALSE;

    // Create NHILOS threads
    /*for (i = 0; i < NHILOS; i++) {
	v[i] = i;
	if ((status = pthread_create(&hilos[i], NULL, Proceso1, (void *) &v[i])))
	    exit(status);
    }*/
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

/*void *adder(void *p)
{
    double l, *to_return;
    extern double counter;
    int *id, i;

    id = (int *) p;

	//SC
    for (i = 0; i < ITER; i++) {
	l = counter;
	fprintf(stdout, "Hilo %d: %f\n", *id, counter);
	l++;
	counter = l;
    }
	//SC

    to_return = malloc(sizeof(double));

    *to_return = counter;

    pthread_exit((void *) to_return);
}*/

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
		while(P2QuiereEntrar)
		{

			if(TurnoProceso==SEGUNDO)
			{

				P1QuiereEntrar=FALSE;
				while(TurnoProceso==SEGUNDO);
				P1QuiereEntrar=TRUE;

			}
		}

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

		//Salida sección crítica

		TurnoProceso=SEGUNDO;
		P1QuiereEntrar=FALSE;

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
		while(P1QuiereEntrar)
		{

			if(TurnoProceso==PRIMERO)
			{

				P2QuiereEntrar=FALSE;
				while(TurnoProceso==PRIMERO);
				P2QuiereEntrar=TRUE;

			}
		}

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

		//Salida sección crítica

		TurnoProceso=PRIMERO;
		P2QuiereEntrar=FALSE;

		pthread_exit((void *) to_return);
			
	}
}
