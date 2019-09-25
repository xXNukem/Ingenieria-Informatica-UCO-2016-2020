#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define ITER	100
#define NHILOS	4
#define N 4

typedef unsigned char BOOLEAN;
BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
typedef enum{

PRIMERO, SEGUNDO
}TURNO;
TURNO TurnoProceso;
double counter = 0;

BOOLEAN Elegido[N];
int ticket[N];

int main()
{
    pthread_t hilos[NHILOS];
    int status, i, v[N];
    extern double counter;
    double *r_value;
    extern BOOLEAN Elegido[N];
    extern int ticket[N];
    void *Process(int);

	P1QuiereEntrar=FALSE;
	P2QuiereEntrar=FALSE;

	/*Inicialización de variables globales*/
	for(i=0;i<N;i++)
	{
		Elegido[i]=TRUE;
		ticket[i]=0;
	}

	/*Se inician los N procesos*/
	for(i=1;i<=N;i++)
	{
		if ((status = pthread_create(&hilos[N], NULL, Process, (int) &v[i])))
		exit(status);
		Process(i);
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

void *Process(int i)
{

	extern BOOLEAN Elegido[N];
	extern int ticket[N];
	int j;
	while(TRUE)
	{

		Elegido[i]=TRUE;
		ticket[i]=max(ticket[0],ticket[1],ticket[2],ticket[3])+1;
		Elegido[i]=FALSE;
		for(j=0;j<N;j++)
		{

			while(Elegido[j]);
			while((ticket[j] != 0) && (ticket[j],j) <m> (ticket[i],i);
		}
		
		//SECCION CRITICA

		for (i = 0; i < ITER; i++) 
		{
			l = counter;
			fprintf(stdout, "Hilo %d: %f\n", *id, counter);
			l++;
			counter = l;
    		}

		to_return = malloc(sizeof(double));

    		*to_return = counter;

		ticket[i]=0;

		//SECCION RESIDUAL

		}

	}

}


