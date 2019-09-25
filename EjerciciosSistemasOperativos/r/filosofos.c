// Solucion al problema de la cena de los filosofos
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define N 		5
#define IZQUIERDA(x)	(((x)>0) ? (x)-1 : N-1)
#define DERECHA(x)	(((x)+1)%N)

typedef enum
{
	PENSANDO, HAMBRIENTO, COMIENDO
} status;

typedef pthread_mutex_t semaforo;

status estado[N] = {PENSANDO, PENSANDO, PENSANDO, PENSANDO, PENSANDO};
semaforo mutex, contador, s[N] = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER};

int comida = 0, contadorFilosofico;

pthread_cond_t nocomida;
semaforo comutex;

void CogerTenedores(int);
void SoltarTenedores(int);
void Comprobar(int);

void main()
{
	extern int contadorFilosofico;
	extern semaforo mutex, contador;
	void *Filosofo(void *);
	void *Cocinero(void *);

	pthread_t hilos[N];
	int status, i, v[N];

	contadorFilosofico = 0;
	
	pthread_mutex_init(&contador, NULL);
	pthread_cond_init(&nocomida, NULL);  
	pthread_mutex_init(&comutex, NULL);
	pthread_mutex_init(&mutex, NULL);

	for (i = 0; i < N; i++) //Abrimos hilos
	{
		//printf("PC1\n");
		v[i] = i;

		if (i == 0)
		{
			if ((status = pthread_create(&hilos[i], NULL, Cocinero, (void *) NULL)))
				exit(status);
		}

		if (i == 1)
		{
			if ((status = pthread_create(&hilos[i], NULL, Filosofo, (void *) &v[i])))
				exit(status);
		}

		if (i == 2)
		{
			if ((status = pthread_create(&hilos[i], NULL, Filosofo, (void *) &v[i])))
				exit(status);
		}

		if (i == 3)
		{
			if ((status = pthread_create(&hilos[i], NULL, Filosofo, (void *) &v[i])))
				exit(status);
		}

		if (i == 4)
		{
			if ((status = pthread_create(&hilos[i], NULL, Filosofo, (void *) &v[i])))
				exit(status);
		}
	}


	for (i = 0; i < N; i++)  //Unimos hilos
	{
		pthread_join(hilos[i], NULL);
		printf("Hilos finalizado.\n");
	}
}

 void *Filosofo(void *p)
{
	int i, d, sec, comer;
	extern int comida, contadorFilosofico;
	extern semaforo comutex, contador;
	extern pthread_cond_t nocomida;

	i = *(int *) p;

	//printf("PC2\n");
	for(d = 0; d < 3; d++)
	{
		printf("Filósofo %d piensa %d segundos.\n", i, sec = random() % 11);
		sleep(sec); //Pensar

		CogerTenedores(i);

		pthread_mutex_lock (&comutex);
		comer =	(random() % 6);
		while(1)
		{
			if(comida >= comer)
			{
				printf("Filosofo %d come %d segundos.\n", i, sec = random() % 11);
				comida -= comer;
				sleep (sec); //Comer
				pthread_mutex_unlock(&comutex);
				break;
			}
			else
			{
				printf("Filosofo %d espera comida.\n", i);
				pthread_cond_wait (&nocomida, &comutex);
				pthread_mutex_unlock(&comutex);
			}
		}

		printf("Filosofo %d suelta tenedores.\n", i);
		SoltarTenedores(i);
	}

	pthread_mutex_lock(&contador);
	contadorFilosofico++;
	pthread_mutex_unlock(&contador);
}

 void CogerTenedores(int i)
{
	extern semaforo mutex, s[N];
	extern status estado[N];

	//printf("PC3\n");
	pthread_mutex_lock(&mutex);
	//printf("PC4\n");
	estado[i] = HAMBRIENTO;
	//printf("PC5\n");
	Comprobar(i);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_lock(&s[i]);
}

 void SoltarTenedores(int i)
{
	extern semaforo mutex;
	extern status estado[N];

	//printf("PC6\n");
	pthread_mutex_lock(&mutex);
	estado[i] = PENSANDO;
	Comprobar(IZQUIERDA(i));
	Comprobar(DERECHA(i));
	pthread_mutex_unlock(&mutex);
}

 void Comprobar(int i)
{
	extern semaforo s[N];
	extern status estado[N];

	//printf("PC7\n");
	if(estado[i] == HAMBRIENTO && estado[IZQUIERDA(i)] != COMIENDO && estado[DERECHA(i)] != COMIENDO)
	{
		estado[i] = COMIENDO;
		pthread_mutex_unlock(&s[i]);
	}
}

 void *Cocinero(void * p)
{
	extern int comida, contadorFilosofico;
	extern semaforo comutex, contador;

	int com;

	pthread_mutex_lock(&contador);
	while(contadorFilosofico != 4)
	{
		pthread_mutex_unlock(&contador);
		pthread_mutex_lock(&comutex);
		com = (random() % 101);
		printf("Se prepara %d comida.\n", com);

		comida += com;

		pthread_cond_broadcast (&nocomida);
		pthread_mutex_unlock(&comutex);

		sleep(5);
	}
}
