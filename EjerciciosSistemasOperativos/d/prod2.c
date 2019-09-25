#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

#define ITER	5
#define N	ITER*P
#define P	2
#define C	2

//Variables gloables compartidas 
int bufer[N]; //item buffer[N];
int producidos=0;
int consumidos=0;
int indice=0;

//Semaforos empty, full y mutex
sem_t empty;
sem_t full;
sem_t mutex;

/*
wait() => sem_wait (sem_t *)
signal() => sem_post (sem_t *)
init() => sem_init (sem_t *, int, int)
*/

int main()
{
	extern sem_t mutex;
	extern sem_t empty;
	extern sem_t full;
	//El segundo parametro indica si es hilo(0) o proceso (1)
	sem_init(&mutex, 0,1); //El segundo parametro indica si es hilo(0) o proceso (1)
	sem_init(&full, 0,0);//Numero de elementos del bufer
	sem_init(&empty,0,N);//Numero de posiciones del bufer libres
	pthread_t productores[P];
	pthread_t consumidores[C];
	int i,status,v[N];
	srand(time(NULL));
	void productor(void *);
	void consumidor(void *);

	// Create NHILOS threads
	for(i=0;i<P;i++)
	{	
		v[i]=i;
		if ((status=pthread_create(&productores[i],NULL,(void *)productor,(void *)&v[i])))
		    exit(status);
	}
	for(i=0;i<C;i++)
	{
		v[i]=i;
		if ((status = pthread_create(&consumidores[i], NULL,(void *) consumidor,(void *)&v[i])))
		    exit(status);
	}

	// Espero a los threads
	for (i = 0; i < P; i++) 
	{
		pthread_join(productores[i],NULL);
	}	
	for (i = 0; i < C; i++) 
	{
		pthread_join(consumidores[i], NULL);
    	}
	
	printf("Suma producidos: %d\n",producidos);
	printf("Suma consumidos: %d\n",consumidos);
	return 0;
}
void productor(void *v)
{
	int j,*id,dato;
	extern int bufer[N],producidos,indice;
	extern sem_t mutex;
	extern sem_t empty;
	extern sem_t full;
	id=(int *)v;
	for(j=0;j<ITER;j++)
	{
		//Entrada SC
		
		sem_wait(&empty);
		sem_wait(&mutex);
		//Genera dato
		//sc
		dato=rand()%1000;
		
		bufer[indice]=dato;
		indice++;		
		printf("Produce %d (Hilo productor %d)\n",dato,*id);
		//Salida SC
		sem_post(&mutex);
		sem_post(&full);
		producidos+=dato;
		
	}	
	pthread_exit(NULL);
}

void consumidor(void *v)
{
	int j,*id,dato;
	extern int bufer[N],consumidos;
	extern sem_t mutex;
	extern sem_t empty;
	extern sem_t full;
	id=(int *)v;
	for(j=0;j<ITER;j++)
	{
		//Entrada SC
		sem_wait(&full);
		sem_wait(&mutex);
		//SC
		dato=bufer[indice-1];
		indice--;
		printf("Consume %d (Hilo consumidor %d)\n",dato,*id);
		//Salida SC		
		sem_post(&mutex);
		sem_post(&empty);
		consumidos+=dato;
		
	}
	pthread_exit(NULL);
}
