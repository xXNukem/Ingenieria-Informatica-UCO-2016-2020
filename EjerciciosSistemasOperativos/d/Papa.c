/* Problema de Papa Noel */

/*Librerias*/

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

/*Variables Globales*/

#define NR	9
#define NE 	6

int renos = 0;
int elfos = 0;


/*Semáforos*/

sem_t mutex;
sem_t ayuda_renos;
sem_t ayuda_elfos;
sem_t despertar_Papa;
sem_t ayudar;

/*Funciones*/

void *Papa();
void *Elfos();
void *Renos();

void prepararTrineo()	{ printf("Papa Noel está preparando el Trineo\n");}
void repartirRegalos()	{ printf("Papa Noel está repartiendo los Regalos\n");}
void recibirAyuda()		{ printf("Papa Noel está ayudando a los Elfos\n");}
void ListoRenos()		{ printf("Los Renos están Listos para repartir los Regalos\n");}

int main (int argc, char const *argv[]){

	system("clear");
	printf("\n========== Problema Santa Claus ==========\n");
	
	int i;
	pthread_t PapaNoel, Elfo[NE], Reno[NR];

	/*Inicializacion de los Semáforos*/

	sem_init(&mutex,0,1);
	sem_init(&ayuda_renos,0,0);
	sem_init(&ayuda_elfos,0,0);
	sem_init(&despertar_Papa,0,0);
	sem_init(&ayudar,0,1);

	/*Inicialización de los Procesos*/

	pthread_create(&PapaNoel,NULL,Papa,NULL);

	for(i=0; i<NE; i++)
		pthread_create(&Elfo[i],NULL,Elfos,NULL);

	for(i=0; i<NR; i++)
		pthread_create(&Reno[i],NULL,Renos,NULL);

	/*Esperamos a que terminen los Procesos*/

	pthread_join(PapaNoel,NULL);

	for(i=0; i<NE; i++)
		pthread_join(Elfo[i],NULL);

	for(i=0; i<NR; i++)
		pthread_join(Reno[i],NULL);

	return 0;
}

void *Papa(){
	extern int renos,elfos;

	sem_wait(&despertar_Papa); 					/*Esperamos a que alguien despierte a Papa Noel*/
	sem_wait(&mutex);							/*Entramos en Sección Crítica*/
	if(renos == 9){								/*Si han regresado todos los Renos*/
		renos == 0;								/*Ponemos el Contador a 0*/
		prepararTrineo();						/*Preparamos el Trineo*/
		sleep(2);								/*Preparar los Trineos lleva su tiempo*/
		sem_post(&ayuda_renos);					/*Avisamos de que podemos Ayudar a los Renos*/
		repartirRegalos();						/*Papa Noel reparte los regalos de Navidad*/
		sleep(2);								/*Repartir los Regalos lleva su tiempo*/
	}else 
		sem_post(&ayuda_elfos);					/*Ayudamos a los Elfos si los Renos no han llegado de Vacacciones*/
	sem_post(&mutex);							/*Salimos de las Sección Crítica*/		

	//pthread_exit(NULL);

}

void *Elfos(){
	extern int elfos;

	sem_wait(&ayudar);							/*Nos ponemos en cola de ayuda para que cuando termine de ayudar Papa nos ayude*/
	sem_wait(&mutex);							/*Entramos en Sección Crítica*/
		elfos++;								/*Aumentamos el numero de Elfos*/
		if(elfos == 3)							/*Si hay 3 elfos en Problemas*/
			sem_post(&despertar_Papa);			/*Despertamos a Papa Noel*/
		else
			sem_post(&ayudar);					/*Nos ponemos en cola de ayuda para que cuando termine de ayudar Papa nos ayude*/
	sem_post(&mutex);							/*Salimos de la Sección Crítica*/

	sem_wait(&ayuda_elfos);						/*Esperamos a que pueda ayudar a los Elfos*/
	recibirAyuda();								/*Recibe la Ayuda*/
	sleep(2);									/*Ayudar lleva su tiempo*/

	sem_wait(&mutex);							/*Volvemos a entrar en Sección Crítica*/
		elfos--;								/*Decrementamos los Elfos*/
		if(elfos == 0)							/*Si no hay ningun elfo en apuros*/
			sem_post(&ayudar);					/*Podemos ayudar al que está en Cola para ayudar*/
	sem_post(&mutex);							/*Salimos de la seccion Crítica*/

	//pthread_exit(NULL);

}
void *Renos(){
	extern int renos;

	sem_wait(&mutex);							/*Entramos en Sección Crítica*/
		renos++;								/*Aumentamos el número de Renos*/
		if(renos == 9)							/*Si estan todos los Renos disponibles*/
			sem_post(&despertar_Papa);			/*Despertamos a Papa Noel*/
	sem_post(&mutex);							/*Salimos de la Sección Crítica*/

	sem_wait(&ayuda_renos);						/*Esperamos a que pueda ayudar a los renos*/
	ListoRenos();								/*Avisamos de que estan listos los Renos*/

	//pthread_exit(NULL);
}
