#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define N 5
#define ITER 10
#define IZQUIERDA(x) (((x)>0) ? (x)-1 : N-1)
#define DERECHA(x) (((x)+1)%N)

//DECLARACION SEMAFOROS

pthread_mutex_t mutex, s[N];

//DECLARACION TYPEDEF

typedef enum
{
	PENSANDO, HAMBRIENTO, COMIENDO
}estatus;

estatus estado[N];

//FUNCIONES

void Filosofo (void *);
void CogerTenedor (int);
void SoltarTenedor (int);
void Comprobar(int);

int main()
{
	extern pthread_mutex_t mutex, s[N];
	int i, status, v[N];
	pthread_t filosofo[N];

	sem_init(&mutex, 0, 1);

	//SEMILLA

	srand(time(NULL));

	for(i=0;i<N;i++)
	{
		pthread_mutex_init(&s[i],NULL);
		estado[i]=PENSANDO;
	}

	for(i=0;i<N;i++)
	{
		v[i]=i+1;
		if((status=pthread_create(&filosofo[i], NULL, (void *)Filosofo, (void *) &v[i])))
			exit(status);
	}

	for(i=0;i<N;i++)
	{
		pthread_join(filosofo[i], NULL);
	}

	return 0;
}

void Filosofo (void * p)
{
	int id, i;

	id=*(int *)p;

	while(TRUE)
	{
		printf("El filosofo %d esta pensando\n",id);
		sleep(rand()%10);
		CogerTenedor(id);
		printf("El filosofo %d esta comiendo\n",id);
		SoltarTenedor(id);
	}
}

void CogerTenedor(int i)
{
	extern pthread_mutex_t mutex, s[N];
	extern estatus estado[N];

	pthread_mutex_lock(&mutex);
	estado[i]=HAMBRIENTO;
	Comprobar(i);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_lock(&s[i]);
}

void SoltarTenedor(int i)
{
	extern pthread_mutex_t mutex, s[N];
	extern estatus estado[N];

	pthread_mutex_lock(&mutex);
	estado[i]=PENSANDO;
	Comprobar(IZQUIERDA(i));
	Comprobar(DERECHA(i));
	pthread_mutex_unlock(&mutex);
}

void Comprobar(int i)
{
	extern estatus estado[N];
	extern pthread_mutex_t s[N];

	if(estado[i]==HAMBRIENTO && estado[DERECHA(i)]!=COMIENDO && estado[IZQUIERDA(i)]!=COMIENDO)
	{
		estado[i]=COMIENDO;
		pthread_mutex_unlock(&s[i]);
	}
}
