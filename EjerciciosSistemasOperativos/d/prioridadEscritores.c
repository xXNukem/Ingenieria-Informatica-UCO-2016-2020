#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ITER 3
#define N 2

sem_t mutex1,mutex2,wdb,rdb;

int rc=0,wc=0,bbdd=0;

main()
{
	// Inicialización de variables
	extern sem_t mutex1,mutex2,wdb,rdb;
	int i,status,v[N];	
	sem_init (&mutex1,0,1);
	sem_init (&mutex2,0,1);
	sem_init (&wdb,0,1);
	sem_init (&rdb,0,1);
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
	extern sem_t mutex2,wdb,rdb;
	extern int bbdd,rc;
	int x,*id;
	id=(int *)v;
	for(x=0;x<ITER;x++)
	{
		sem_wait(&rdb);
		sem_wait(&mutex2);
		rc++;
		if(rc==1)
		{
			sem_wait(&wdb);
		}
		sem_post(&mutex2);
		sem_post(&rdb);
		/*Leer base de datos*/
		printf("Lector %d lee de la BBDD %d\n",*id,bbdd);
		sem_wait(&mutex2);
		rc--;
		if(rc==0)
		{
			sem_post(&wdb);
		}
		sem_post(&mutex2);
	}
}

void Escritor(void *v)
{
	extern sem_t mutex1,wdb,rdb;
	extern int bbdd,wc;
	int x,*id;
	id=(int *)v;
	for(x=0;x<ITER;x++)
	{
		sem_wait(&mutex1);
		wc++;
		if(wc==1)
		{
			sem_wait(&rdb);
		}
		sem_post(&mutex1);
		sem_wait(&wdb);
		/*Escribir en base de datos*/
		bbdd=rand()%11;
		printf("Escritor %d escribe en la base de datos %d\n",*id,bbdd);	
		sem_post(&wdb);
		sem_wait(&mutex1);
		wc--;
		if(wc==0)
		{
			sem_post(&rdb);
		}
		sem_post(&mutex1);
	}	
}
