#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define N 2
#define ITER 10

//DECLARACION DE TYPEDEF

typedef unsigned char BOOLEAN;
typedef enum
{
	PRIMERO, SEGUNDO
}TURNO;
TURNO TurnoProceso;
BOOLEAN P1QuiereEntrar, P2QuiereEntrar;

//VARIABLES GLOBALES
int contador=0;

void * Proceso1(void *);
void * Proceso2(void *);

int main()
{
  
	extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
	int estado;
	P1QuiereEntrar=FALSE;
	P2QuiereEntrar=FALSE;

	pthread_t hilos[N];
	int v[N], i;
	int * retorno;

	//DECLARACION DE HIJOS

	v[0]=1;
	if((estado=pthread_create(&hilos[0],NULL,Proceso1,(void *) &v[0])))
		exit(estado);

	v[1]=2;
	if((estado=pthread_create(&hilos[1],NULL,Proceso2,(void *) &v[1])))
		exit(estado);

	for(i=0;i<N;i++)
	{
		pthread_join(hilos[i], (void **) &retorno);
	}

	printf("Resultado final: %d\n",contador);
	
	return 0;

}

void * Proceso1(void * p)
{
	extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
	extern TURNO TurnoProceso;
	extern int contador;
	int * retorno;
	int * id;
	int i;

	id=(int *)p;

	for(i=0;i<ITER;i++)
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
		contador++;
		printf("El proceso %d lleva %d\n",*id,contador);

		retorno=malloc(sizeof(int));
		*retorno=contador;

		P1QuiereEntrar=FALSE;
		TurnoProceso=SEGUNDO;
	}

	pthread_exit((void *)retorno);
	
}

void * Proceso2(void * p)
{
	extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
	extern TURNO TurnoProceso;
	extern int contador;
	int * retorno;
	int * id;
	int i;

	id=(int *)p;

	for(i=0;i<ITER;i++)
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
		contador++;
		printf("El proceso %d lleva %d\n",*id,contador);

		retorno=malloc(sizeof(int));
		*retorno=contador;

		P2QuiereEntrar=FALSE;
		TurnoProceso=PRIMERO;
	}

	pthread_exit((void *)retorno);
}
