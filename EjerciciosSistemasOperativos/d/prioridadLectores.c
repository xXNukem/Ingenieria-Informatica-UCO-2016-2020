/*
Enunciado
---------
Implementar la solución al problema de los lectores/escritores usando hilos o procesos.

Se debe implementar las siguientes soluciones:

1) Solución con prioridad a lectores usando semáforos.

2) Solución con prioridad a escritores usando semáforos

3) Solución usando variables condición (tomar como modelo la solución usando monitores)

El acceso a la información compartida por lectores y escritores queda a la elección del alumno.
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ITER 3
#define N 2

sem_t mutex,db;

int rc=0,bbdd=0;

main()
{
	// Inicialización de variables
	extern sem_t mutex,db;
	int i,status,v[N];	
	sem_init (&mutex,0,1);
	sem_init (&db,0,1);
	pthread_t lectores[N];
	pthread_t escritores[N];
	srand(time(NULL));
	void Lector(void *);
	void Escritor(void *);

	for(i=0;i<N;i++)	
	{
		v[i]=i;
		if((status=pthread_create(&lectores[i], NULL,(void *)Lector,(void *)&v[i])))
		{
			exit(status);
		}
	}
	for(i=0;i<N;i++)
	{
		v[i]=i;
		if((status=pthread_create(&escritores[i], NULL,(void *)Escritor,(void *)&v[i])))
		{
			exit(status);
		}
	}
	
	for(i=0;i<N;i++)
	{
		pthread_join(lectores[i],NULL);
	}
	for(i=0;i<N;i++)
	{
		pthread_join(escritores[i],NULL);
	}

}
void Lector(void *v)
{
	extern sem_t mutex,db;
	extern int bbdd;
	int x,*id;
	id=(int *)v;

	for(x=0;x<ITER;x++)
	{
		sem_wait(&mutex);
		rc++;
		if(rc==1)
		{
			sem_wait(&db);
		}
		sem_post(&mutex);
		/*Leer base de datos*/
		printf("Lector %d lee de la BBDD %d\n",*id,bbdd);
		sem_wait(&mutex);
		rc--;
		if(rc==0)
		{
			sem_post(&db);
		}
		sem_post(&mutex);
	}
}

void Escritor(void *v)
{
	extern sem_t db;
	extern int bbdd;
	int x,*id;
	id=(int *)v;

	for(x=0;x<ITER;x++)
	{
		sem_wait(&db);
		/*Escribir en base de datos*/
		bbdd=rand()%11;
		printf("Escritor %d escribe en la base de datos %d\n",*id,bbdd);	
		sem_post(&db);
	}	
}


