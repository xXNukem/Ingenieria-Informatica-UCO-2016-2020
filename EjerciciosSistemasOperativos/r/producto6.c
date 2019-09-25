#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define N 5
#define P 1
#define C 1
#define ITER 10

//DEFINICION DE SEMAFOROS

sem_t mutex;
sem_t entradas_vacias;
sem_t entradas_ocupadas;

//DECLARACION DE BUFFER
int buffer[N];

//FUNCIONES

void * Productor();
void * Consumidor();

int main()
{
	srand(time(NULL));
	
	extern sem_t mutex, entradas_vacias, entradas_ocupadas;
	pthread_t hilos[P+C];
	int estado, v[P+C], retorno, i;

	sem_init(&mutex, 0, 1);
	sem_init(&entradas_vacias, 0, N);
	sem_init(&entradas_ocupadas, 0, 0);

	//DEFINICION DEL PRODUCTOR
	v[0]=1;
	if((estado=pthread_create(&hilos[0], NULL, Productor, NULL)))
		exit(estado);

	//DEFINICION DEL CONSUMIDOR
	v[1]=2;
	if((estado=pthread_create(&hilos[1], NULL, Consumidor, NULL)))
		exit(estado);

	for(i=0;i<P+C;i++)
	{
		pthread_join(hilos[i],NULL);
	}

	return 0;
}//fin main

void * Productor ()
{
	extern sem_t mutex, entradas_vacias, entradas_ocupadas;
	extern buffer[N];
	int dato, i;

	for(i=0;i<ITER;i++)
	{
		sem_wait(&entradas_vacias);
		sem_wait(&mutex);
		dato=rand()%1000;
		printf("Producido el valor %d\n",dato);
		buffer[i]=dato;
		sem_post(&mutex);
		sem_post(&entradas_ocupadas);
	}
	
	pthread_exit(NULL);
}//fin productor

void * Consumidor()
{
	extern sem_t mutex, entradas_vacias, entradas_ocupadas;
	extern buffer[N];
	int dato, i;

	for(i=0;i<ITER;i++)
	{
		sem_wait(&entradas_ocupadas);
		sem_wait(&mutex);
		dato=buffer[i];
		printf("Consumido valor %d\n",dato);
		sem_post(&mutex);
		sem_post(&entradas_vacias);
	}

	pthread_exit(NULL);
}//fin consumidor
