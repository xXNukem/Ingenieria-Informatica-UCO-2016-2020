#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define ITER 5
#define H 4
#define M 4

int sexo=0;//H->0;M->1 Vasio->-1
int L=0;//vacio por defecto
sem_t mutex;


void *mujer( void * id);
void *hombre( void * id);

int main(){

	extern sem_t mutex;
	pthread_t hilosH[H],hilosM[M];
	
	int hiloH[H],hiloM[M],i,status;
	sem_init(&mutex,0,1);
	for(i=0;i<H;i++)
	{
		hiloH[i]=i;
		if((status=pthread_create(&hilosH[i],NULL,hombre,(void *) &hiloH[i])))
		{
			exit(status);
		}	
	}
	for(i=0;i<M;i++)
	{
		hiloM[i]=i;
		if((status=pthread_create(&hilosM[i],NULL,mujer,(void *) &hiloM[i])))
		{
			exit(status);
		}	
	}

	for(i=0;i<H;i++)
	{
		pthread_join(hilosH[i],NULL);
		printf("El hombre %d termino\n",i);	

	}
	for(i=0;i<M;i++)
	{
		pthread_join(hilosM[i],NULL);
		printf("La mujer %d termino\n",i);	

	}
	return(0);
}


void *hombre( void * id){
	
	extern sem_t mutex;
	extern int sexo;
	int *ident,i=0,acabo=0;
	ident=(int *) id;
	do{//Otra oportunida miro luego
	sem_wait(&mutex);
		if((L==0 || L <3 ) && (sexo==0 || sexo ==-1)){
		
				printf("El hombre %d Entra al baño\n",*ident);
				L++;
				sexo=0;
				acabo=1;
		}else{
		printf("El hombre %d se da unavuelta por que esta lleno\n",*ident);
		
		}
		sem_post(&mutex);
		i++;
		sleep(2);
	}while(i<ITER && acabo==0);	
	//tiempo ke esta dentro
	sleep(2);

	if(acabo==1){
	//sale del baño
		sem_wait(&mutex);
			L--;//sale del lavabo
			if(L==0)
				sexo=-1;
			printf("El hombre %d ha salido\n",*ident);
		sem_post(&mutex);
	}
}
void *mujer( void * id){
	
	extern sem_t mutex;
	extern int sexo;
	int *ident,i=0,acabo=0;
	ident=(int *) id;
	do{//Otra oportunida miro luego
	sem_wait(&mutex);
		if((L==0 || L <3 ) && (sexo==1 || sexo ==-1)){
		
				printf("El mujer %d Entra al baño\n",*ident);
				L++;
				sexo=1;
				acabo=1;
		}else{
			printf("La mujer %d se da unavuelta por que esta lleno\n",*ident);
			
		}
	sem_post(&mutex);
	i++;
	sleep(2);
	}while(i<ITER && acabo==0);	
	//tiempo que esta dentro
	sleep(2);
	if(acabo==1){
	//sale del baño
		sem_wait(&mutex);
			L--;
			if(L==0)
				sexo=-1;
			printf("El mujer %d ha salido\n",*ident);
		sem_post(&mutex);
	}
}















