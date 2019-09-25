#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define N 2
#define ITER 10

//DECLARACION DE TYPEDEF
typedef unsigned char BOOLEAN;
typedef enum
{
	PRIMERO, SEGUNDO
}TURNO;
BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
TURNO TurnoProceso;

//VARIABLES GLOBALES
int contador=0;

//FUNCIONES
void * Proceso1(void *);
void * Proceso2(void *);

int main()
{
	extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
	extern TURNO TurnoProceso;
	extern int contador;
	pthread_t hilos[N];
	int * retorno;
	int v[N], estado, i;

	P1QuiereEntrar=FALSE;
	P2QuiereEntrar=FALSE;
	TurnoProceso=PRIMERO;

	v[0]=1;
	if((estado=pthread_create(&hilos[0], NULL, Proceso1, (void *) &v[0])))
		exit(estado);

	v[1]=2;
	if((estado=pthread_create(&hilos[1], NULL, Proceso2, (void *) &v[1])))
		exit(estado);

	for(i=0;i<N;i++)
	{
		pthread_join(hilos[i],(void **)&retorno);
	}

	printf("Resultado final: %d\n", contador);

	return 0;
}

void * Proceso1(void * p)
{
	extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
	extern TURNO TurnoProceso;
	extern int contador;
	int * retorno;
	int id, i;

	id=*(int *)p;

	for(i=0;i<ITER;i++)
	{
		P1QuiereEntrar=TRUE;
		TurnoProceso=SEGUNDO;
		while(P2QuiereEntrar && TurnoProceso==SEGUNDO);
		contador++;
		printf("El proceso %d lleva %d\n", id, contador);
		P1QuiereEntrar=FALSE;

		retorno=malloc(sizeof(int));
		*retorno=contador;
	}

	pthread_exit((void *) retorno);
}

void * Proceso2(void * p)
{
	extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
	extern TURNO TurnoProceso;
	int id, i;
	int * retorno;

	id=*(int *)p;

	for(i=0;i<ITER;i++)
	{
		P2QuiereEntrar=TRUE;
		TurnoProceso=PRIMERO;
		while(P1QuiereEntrar && TurnoProceso==PRIMERO);
		contador++;
		printf("El proceso %d lleva %d\n", id, contador);
		P2QuiereEntrar=FALSE;

		retorno=malloc(sizeof(int));
		*retorno=contador;
	}

	pthread_exit((void *) retorno);
}
