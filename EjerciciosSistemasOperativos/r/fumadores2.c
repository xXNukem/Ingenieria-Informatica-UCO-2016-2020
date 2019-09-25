#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define N 20

typedef sem_t semaforo;

semaforo mutex, sem_provee, sem_fum[3];

int papel, tabaco, cerillas;

int main()
{
	extern semaforo mutex, sem_provee, sem_fum[3];
	extern int papel, tabaco, cerillas;
	int status, v[4];
	int i;
	double r_value;
	pthread_t hilos[4];

	void *Proveedor (void *), *Fumador (void *);

	papel = 0;
	tabaco = 0;
	cerillas = 0;

	sem_init(&mutex, 0, 1);
	sem_init(&sem_provee, 0, 0);
	for(i = 0; i < 3; i++)
		sem_init(&sem_fum[i], 0, 0);

	for(i = 0; i < 4; i++)
	{
		v[i] = i;

		if (i == 0)
		{
			if ((status = pthread_create(&hilos[i], NULL, Fumador, (void *) &v[i])))
				exit(status);
		}

		if (i == 1)
		{
			if ((status = pthread_create(&hilos[i], NULL, Fumador, (void *) &v[i])))
				exit(status);
		}

		if (i == 2)
		{
			if ((status = pthread_create(&hilos[i], NULL, Fumador, (void *) &v[i])))
				exit(status);
		}

		if (i == 3)
		{
			if ((status = pthread_create(&hilos[i], NULL, Proveedor, (void *) &v[i])))
				exit(status);
		}
	}

	for (i = 0; i < 4; i++) 
	{
		pthread_join(hilos[i], (void **) &r_value);	
	}


	return 0;
}

void *Fumador(void *p)
{
	extern int papel, tabaco, cerillas;
	extern semaforo mutex, sem_provee, sem_fum[3];//estos nombre no coincidian con los definidos globales

	int *i;
	int papel_f, tabaco_f, cerillas_f, j;

	i = (int *) p;


	if(*i == 0)
	{
		papel_f  =25;
		tabaco_f = 25;
		cerillas_f = 0;
	}
	if(*i == 1)
	{
		papel_f = 25;
		tabaco_f = 0;
		cerillas_f = 25;
	}
	if(*i == 2)
	{
		papel_f = 0;
		tabaco_f = 25;
		cerillas_f = 25;
	}

	for(j = 0; j < N; j++)
	{
		if(tabaco_f > 0 && papel_f > 0 && cerillas_f > 0)//kito los != xk se daban valores negativos y les seguian kitando. Raro 									xk kita de 1 en 1
		{
			printf("El fumador %d esta fumando\n", *i);
			papel_f--;
			tabaco_f--;
			cerillas--;
		}
		else
		{
			sem_post(&sem_provee);
			sem_wait(&sem_fum[*i]);
			sem_wait(&mutex);

			if(papel > 0 && papel_f == 0)//idem aki, asi no le coge si por algun motivo hay valores negativos
			{
				printf("El fumador %d coge %d papel\n", *i,papel);
				papel_f = papel;
				papel = 0;
			}
			if(tabaco > 0 && tabaco_f == 0)//idem
			{
				printf("El fumador %d coge %d tabaco\n", *i,tabaco);
				tabaco_f = tabaco;
				tabaco = 0;
			}
			if(cerillas > 0 && cerillas_f == 0)//idem
			{
				printf("El fumador %d coge %d cerillas\n", *i,cerillas);
				cerillas_f = cerillas;
				cerillas = 0;
			}

			sem_post(&mutex);
		}
		
	}
}

void *Proveedor(void *p)
{
	extern semaforo mutex, sem_provee, sem_fum[3];//estos nombre no coincidian con los definidos globales
	extern int papel, tabaco, cerillas;

	int i, j, material;
	int nuevo;//para controlar el numero k se genera cada vez
	
	for(i = 0; i < N; i++)
	{
		sem_wait(&sem_provee);
		material = rand() % 3;//aki habia un 4 no se xk
		sem_wait(&mutex);

		nuevo=(rand()%11);

		if(material == 0)
		{
			
			//papel += (rand()%11);
			papel=papel+nuevo;
			printf("Proveedor produce %d papel, total: %d\n",nuevo, papel);
		}
		if(material == 1)
		{
			//tabaco += (rand()%11);
			tabaco=tabaco+nuevo;
			printf("Proveedor produce %d tabaco, total: %d\n", nuevo, tabaco);
		}
		if(material == 2)
		{
			//cerillas += (rand()%11);
			cerillas=cerillas+nuevo;
			printf("Proveedor produce %d cerillas, total: %d\n", nuevo, cerillas);
		}
		sem_post(&mutex);
		for(j = 0; j < 3; j++)
			sem_post(&sem_fum[j]);		
	}
}
