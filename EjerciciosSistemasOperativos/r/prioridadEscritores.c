#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define N 3
#define M 5

//DECLARACION DE SEMAFOROS
pthread_mutex_t mutex1, mutex2, s_escritor, s_lector;

//MUTEX1 CONTROLA EL ACCESO DE ESCRITORES, MUTEX2 EL DE LOS LECTORES, S_ESCRITOR LA ESCRITURA DE LA VARIABLE GLOBAL Y S_LECTOR EL ACCESO DE LOS LECTORES CUANDO NO HAY ESCRITORES

//DECLARACIÓN DE VARIABLES GLOBALES
int global=0,n_lectores=0,n_escritores=0;

//DEFINICION FUNCIONES
void lector(int i);
void escritor(int i);

int main()
{
	pthread_t lectores[N], escritores[N];
	extern pthread_mutex_t mutex, variable;
	int i,status;

	//INICIALIZACIÓN DE SEMAFOROS
	pthread_mutex_init(&mutex1,NULL);
	pthread_mutex_init(&mutex2,NULL);
	pthread_mutex_init(&s_escritor,NULL);
	pthread_mutex_init(&s_lector,NULL);

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
	extern pthread_mutex_t mutex2, s_escritor, s_lector;
	extern int global, n_lectores;
	int j;

	for(j=0;j<2;j++)
	{
		pthread_mutex_lock(&s_lector);//CON ESTE MUTEX NOS ASEGURAMOS DE QUE LOS LECTORES NO ENTRAN A MENOS QUE TODOS LOS ESCRITORES HAYAN SALIDO
		pthread_mutex_lock(&mutex2);
		n_lectores++;
		if(n_lectores==1)//SOY EL PRIMERO POR TANTO CIERRO EL ACCESO A LA VARIABLE
		{
			pthread_mutex_lock(&s_escritor); //SI NO SOY EL PRIMERO YA ESTA CERRADO
		}
		pthread_mutex_unlock(&mutex2);
		pthread_mutex_unlock(&s_lector);
		printf("Lector[%d] - El valor es %d\n",i,global);
		pthread_mutex_lock(&mutex2);
		n_lectores--;
		if(n_lectores==0)
		{
			pthread_mutex_unlock(&s_escritor); //AL SER EL ULTIMO EN SALIR DEJO ENTRAR A LOS ESCRITORES
		}
		pthread_mutex_unlock(&mutex2);
	}
}

void escritor(int i)
{
	extern pthread_mutex_t mutex1, s_escritor, s_lector;
	extern int global,n_escritores;
	int j, aux;

	for(j=0;j<M;j++)
	{
		pthread_mutex_lock(&mutex1);
		n_escritores++;
		if(n_escritores==1)
		{
			pthread_mutex_lock(&s_lector);//SI ES EL PRIMER ESCRITOR BLOQUEA A LOS LECTORES
		}
		pthread_mutex_unlock(&mutex1);

		pthread_mutex_lock(&s_escritor); //AQUI BLOQUEAMOS A LOS DEMAS ESCRITORES YA QUE LA ESCRITURA DEBE SER UNO A UNO
		aux=rand()%5;
		printf("Escritor[%d] - Numero creado: %d\n",i,aux);
		global=global+aux;
		pthread_mutex_unlock(&s_escritor);//DESBLOQUEAMOS ESCRITORES PARA QUE ENTRE OTRO

		pthread_mutex_lock(&mutex1);
		n_escritores--;
		if(n_escritores==0)
		{
			pthread_mutex_unlock(&s_lector);//SI ES EL ULTIMO ESCRITOR EL QUE SALE DEBE DAR ENTRADA A LOS LECTORES
		}
		pthread_mutex_unlock(&mutex1);
	}
}
