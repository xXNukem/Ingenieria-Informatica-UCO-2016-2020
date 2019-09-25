#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define N 5
#define P 2
#define IZQUIERDA(x)	(((x)>0) ? (x)-1 : N-1)
#define DERECHA(x)	(((x)+1)%N)

typedef enum {
    PENSANDO, HAMBRIENTO, COMIENDO
}status;
status estado[N];
pthread_mutex_t mutex, s[N],semComida;
pthread_cond_t condFilosofo;

/*
pthread_mutex_lock() = wait
pthread_mutex_unlock() = signal
*/

void Cocina();
void Filosofo(int);
void CogerTenedores(int);
void SoltarTenedores(int);
void Comprobar(int);
int comida=0;

main()
{
	// Inicialización de variables
	int i,status;	
	pthread_mutex_init (&mutex,NULL);
	pthread_mutex_init (&semComida,NULL);
	pthread_cond_init (&condFilosofo,NULL);
	pthread_t hilos[N],cocina;
	srand(time(NULL));

	for(i=0;i<N;i++)
	{
		pthread_mutex_init(&s[i],NULL);
		estado[i]=PENSANDO;
	}
	if((status=pthread_create(&cocina,NULL,(void *)Cocina,NULL)))
	{
		exit(status);
	}
	for(i=0;i<N;i++)
	{
		if((status=pthread_create(&hilos[i], NULL,(void *)Filosofo,(void *)i)))
		{
			exit(status);
		}
	}
	for (i = 0; i < N; i++) 
	{
		pthread_join(hilos[i],NULL);
	}
	pthread_join(cocina,NULL);

}
void Cocina ()
{
	int c=0,x;
	extern pthread_mutex_t semComida;
	extern int comida;

	while(TRUE)
	{
		sleep(5);
		c=(rand()%101);	
		pthread_mutex_lock(&semComida);	
		comida+=c;
		pthread_mutex_unlock(&semComida);
		printf("Se ha cocinado %d unidades\n",c);
	}
}

void Filosofo(int i)
{
	int c=0,x;
	extern pthread_mutex_t s[N],semComida;
	extern pthread_cond_t condFilosofo;
	extern int comida;

	while(TRUE)
	{
		//Pensar
		printf("El filosofo %d esta pensando\n",i);
		estado[i]=PENSANDO;
		sleep(rand()%11);
		pthread_cond_broadcast(&condFilosofo);	
		CogerTenedores(i);
		//Comer
		c=(rand()%6);
		printf("Filosofo %d quiere comer %d unidades\n",i,c);
		if(comida<c)
		{
			printf("No hay suficientes unidades de comida\n"),
			pthread_cond_wait(&condFilosofo,&s[i]);
		}
		else
		{	
			pthread_mutex_lock(&semComida);
			pthread_mutex_lock(&mutex);	
			estado[i]=COMIENDO;
			comida-=c;
			pthread_mutex_unlock(&mutex);
			pthread_mutex_unlock(&semComida);	
			printf("El filosofo %d se come %d unidades\n",i,c);
			sleep(rand()%11);
			SoltarTenedores(i);
		}
	}
}

void CogerTenedores(int i)
{
	extern pthread_mutex_t mutex,s[N];
	extern status estado[N];

	pthread_mutex_lock(&mutex);
	estado[i] = HAMBRIENTO;
	Comprobar(i);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_lock(&s[i]);
}

void SoltarTenedores(int i)
{
	extern pthread_mutex_t mutex;
	extern status estado[N];

	pthread_mutex_lock(&mutex);
	estado[i] = PENSANDO;
	Comprobar(IZQUIERDA(i));
	Comprobar(DERECHA(i));
	pthread_mutex_unlock(&mutex);
}

void Comprobar(int i)
{
	extern pthread_mutex_t s[N];
	extern status estado[N];

	if (estado[i] == HAMBRIENTO && estado[IZQUIERDA(i)] != COMIENDO &&
	estado[DERECHA(i)] != COMIENDO) 
	{
		estado[i] = COMIENDO;
		pthread_mutex_unlock(&s[i]);
	}
}

