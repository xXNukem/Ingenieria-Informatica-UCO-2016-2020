/*Includes*/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

/*Semáforos*/

sem_t shombres;/*Controla a los hombres*/
sem_t smujeres;/*Controla a las mujeres*/
sem_t lavabo;/*Controla quien esta en el lavabo*/
sem_t cola;/*Controla la cola*/

/*Variables Globales*/

#define N_hombres 10
#define N_mujeres 10

int personas = 0;

/*Funciones*/

void *hombre();
void *mujer();

int main(int argc, char const *argv[])
{
	system("clear");
	printf("\n========== Lavabo UNISEX Planta 21 ==========\n");
	int i;

	pthread_t Personas[N_hombres + N_mujeres];

	sem_init(&shombres,0,1);
	sem_init(&smujeres,0,1);
	sem_init(&cola,0,1);
	sem_init(&lavabo,0,3);

	for(i=0;i<N_hombres;i++)
		pthread_create(&Personas[i],NULL,hombre,NULL);

	for(i=0;i<N_mujeres;i++)
		pthread_create(&Personas[i + N_hombres],NULL,mujer,NULL);

	for(i=0;i<N_hombres + N_mujeres;i++)
		pthread_join(Personas[i],NULL);

	return 0;
}

void *hombre()
{

	extern int personas;

	sem_wait(&cola);/*Esperamos a que haya gente en la Cola*/
	sem_wait(&shombres);/*Esperamos a que puedan entrar los hombres*/
	if(personas == 0)/*Si no hay nadie en el Lavabo*/
		sem_wait(&smujeres);/*Bloqueamos a las mujeres*/
		personas++;/*Aumentamos las personas*/
	sem_post(&shombres);/*Avisamos de que puede entrar los hombres*/
	sem_post(&cola);/*Avisamos de que puede avanzar la Cola*/

	/*Sección Crítica*/

	sem_wait(&lavabo);/*Controlamos el Lavabo*/
	printf("\033[0;34mUn hombre entra en el Lavabo\033[0m\n");/*Printf que avisa que entra un hombre en el lavabo*/
	sleep(2);/*Dormimos el proceso 2 Segundos, podeis ponerlo al gusto*/
	sem_post(&lavabo);/*Controlamos el Lavabo*/

	/*Sección Crítica*/

	sem_wait(&shombres);/*Vamos a quitar los hombres de la Lista*/
		personas--;/*Decrementamos las personas del Lavabo*/
		printf("\033[0;44mUn Hombre sale del Servicio\033[0m\n");/*Printf que avisa que sale un hombre en el lavabo*/
		if(personas == 0)/*Si no hay nadie en el Lavabo*/
			sem_post(&smujeres);/*Si no queda nadie avisamos a las mujeres*/
	sem_post(&shombres);/*Terminamos de controlar a las mujeres*/
}

void *mujer()
{
	extern int personas;

	sem_wait(&cola);/*Esperamos a que haya gente en la Cola*/
	sem_wait(&smujeres);/*Esperamos a que puedan entrar las mujeres*/
	if(personas == 0)/*Si no hay nadie en el Lavabo*/
		sem_wait(&shombres);/*Bloqueamos a los hombres*/
	personas++;/*Aumentamos las personas*/
	sem_post(&smujeres);/*Avisamos de que puede entrar las mujeres*/
	sem_post(&cola);/*Avisamos de que puede avanzar la Cola*/
	
	/*Sección Crítica*/

	sem_wait(&lavabo);/*Controlamos el Lavabo*/
		printf("\033[0;33mUna Mujer entra en el Lavabo\033[0m\n");/*Printf que avisa que entra una mujer en el lavabo*/
		sleep(2);/*Dormimos el proceso 2 Segundos, podeis ponerlo al gusto*/
	sem_post(&lavabo);/*Controlamos el lavabo*/

	/*Sección Crítica*/

	sem_wait(&smujeres);/*Vamos a quitar las mujeres de la Lista*/
		personas--;/*Decrementamos las personas del Lavabo*/
		printf("\033[0;43mUna Mujer sale del Servicio\033[0m\n");/*Printf que avisa que sale una mujer en el lavabo*/
		if(personas == 0)/*Si no hay nadie en el Lavabo*/
			sem_post(&shombres);/*Si no queda nadie avisamos a los Hombres*/
	sem_post(&smujeres);/*Terminamos de controlar a las mujeres*/
}
