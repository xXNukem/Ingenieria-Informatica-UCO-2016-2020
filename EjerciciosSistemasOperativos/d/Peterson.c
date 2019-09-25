#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

double counter=0;

#define ITER	5
#define NHILOS	2
#define FALSE 0
#define TRUE 1

typedef unsigned char BOOLEAN;
typedef enum{
    PRIMERO, SEGUNDO
} TURNO;
BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
TURNO TurnoProceso;

int main()
{
	extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
	void *Proceso1 (void *),*Proceso2 (void *);
	pthread_t hilos[NHILOS];
	int status, i, v[NHILOS];
	extern double counter;
	double *r_value;

	// Peterson
	P1QuiereEntrar = FALSE;
	P2QuiereEntrar = FALSE;
	TurnoProceso = PRIMERO;
	// Proceso 1
	v[0]=0;
	if ((status = pthread_create(&hilos[0],NULL, Proceso1, (void *) &v[0])))
	{
		exit(status);
	}
	// Proceso 2
	v[1]=1;
	if ((status = pthread_create(&hilos[1], NULL, Proceso2, (void *) &v[1])))
	{
		exit(status);
	}
	// Wait threads
	for(i=0;i<NHILOS;i++)
	{
		pthread_join(hilos[i], (void **) &r_value);
		printf("El hilo %d retorna %lf\n", i, *r_value);
	}
	// Resultado final
	fprintf(stdout, "%f\n", counter);
	return 0;
}

void *Proceso1(void *p)
{
	extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
	extern TURNO TurnoProceso;
	double *to_return;
	extern double counter;
	int *id, i;

	id = (int *) p;

	for (i = 0; i < ITER; i++) 
	{
		P1QuiereEntrar = TRUE;
		TurnoProceso = SEGUNDO;
		while (P2QuiereEntrar && TurnoProceso == SEGUNDO);/*Espero a que P2 acabe*/
		//Seccion critica
		counter++;
		fprintf(stdout, "Hilo %d: %f\n", *id, counter);
		to_return = malloc(sizeof(double));
		*to_return = counter;
		//Salida seccion critica
		P1QuiereEntrar = FALSE;	
	}
	pthread_exit((void *) to_return);
}	

void *Proceso2(void *p)
{
	extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
	extern TURNO TurnoProceso;
	double *to_return;
	extern double counter;
	int *id, i;

	id = (int *) p;

	for (i = 0; i < ITER; i++) 
	{
		P2QuiereEntrar = TRUE;
		TurnoProceso = PRIMERO;
		while (P1QuiereEntrar && TurnoProceso == PRIMERO);/*Espero a que P1 acabe*/
		//Seccion critica
		counter++;
		fprintf(stdout, "Hilo %d: %f\n", *id, counter);
		to_return = malloc(sizeof(double));
		*to_return = counter;
		//Salida seccion critica
		P2QuiereEntrar = FALSE;	
	}
	pthread_exit((void *) to_return);
}
