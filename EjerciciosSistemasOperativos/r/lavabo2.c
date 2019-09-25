#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define CAPACIDAD 3
#define MUJERES 4
#define HOMBRES 4


typedef sem_t semaforo;

semaforo lavabo, sHombres, sMujeres, cola;

int personas=0;
pthread_t hilos[HOMBRES+MUJERES];
void *mujer();
void *hombre();
int main()
{
	extern semaforo lavabo, sHombres,sMujeres,cola;
	int i,status;
	double r_value;
	sem_init(&lavabo, 0, CAPACIDAD);
	sem_init(&sHombres, 0, 1);
	sem_init(&sMujeres, 0, 1);
	sem_init(&cola, 0, 1);

	for(i=0;i<MUJERES;i++)
		if ((status = pthread_create(&hilos[i], NULL, mujer, NULL)))
			exit(status);
	for(i;i<HOMBRES+MUJERES;i++)	
		if ((status = pthread_create(&hilos[i], NULL, hombre, NULL)))
		exit(status);
				
	for (i = 0; i < HOMBRES+MUJERES ; i++) 
	{
		pthread_join(hilos[i], (void **) &r_value);	
	}
}

void *mujer()
{
	extern semaforo lavabo, sHombres,sMujeres,cola;
	extern int personas;
	
		sem_wait(&cola);
		sem_wait(&sMujeres);
			if(personas==0)
				sem_wait(&sHombres);
			
		sem_post(&sMujeres);
		sem_post(&cola);
		sem_wait(&lavabo);
		personas++;
		printf("Mujeres dentro %d\n",personas);
		personas--;
		sem_post(&lavabo);
		
		sem_wait(&sMujeres);
			if(personas==0)
				sem_post(&sHombres);
		sem_post(&sMujeres);
}

void *hombre(void *p)
{
	extern semaforo lavabo, sHombres,sMujeres,cola;
	extern int personas;
	
		sem_wait(&cola);
		sem_wait(&sHombres);
			if(personas==0)
				sem_wait(&sMujeres);
			
		sem_post(&sHombres);
		sem_post(&cola);
		sem_wait(&lavabo);
		personas++;
		printf("Hombres dentro %d\n",personas);
		personas--;
		sem_post(&lavabo);
		
		sem_wait(&sHombres);
			if(personas==0)
				sem_post(&sMujeres);
		sem_post(&sHombres);	
}
