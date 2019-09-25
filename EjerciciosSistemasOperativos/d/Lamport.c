#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define ITER	5
#define NHILOS	4
#define FALSE 0
#define TRUE 1

double counter = 0;
typedef unsigned char BOOLEAN;
BOOLEAN Eligiendo [NHILOS];
int Numero[NHILOS];

int main()
{
	extern BOOLEAN Eligiendo[NHILOS];
	extern int Numero[NHILOS];
	pthread_t hilos[NHILOS];
	int status, i, v[NHILOS];
	extern double counter;
	void *adder(void *);
	int max(int *vector);

	//Inicializa las variables globales
	for(i=0;i<NHILOS;i++)
	{
		Eligiendo[i]=TRUE;
		Numero[i]=0;
	}
	// Create NHILOS threads
	for (i = 0; i < NHILOS; i++) {
		v[i] = i;
		if ((status = pthread_create(&hilos[i], NULL, adder, (void *) &v[i])))
		exit(status);
	}

	// Espera a los hilos
	for (i = 0; i < NHILOS; i++) 
	{
		pthread_join(hilos[i], NULL);
	}

	// Resultado final
	fprintf(stdout, "%f\n", counter);

	return 0;
}

void *adder(void *p)
{
	extern double counter;
	int *id,i,j;
	extern BOOLEAN Eligiendo[NHILOS];
	extern int Numero[NHILOS];

	id=(int *)p;

	for(i=0; i<ITER; i++)
	{
		Eligiendo[*id]=TRUE;
		Numero[*id]=max(Numero)+1;		
		Eligiendo[*id]=FALSE;
		for(j=0;j<NHILOS;j++)
		{
			while (Eligiendo[j]);
			while((Numero[j] != 0) && ((Numero[j] < Numero[*id]) || ((Numero[j] == Numero[*id]) && (j<*id))) );
		}
		//Seccion critica
		counter++;
		fprintf(stdout, "Hilo %d: %f\n", *id, counter);
		//Seccion residual
		Numero[*id]=0;
	}
	pthread_exit(NULL);
}

int max(int *v)
{
	int i,max;
	max=v[0];

	for(i=1;i<NHILOS;i++)
	{
		if(v[i]>max)
		{
			max=v[i];
		}
	}
	return max;
}
