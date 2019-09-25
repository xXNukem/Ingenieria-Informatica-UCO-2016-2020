//Declaración de estructuras
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

typedef struct{
	int valor;
}SEMAFORO;

typedef struct{
	int papel;
	int tabaco;
	int cerillas;
}fumador;

#define N 3

//Declaracion de semaforos

sem_t proveedor; //Semáforo para bloquear al proveedor
sem_t fum[N]; //Semáforo para bloquear a los fumadores
sem_t material; //Semáforo para controlar los materiales que da el proveedor

//Declaración de fumadores
fumador fumadores[N];

int tabaco=0,papel=0,cerillas=0; //Estas son las unidades que irá creando el proveedor

main()
{
	int i,v[N];
	sem_init(&proveedor,0,0); //Inicializamos el proveedor como cerrado, ya el fumador lo abrirá cuando lo necesite
	sem_init(&material,0,1); //Ya que en el proveedor tenemos un wait y en los fumadores también, debe ir a 1
	void proveedores();
	void Fumador(void *);
	pthread_t fuma[N];
	pthread_t prov;
	srand(time(NULL));

	for(i=0;i<N;i++)
	{
		sem_init(&fum[i],0,1);
	}

	fumadores[0].papel=25;
	fumadores[0].tabaco=25;

	fumadores[1].cerillas=25;
	fumadores[1].tabaco=25;

	fumadores[2].cerillas=25;
	fumadores[2].papel=25;

	for(i=0;i<3;i++)
	{
		v[i]=i;
		pthread_create(&fuma[i],NULL,(void *)Fumador,(void *)&v[i]);
	}

	pthread_create(&prov,NULL,(void *)proveedores,NULL);

	for(i=0;i<3;i++)
	{
		pthread_join(fuma[i],NULL);
	}

	pthread_join(prov,NULL);
}

void proveedores()
{
	extern int tabaco, papel, cerillas; 
	extern sem_t proveedor;
	extern sem_t fum[N];
	extern sem_t material;
	int cantidad,i,x; //Este valor almacenará el aleatorio que vamos generando

	for(x=0;x<5;x++)
	{
		sem_wait(&proveedor); //Dormimos al proveedor
		switch(rand()%3)//Generamos un numero aleatorio que nos sirve para entrar en el switch
		{
			case 0:
				//Generar Tabaco
				sem_wait(&material);
				cantidad = rand()%10;
				tabaco += cantidad;
				printf("Se ha generado %d tabaco. Total tabaco: %d\n",cantidad,tabaco);
				sem_post(&material);
			case 1:
				//Generar papel
				sem_wait(&material);
				cantidad = rand()%10;
				papel += cantidad;
				printf("Se ha generado %d papel. Total papel: %d\n",cantidad,papel);
				sem_post(&material);

			case 2:
				//Generar cerillas
				sem_wait(&material);
				cantidad = rand()%10;
				cerillas += cantidad;
				printf("Se ha generado %d cerillas. Total cerillas: %d\n",cantidad,cerillas);
				sem_post(&material);
		}
		for(i=0;i<3;i++)
		{
			sem_post(&fum[i]); //Avisamos a los fumadores
		}
	}
}

void Fumador(void *id)
{
	int *i,x;
	extern sem_t proveedor;
	extern sem_t fum[N];
	extern int tabaco, papel, cerillas;
	i = (int *)id;

	for(x=0;x<5;x++)
	{
		if(fumadores[*i].papel*fumadores[*i].tabaco*fumadores[*i].cerillas>0) //Entonces quiere decir que tengo al menos 1 de cada
		{
			printf("El fumador %d fuma\n",*i);
			/*fumadores[*ì].papel=fumadores[*ì].papel-1;
			fumadores[*ì].tabaco=fumadores[*ì].tabaco-1;
			fumadores[*ì].cerillas=fumadores[*ì].cerillas-1;*/
		}
		else
		{ //El fumador necesita al menos 1
			sem_post(&proveedor);
			sem_wait(&fum[*i]);
			sem_wait(&material);
			if(tabaco!=0 && fumadores[*i].tabaco==0)
			{
				printf("El fumador va a coger %d tabaco\n",tabaco);
				fumadores[*i].tabaco=tabaco;
				tabaco=0;
			}

			if(cerillas!=0 && fumadores[*i].cerillas==0)
			{
				printf("El fumador va a coger %d cerillas\n",cerillas);
				fumadores[*i].cerillas=cerillas;
				cerillas=0;
			}

			if(papel!=0 && fumadores[*i].papel==0)
			{
				printf("El fumador va a coger %d papel\n",papel);
				fumadores[*i].papel=papel;
				papel=0;
			}
			sem_post(&material);
			sem_post(&fum[*i]);
		}
	}
}
