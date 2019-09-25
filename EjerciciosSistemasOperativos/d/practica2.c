#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

double counter=0;

#define ITER	100
#define NHILOS	4
#define N
#define FALSE 0
#define TRUE 1

typedef unsigned char BOOLEAN;
BOOLEAN Elegido[N];
int ticket[N];

int main()
{
	extern BOOLEAN Elegido[N];
	extern int ticket [N];
	void *Proceso1 (void *),*Proceso2 (void *);
	pthread_t hilos[NHILOS];
	int status, i, v[NHILOS];
	extern double counter;
	double *r_value;

	// Lamport
	for (i=0; i<N; i++)
	{
		Elegido[i] = TRUE;
		ticket[i] = 0;
	}
	for (i=1; i<=N;i++)
	{
		if ((status = pthread_create(&hilos[0],NULL, Proceso1, (void *) &v[0])))
		{
		exit(status);
		}
	}
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
	double l, *to_return;
	extern double counter;
	int *id, i;

	id = (int *) p;

	while (TRUE) 
	{
		P1QuiereEntrar = TRUE;
		TurnoProceso = SEGUNDO;
		while (P2QuiereEntrar && TurnoProceso == SEGUNDO)
		{
			//Seccion critica
			for (i = 0; i < ITER; i++) {
				l = counter;
				fprintf(stdout, "Hilo %d: %f\n", *id, counter);
				l++;
				counter = l;
			}
			to_return = malloc(sizeof(double));
			*to_return = counter;
			//Salida seccion critica
			P1QuiereEntrar = FALSE;	
			pthread_exit((void *) to_return);
		}
	}
	
}	

void *Proceso2(void *p)
{
	extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
	extern TURNO TurnoProceso;
	double l, *to_return;
	extern double counter;
	int *id, i;

	id = (int *) p;

	while (TRUE) 
	{
		P2QuiereEntrar = TRUE;
		TurnoProceso = PRIMERO;
		while (P1QuiereEntrar && TurnoProceso = PRIMERO)
		{
			//Seccion critica
			for (i = 0; i < ITER; i++) {
				l = counter;
				fprintf(stdout, "Hilo %d: %f\n", *id, counter);
				l++;
				counter = l;
			}
			to_return = malloc(sizeof(double));
			*to_return = counter;
			//Salida seccion critica
			P2QuiereEntrar = FALSE;	
			pthread_exit((void *) to_return);
		}
	}
	
}
