#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define N 3
#define M 5

//DECLARACION DE SEMAFOROS
pthread_mutex_t mutex, variable;

//DECLARACIÓN DE VARIABLES GLOBALES
int global=0,n_lectores=0;

//DEFINICION FUNCIONES
void lector(int i);
void escritor(int i);

int main()
{
	pthread_t lectores[N], escritores[N];
	extern pthread_mutex_t mutex, variable;
	int i,status;

	//INICIALIZACIÓN DE SEMAFOROS
	pthread_mutex_init(&mutex,NULL);
	pthread_mutex_init(&variable,NULL);

	//SEMILLA
	srand(time(NULL));

	//CREACION DE HILOS
	for(i=0;i<N;i++)
	{
		status=pthread_create(&lectores[i],NULL,(void *)lector,(void *)i);//ESTO DEVUELVE 0 SI SE HA CREADO CON EXITO
		if(status!=0)
		{
			printf("Error al crear hilos lectores\n");
			exit(status);
		}
		status=pthread_create(&escritores[i],NULL,(void *)escritor,(void *)i);
		if(status!=0)
		{
			printf("Error al crear hilos escritores\n");
			exit(status);
		}
	}

	//CERRANDO HILOS
	for(i=0;i<N;i++)
	{
		pthread_join(lectores[i],NULL);
	}

	for(i=0;i<N;i++)
	{
		pthread_join(escritores[i],NULL);
	}

	return 0;
}

void lector(int i)
{
	extern pthread_mutex_t mutex, variable;
	extern int global, n_lectores;
	int j;

	for(j=0;j<2;j++)
	{
		pthread_mutex_lock(&mutex);
		n_lectores++;
		if(n_lectores==1)//SOY EL PRIMERO POR TANTO CIERRO EL ACCESO A LA VARIABLE
		{
			pthread_mutex_lock(&variable); //SI NO SOY EL PRIMERO YA ESTA CERRADO
		}
		pthread_mutex_unlock(&mutex);
		printf("Escritor[%d] - El valor es %d\n",i,global);
		pthread_mutex_lock(&mutex);
		n_lectores--;
		if(n_lectores==0)
		{
			pthread_mutex_unlock(&variable); //AL SER EL ULTIMO EN SALIR LIBERO LA VARIABLE PARA QUE EL ESCRITOR PUEDA AMPLIARLA
		}
		pthread_mutex_unlock(&mutex);
	}
}

void escritor(int i)
{
	extern pthread_mutex_t variable;
	extern int global;
	int j, aux;

	for(j=0;j<M;j++)
	{
		pthread_mutex_lock(&variable);
		aux=rand()%5;
		printf("Escritor [%d] - Introduce %d\n",i,aux);
		global=global+aux;
		pthread_mutex_unlock(&variable);
	}
}
