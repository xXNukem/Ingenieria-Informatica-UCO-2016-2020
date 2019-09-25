//Ejercicio voluntario fumadoress !!

//Librerias nesesarias
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

//DEFINES

#define TIPOS 3 //cerillas-tabaco-papel
#define ITER 20 //iteraciones del fumador
#define ITERP 500 //Iteraciones del productor
#define F 3 //Numero de fumadores

//Variables glovales

int f[TIPOS][TIPOS];
int mesa[TIPOS];
char traducion[TIPOS][100]={"serillas","Papel","Tabaco"};
//Semaforos
pthread_mutex_t mutex,nesesidad,producido;


//Prototipos de funciones
void *fumador(void *id);
void *productor();
void cojerLoQueNesesito(int id);

//Programa principal
int main(){

	extern int f[TIPOS][TIPOS],mesa[TIPOS];
	 pthread_t hiloP[1];
	pthread_t hilosF[F];
	

	int i,id[F],status;


	// Inicializaci�n de variables
		//FUMADOR 0
		f[0][0]=0;f[0][1]=25;f[0][2]=25;
		//FUMADOR 1
		f[1][0]=25;f[1][1]=0;f[1][2]=25;
		//FUMADOR 2
		f[2][0]=25;f[2][1]=25;f[2][2]=0;
		//mesa
		mesa[0]=0;mesa[1]=0;mesa[2]=0;
	srand(time(NULL));

    // Create NHILOS threads

	//hilo productor
	if ((status = pthread_create(&hiloP[0], NULL, productor, NULL)))
	    exit(status);
    	
	

	for(i=0;i<F;i++){	
		id[i]=i;
		if ((status = pthread_create(&hilosF[i], NULL, fumador,(void *) &id[i])))
		    exit(status);
	}

    //esperar hasta finalizar el productor
  
	pthread_join(hiloP[0], NULL);

    
	//esperar hasta finalizar los hilos fumadores
	for (i = 0; i < F; i++) {
		pthread_join(hilosF[i], NULL);
    	}

	return (0);
}
//funcion para los fumadores
void *fumador(void *id){

		extern pthread_mutex_t mutex,nesesidad,producido;
	
	int *nombre,i,j,vez=0;
	nombre= (int *) id;

	printf("\nComienza el fumador %d",*nombre);
	for(i=0;i<ITER;i++){
		 pthread_mutex_lock(&producido); //Espera hasta que el productor haya producido algo
		//comprueba que es lo que nesesita y si nesesita algo lo coje
		cojerLoQueNesesito(*nombre);


		while(f[*nombre][0]>0 &&f[*nombre][1]>0 &&f[*nombre][2]>0){//fuma mientras tenga
			for(j=0;j<TIPOS;j++)//Gasta una unidad de cada cosa			
				f[*nombre][j]-=1;
			vez++;
			printf("\nEl fumador %d esta fumado %d",*nombre,vez);
					
		}
		//ha este punto solo se llega si no se tiene nada mas qu fumar
		//sleep(2);
		printf("\nElfumador %d nesesita coger cosas",*nombre);
			pthread_mutex_unlock(&nesesidad); //Espera hasta que el productor haya producido algo
		
			
	}
	

}
//funcion para el poductor
void *productor(){
	extern pthread_mutex_t mutex,nesesidad,producido;
	int i,tipo,U;	
	extern mesa[TIPOS];
	extern char traducion[TIPOS][100];
	//while(1==1)
	for(i=0;i<ITERP;i++){
		 pthread_mutex_lock(&nesesidad);//Espera ha que el productor nesesite algo
		 pthread_mutex_lock(&mutex);
			tipo=rand() %3;
			U=rand() %10;
			mesa[tipo]+=U;	
			printf("\nProductor produjo %s --> %d",traducion[tipo],U);
		pthread_mutex_unlock(&mutex);
		pthread_mutex_unlock(&producido);//Indica que ya hay nuevas cosas producidas
	}

}

//Esta funcion solo coje lo que el fumador nesesita
void cojerLoQueNesesito(int id){
	extern pthread_mutex_t mutex,producido;
		
	extern mesa[TIPOS],f[TIPOS][TIPOS];
	extern char traducion[TIPOS][100];	
	int j,cojido=0;
	 pthread_mutex_lock(&mutex);
		for(j=0;j<TIPOS;j++){
		
			if(f[id][j]==0){
					if(mesa[0]>0){
						f[id][j]=mesa[j];
						printf("\n\nEl Fumador %d cojio %d de %s ",id,mesa[j],traducion[j] );
						mesa[j]=0;
						cojido=1;
					}					
			}
		}
	pthread_mutex_unlock(&mutex);
	 
		
}

