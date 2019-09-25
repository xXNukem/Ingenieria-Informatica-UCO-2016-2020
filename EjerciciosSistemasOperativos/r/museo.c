#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


#define C 2
#define V 6 //multiplos de 3


int cocheActivo=-1,coches[C],funcionando=V;
sem_t semCoche[C],mutex,cola,visitante;


void *coche( void * id);
void *fvisitante();

int main(){
	extern sem_t semCoche[C],mutex,cola;
	
	int i,idC[C],status;
	sem_init(&mutex,0,1);
	sem_init(&cola,0,1);
	sem_init(&visitante,0,0);
	pthread_t hilosC[C],hilosV[V];
	for(i=0;i<C;i++)//inicializo semaforo de los coches
		sem_init(&semCoche[i],0,0);//cerrado pordefecto
	
	for(i=0;i<C;i++)
	{
		idC[i]=i;
		if((status=pthread_create(&hilosC[i],NULL,coche,(void *) &idC[i])))
		{
			exit(status);
		}	
	}
	for(i=0;i<V;i++)
	{
		
		if((status=pthread_create(&hilosV[i],NULL,fvisitante,NULL)))
		{
			exit(status);
		}	
	}

	for(i=0;i<V;i++)
	{
		pthread_join(hilosV[i],NULL);
		printf("El visitante %d termino\n",i);	

	}
	for(i=0;i<C;i++)
	{
		pthread_join(hilosC[i],NULL);
		printf("El coche %d termino\n",i);	

	}


	return(0);
}

void *coche( void * id){
	extern int cocheActivo,coches[C],funcionando;

	extern sem_t mutex,semCoche[C],cola,visitante;

	int *ident,f,n=0;
	ident=id;

	do{
		sem_wait(&cola);//Entro y me coloco el primero
			sem_wait(&mutex);
				cocheActivo=*ident;
				printf("El coche %d es coche activo\n",*ident);
			sem_post(&mutex);
			do{
				sem_wait(&visitante);
				sem_wait(&mutex);//este coche a salido a espera del siguiente
					
					n=coches[*ident];
					if(n==3)
						cocheActivo=-1;
					else
						sleep(1);
				sem_post(&mutex);
			}while(n<3);//Apartir de este puntolos visitantes estan dentro
				
		sem_post(&cola);//deja de ser el cohe activo
		printf("Los visitantes del coche %d estan paseando\n",*ident);
		sleep(5);//se pacean
	
		sem_post(&semCoche[*ident]);sem_post(&semCoche[*ident]);sem_post(&semCoche[*ident]);//libera a los vistantes
		coches[*ident]=0;
		printf("se bajan 3 visitantes del coche %d\n",*ident);
		sleep(5);
		sem_wait(&mutex); //este coche a salido a espera del siguiente
			f=funcionando;
			printf(" f-> %d\n",f);
		sem_post(&mutex);
	}while(f);//cuando no kede visitantes muere
	pthread_exit(NULL);

}
void *fvisitante(){

	extern int cocheActivo,coches[C],funcionando;

	extern sem_t mutex,semCoche[C],cola,visitante;
	int idC,n=0;
	do{
		sem_wait(&mutex);
			idC=cocheActivo;//mira quien es el coche activo
			if(idC!=-1){
				n=coches[idC];//mira qcuantos estan montados
				if(n<3){
					coches[idC]++;

				sem_post(&visitante);//aviso al coche de que me monte
				printf("Un vitante se monto en el coche %d\n",idC);

				}
			}
	

		sem_post(&mutex);
		sleep(2);
	}while(idC==-1 || n>=3);
		

	sem_wait(&semCoche[idC]);//esperando a bajar del coche

	sem_wait(&mutex);//se a salido del coche
		funcionando--;
	sem_post(&mutex);
	printf("Se bajo del coche %d\n",idC);
	pthread_exit(NULL);
}





