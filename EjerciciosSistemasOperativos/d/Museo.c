/* Problema del Museo de Ciencias */

/*Librerias*/

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>


/*Variables Globales*/

#define NC	2
#define NP 	12

int cocheActivo = -1;
int coches[NC];
int pasajeros_restantes = NP;


/*Semáforos*/

sem_t semCoche[NC];/*Controla los Coches del Recinto*/
sem_t mutex;/*Controla la Sección Crítica*/
sem_t cola;/*Controla la Cola de Pasajeros*/
sem_t visitante;/*Controla los pasajeros que entran en los coches*/

/*Funciones*/

void *Coche(void * id);
void *Visitante();

void cocheActivos(int i)
{ 
	printf("El Coche %d está Activo\n",i);
}
void PaseoCoche(int i)
{ 
	printf("Los visitantes del coche %d estan paseando\n",i);
}
void BajarCoche(int i)
{ 
	printf("Se bajan 3 visitantes del coche %d\n",i);
}
void SubirCoche(int i)
{ 
	printf("Un visitante se montó en el coche %d\n",i);
}

int main (int argc, char const *argv[]){

	system("clear");
	printf("\n========== Problema Museo de Ciencias ==========\n");
	
	int i,idC[NC];
	pthread_t Coches[NC], Visitantes[NP];

	/*Inicializacion de los Semáforos*/

	for(i=0; i<NC; i++)
	{
		sem_init(&semCoche[i],0,0);
	}
	sem_init(&mutex,0,1);
	sem_init(&cola,0,1);
	sem_init(&visitante,0,0);

	/*Inicialización de los Procesos*/

	for(i=0; i<NC; i++)
	{
		idC[i] = i;
		pthread_create(&Coches[i],NULL,Coche,&idC[i]);
	 }

	for(i=0; i<NP; i++)
	{
		pthread_create(&Visitantes[i],NULL,Visitante,NULL);
	}

	/*Esperamos a que terminen los Procesos*/

	for(i=0; i<NC; i++)
	{
		pthread_join(Coches[i],NULL);
	}
	for(i=0; i<NP; i++)
	{
		pthread_join(Visitantes[i],NULL);
	}
	return 0;
}

void *Coche(void * id)
{
	extern int cocheActivo,coches[NC],pasajeros_restantes;/*Llamamos a la variables externas*/

	int *idem, n = 0,f;/*Declaramos las variables que nos hagan falta en este caso un identificador llamado idem, n que sería el numero de plazas y f*/														
	idem = id;/*Le Pasamos el identificador del Coche a la Variable*/

	do
	{
		sem_wait(&cola);/*Me coloco en la Cola*/
			sem_wait(&mutex);/*Entro en Sección Crítica (Entramos para asignar un identificador al coche) */
				cocheActivo = *idem;/*El coche Activo será el que este referenciado por el Identificador*/
				cocheActivos(*idem);/*Función printf*/
			sem_post(&mutex);/*Salimos de la Sección Crítica*/
			do
			{
				sem_wait(&visitante);/*Esperamos a que puedan entrar los visitantes en el Coche*/
				sem_wait(&mutex);/*Entramos en la Sección Crítica*/

					n = coches[*idem];/*El valor del vector coches con el Identificador es el numero de pasajeros que hay en el Coche*/
					if (n == 3)/*Si hay 3 pasajeros en el Coche (Si está lleno)*/
						cocheActivo = -1;/*El coche está lleno y ya no está activo*/
					else
						sleep(1);/*Si no Espera a que se llene*/
				sem_post(&mutex);/*Salimos de la Sección Crítica*/
			} while(n < 3);/*Todo eso se va a hacer (Mientras no esté el coche lleno)*/

		sem_post(&cola);/*Aviso a la Cola de que pueden pasar*/
		PaseoCoche(*idem);/*El Coche pasea*/
		sleep(5);

		sem_post(&semCoche[*idem]); sem_post(&semCoche[*idem]); sem_post(&semCoche[*idem]);/*Liberamos a los Pasajeros del coche (Avisamos de que ya ha termiando el trayecto)*/
		coches[*idem] = 0;/*El valor de la Capacidad del Coche es 0 (Queda el coche vacio)*/
		BajarCoche(*idem);/*Funcion Printf*/
		sleep(5);/*Bajar del Coche tarda*/

		sem_wait(&mutex);/*Entramos de nuevo en sección Crítica (Para asignar los pasajeros restantes a f)*/
			f = pasajeros_restantes;/*Le asignamos el valor de pasajeros-restantes a f*/
			printf("Pasajeros restantes -> %d\n",f);/*Imprimimos el valor de f a modo de depuración*/
		sem_post(&mutex);/*Salimos de la Sección Crítica*/

	}while(f);/*Todo esto se va a cumplir mientras EXISTAN pasajeros en cola*/
}

void *Visitante()
{

	extern int cocheActivo, coches[NC], pasajeros_restantes;/*Llamamos a la variables externas*/

	int idC, n=0;

	do
	{
		sem_wait(&mutex);/*Entramos en Sección Crítica (Para asignar el valor del coche del identificador a Coche Activo)*/
			idC = cocheActivo;/*Mira quien es el coche Activo*/
			if( idC != -1)/*Si el coche está disponible*/
			{
				n = coches [idC];/*Comprueba cuantos pasajeros están montados en el Coche*/ 															
				if(n<3)
				{/*Si no se ha llenado el coche y hay gente esperando...*/
					coches[idC]++;/*Metemos un pasajeros más en el coche*/
					sem_post(&visitante);/*Avisamos de que pueden entrar al coche*/
					SubirCoche(idC);/*Funcion printf que avisa de que se suben pasajeros al coche que está identificado*/
				}
			}
		sem_post(&mutex);/*Salimos de la Sección Crítica*/
		sleep(2);													
	}while( idC == -1 || n>=3);/*Todo esto se hace mientras haya un coche no disponible o si el numero de pasajeros es mayor o igual que 3*/
	sem_wait(&semCoche[idC]);/*Esperamos a que podamos bajar del Coche*/														
	sem_wait(&mutex);/*Entramos en Seccion Crítica (Para eliminar los pasajeros restantes que hayan sido guiados por el recinto)*/
		pasajeros_restantes--;/*Decrementamos los pasajeros restantes que ya han visto el jardín botánico*/
		printf("Se bajó del Coche %d\n",idC);/*Printf que indica que un pasajero se bajó del coche*/
	sem_post(&mutex);/*Salimos de la Sección Crítica*/

}
