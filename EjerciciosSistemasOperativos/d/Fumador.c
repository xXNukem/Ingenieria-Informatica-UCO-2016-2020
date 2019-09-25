/*Includes*/

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

/*Semáforos*/

sem_t Agente_Listo;/*Representa los Elementos de la Tabla*/
sem_t Productor_Mutex;/*Este Semáforo da al Productor acceso exclusivo a los elementos de la Mesa*/
sem_t Semaforo_Fumadores[3];/*Cada Semáforo Fumador representa cuando un fumador tiene los elementos Necesarios*/
sem_t Semaforo_Productor[3];/*Cada Productor produce un determinado tipo de elemento, gestiona estos con este semáforo*/

/*Variables Globales*/

char* Tipos_Fumador[3] = { "Cerillas", "Tabaco", "Papel" };/* Se trata de una matriz de cadenas que describe lo que necesita cada tipo de fumador*/
bool Elementos_Mesa[3] = { false, false, false };/*Esta lista representa los tipos de elementos que están en la mesa. Esto debería corresponde con los Tipos_Fumador, de manera que cada elemento es la que el fumador tiene. Así que el primer elemento sería papel y tabaco, a continuación, coincide*/

/*Funciones*/ 

/*Función fuma, maneja la espera de que necesitan del elemento y, a continuación,Fuman. Repita esto tres veces*/

void *Fumador(void* arg)
{

	int Fumador_id = *(int*) arg;
	int Tipo_id = Fumador_id % 3;
	int i;

	
	for (i = 0; i < 3; ++i)	/*Fuman 3 Fumadores*/			
	{
		printf("Fumador %d Espera para %s\n",Fumador_id, Tipos_Fumador[Tipo_id]);/*Mensaje que indica que fumador espera para los tipos de Ingredientes*/		
		sem_wait(&Semaforo_Fumadores[Tipo_id]);/*Espera a que la combinación correcta de elementos para estar en la mesa*/	
		printf("Fumador %d Se está haciendo un Cigarrillo\n", Fumador_id);/*Hace el cigarrillo antes de liberar el agente*/
		usleep(rand() % 50000);
		sem_post(&Agente_Listo);/*Avisamos de que el Agente está Listo*/
		/*Vamos a fumar...*/
		printf("Fumador %d Está Fumando\n", Fumador_id);
		usleep(rand() % 50000);
	}
	return NULL;
}

																		
/*El Productor es responsable de liberar el semáforo Fumador adecuado cuando el artículo correctos están en la mesa*/

void *Productor(void* arg)
{

	int Productor_id = *(int*) arg;
	int i;

	for (i = 0; i < 3; ++i)
	{
		sem_wait(&Semaforo_Productor[Productor_id]);/*Espera hasta que salga el producto Necesitado*/
		sem_wait(&Productor_Mutex);/*Entramos en Sección Crítica*/
		if (Elementos_Mesa[(Productor_id + 1) % 3])/*Comprueba si el otro elemento que necesitamos está en la mesa*/
		{
				Elementos_Mesa[(Productor_id + 1) % 3] = false;
				sem_post(&Semaforo_Fumadores[(Productor_id + 2) % 3]);
		}
		else if (Elementos_Mesa[(Productor_id + 2) % 3])
		{
				Elementos_Mesa[(Productor_id + 2) % 3] = false;
				sem_post(&Semaforo_Fumadores[(Productor_id + 1) % 3]);
		}
		else
		{
			Elementos_Mesa[Productor_id] = true;/*El otro elemento no está en la mesa todavía*/
		}		
		sem_post(&Productor_Mutex);/*Salimos de la Sección Crítica*/
	}
	return NULL;
}

/* El Agente pone los ingredientes en la Mesa*/

void *Agente(void* arg)
{

	int Agente_id = *(int*) arg;
	int i;

	for (i = 0; i < 3; ++i)
	{
		usleep(rand() % 200000);		
		sem_wait(&Agente_Listo);/*Espera a que un Fumador avise ha terminado con los elementos que ha ofrecido*/
		sem_post(&Semaforo_Productor[Agente_id]);/*Avisa de los Elementos que está dando el Agente*/
		sem_post(&Semaforo_Productor[(Agente_id + 1) % 3]);		
		printf("\033[0;35m==> \033[0;33mAgente %d está dando %s\033[0;0m\n",Agente_id, Tipos_Fumador[(Agente_id + 2) % 3]);	
	}
	return NULL;
}

/* Main */

int main(int argc, char* arvg[])
{
	
	srand(time(NULL));/*Semilla Para los números aleatorios que vamos a utilizar*/
	int i;

	/*Declaración de los IDs*/

	int Agente_IDs[3];
	int Productor_IDs[3];
	int Fumador_IDs[3];

	/*Inicialización de los Semáforos*/
	
	sem_init(&Agente_Listo, 0, 1);/*Sólo hay un semáforo agente ya que sólo un conjunto de artículos puede estar en la mesa en cualquier momento dado. A valores de 1 = nada en la mesa*/
	sem_init(&Productor_Mutex, 0, 1);

	for (i = 0; i < 3; ++i)
	{
		sem_init(&Semaforo_Fumadores[i], 0, 0);
		sem_init(&Semaforo_Productor[i], 0, 0);
	}

	/*Declaración de las Hebras*/

	pthread_t Hebra_Fumador[3];
	pthread_t Hebra_Productor[3];
	pthread_t Hebra_Agente[3];

	for (i = 0; i < 3; ++i)
	{
		Fumador_IDs[i] = i;

		if (pthread_create(&Hebra_Fumador[i], NULL, Fumador, &Fumador_IDs[i]) == EAGAIN)
		{
			perror("Insuficientes Recursos para crear la Hebra");
			return 0;
		}
	}
	
	for (i = 0; i < 3; ++i)
	{
		Productor_IDs[i] = i;
		if (pthread_create(&Hebra_Productor[i], NULL, Productor, &Productor_IDs[i]) == EAGAIN)
		{
			perror("Insuficientes Recursos para crear la Hebra");
			return 0;
		}
	}
	
	for (i = 0; i < 3; ++i)
	{
		Agente_IDs[i] =i;
		if (pthread_create(&Hebra_Agente[i], NULL, Agente, &Agente_IDs[i]) == EAGAIN)
		{
			perror("Insuficientes Recursos para crear la Hebra");
			return 0;
		}
	}

	/*Nos aseguramos de que terminan todos los procesos del Fumador*/

	for (i = 0; i < 3; ++i)
	{
		pthread_join(Hebra_Fumador[i], NULL);
	}
	return 0;
}
