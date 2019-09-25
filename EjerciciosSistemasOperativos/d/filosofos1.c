#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define ITER 2
#define N 5
#define IZQUIERDA(x)	(((x)>0) ? (x)-1 : N-1)
#define DERECHA(x)	(((x)+1)%N)

typedef enum {
    PENSANDO, HAMBRIENTO, COMIENDO
}status;
status estado[N];
pthread_mutex_t mutex, s[N];

/*
pthread_mutex_lock() = wait
pthread_mutex_unlock() = signal
*/
void Filosofo(int);
void CogerTenedores(int);
void SoltarTenedores(int);
void Comprobar(int);

main()
{
	// Inicialización de variables
	int i;	
	pthread_mutex_init (&mutex,NULL);
	pthread_t hilos[N];
	srand(time(NULL));

	for(i=0;i<N;i++)
	{
		pthread_mutex_init(&s[i],NULL);
		estado[i]=PENSANDO;
	}
	for(i=0;i<N;i++)
	{
		pthread_create(&hilos[i], NULL,(void *)Filosofo,(void *)i);
	}
	for (i=0; i<N;i++) 
	{
		pthread_join(hilos[i],NULL);
	}

}
void Filosofo(int i)
{
	int j;

	for(j=0;j<ITER;j++)
	{
		//Pensar
		estado[i]=PENSANDO;
		printf("El filosofo %d esta pensando\n",i);
		sleep(rand()%11);
		CogerTenedores(i);
		//Comer
		estado[i]=COMIENDO;
		printf("El filosofo %d esta comiendo chocolate\n",i);
		sleep(rand()%11);
		SoltarTenedores(i);
	}
}

void CogerTenedores(int i)
{
	pthread_mutex_lock(&mutex);
	estado[i] = HAMBRIENTO;
	Comprobar(i);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_lock(&s[i]);
}

void SoltarTenedores(int i)
{
	pthread_mutex_lock(&mutex);
	estado[i] = PENSANDO;
	Comprobar(IZQUIERDA(i));
	Comprobar(DERECHA(i));
	pthread_mutex_unlock(&mutex);
}

void Comprobar(int i)
{
	if (estado[i] == HAMBRIENTO && estado[IZQUIERDA(i)] != COMIENDO &&
	estado[DERECHA(i)] != COMIENDO) 
	{
		estado[i] = COMIENDO;
		pthread_mutex_unlock(&s[i]);
	}
}

