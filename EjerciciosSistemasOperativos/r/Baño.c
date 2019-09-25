#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

typedef sem_t semaforo;

semaforo mutex, mutex2, cola, bano, hombre, mujer;
int Mcontador, Hcontador;

void * Mujer (void *);
void * Hombre (void *);

int main()
{
	extern semaforo mutex, cola, hombre, mujer, bano;
	extern int Mcontador, Hcontador;
	
	int i, status, v[8];
	pthread_t hilos[8];

	Mcontador = 0;
	Hcontador = 0;

	sem_init(&mutex2, 0, 1);
	sem_init(&mutex, 0, 1);
	sem_init(&cola, 0, 1);
	sem_init(&hombre, 0, 1);
	sem_init(&mujer, 0, 1);
	sem_init(&bano, 0, 7);

	for(i = 0; i < 8; i++)
	{
		v[i] = i;
		if(i == 0) 
			if((status = pthread_create(&hilos[i], NULL, Mujer, (void *) &v[i])))
				exit(0);
		if(i == 1) 
			if((status = pthread_create(&hilos[i], NULL, Mujer, (void *) &v[i])))
				exit(0);
		if(i == 2) 
			if((status = pthread_create(&hilos[i], NULL, Mujer, (void *) &v[i])))
				exit(0);
		if(i == 3) 
			if((status = pthread_create(&hilos[i], NULL, Mujer, (void *) &v[i])))
				exit(0);
		if(i == 4) 
			if((status = pthread_create(&hilos[i], NULL, Hombre, (void *) &v[i])))
				exit(0);
		if(i == 5) 
			if((status = pthread_create(&hilos[i], NULL, Hombre, (void *) &v[i])))
				exit(0);
		if(i == 6) 
			if((status = pthread_create(&hilos[i], NULL, Hombre, (void *) &v[i])))
				exit(0);
		if(i == 7) 
			if((status = pthread_create(&hilos[i], NULL, Hombre, (void *) &v[i])))
				exit(0);
	}

	for(i = 0; i < 8; i++)
	{
		pthread_join(hilos[i], NULL);
		printf("Finalizando procesos\n");
	}

	return 0;
}

void * Mujer (void *p)
{
	extern semaforo mutex, cola, mujer, hombre, bano;
	extern int Mcontador;

	int id;

	id = *(int *) p;

	printf("Proceso mujer %d entra en cola:\n", id);

	sem_wait(&cola);
	sem_wait(&mujer);
	sem_wait(&mutex);

	Mcontador++;
	if(Mcontador == 1)
		sem_wait(&hombre);

	sem_post(&mutex);
	sem_post(&mujer);
	sem_post(&cola);

	sem_wait(&bano);
	printf("Proceso mujer %d, entra al baño 5 segundos\n", id);
	sleep(5);
	sem_post(&bano);

	sem_wait(&mutex);
	Mcontador--;
	if(Mcontador == 0)
		sem_post(&hombre);
	sem_post(&mutex);
	
	 
}

void * Hombre (void *p)
{
	extern semaforo mutex2, cola, mujer, hombre, bano;
	extern int Hcontador;

	int id;

	id = *(int *) p;

	printf("Proceso hombre %d entra en cola.\n", id);

	sem_wait(&cola);
	sem_wait(&hombre);
	sem_wait(&mutex2);

	Hcontador++;
	if(Hcontador == 1)
		sem_wait(&mujer);

	sem_post(&mutex2);
	sem_post(&hombre);
	sem_post(&cola);

	sem_wait(&bano);
	printf("Proceso hombre %d, entra al baño 5 segundos.\n", id);
	sleep(5);
	sem_post(&bano);

	sem_wait(&mutex2);
	Hcontador--;
	if(Hcontador == 0)
		sem_post(&mujer);
	sem_post(&mutex2);
	
	 
}
