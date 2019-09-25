#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define N 2

typedef unsigned char BOOLEAN;
pthread_mutex_t Lec_Esc;
pthread_cond_t Listo_Leer,Listo_Escribir;
BOOLEAN Escribiendo=FALSE,ListoEscribir=FALSE;
int Lectores=0;
int bbdd=0;

main()
{
	int i,status;
	pthread_mutex_init (&Lec_Esc,NULL);
	pthread_cond_init (&Listo_Leer,NULL);
	pthread_cond_init (&Listo_Escribir,NULL);
	pthread_t lectores[N];
	pthread_t escritores[N];
	srand(time(NULL));
	void Lector();
	void Escritor();

	for(i=0;i<N;i++)
	{
		if((status=pthread_create(&lectores[i], NULL,(void *)Lector,(void *)i)))
		{
			exit(status);
		}
	}
	for(i=0;i<N;i++)
	{
		if((status=pthread_create(&escritores[i], NULL,(void *)Escritor,(void *)i)))
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

void Escritor()
{
	extern int bbdd;
	while(TRUE)
	{
		ListoEscribir=TRUE;
		if(Escribiendo || Lectores !=0)
		{
			pthread_cond_wait(&Listo_Escribir,&Lec_Esc);
		}
		Escribiendo=TRUE;
		bbdd=rand()%11;
		printf("Escribo %d en la base de datos\n",bbdd);
		Escribiendo=FALSE;
		ListoEscribir=FALSE;
		if(ListoEscribir==FALSE)
		{
			pthread_cond_signal(&Listo_Leer);	
		}
		else
		{
			pthread_cond_signal(&Listo_Escribir);
		}
	}
}
void Lector()
{
	extern int bbdd;
	while(TRUE)
	{
		if(Escribiendo || pthread_cond_signal(&Listo_Escribir))
		{
			pthread_cond_wait(&Listo_Leer,&Lec_Esc);
		}
		Lectores++;
		printf("Lee %d de la base de datos\n",bbdd);
		Lectores--;
		if(Lectores=0)
		{
			pthread_cond_signal(&Listo_Escribir);
		}
	}
}


