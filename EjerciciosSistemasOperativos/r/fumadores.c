#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

int papel = 0, tabaco = 0, cerillas = 0, var = 5;
pthread_mutex_t poner_papel = PTHREAD_MUTEX_INITIALIZER, poner_tabaco = PTHREAD_MUTEX_INITIALIZER, poner_cerillas = PTHREAD_MUTEX_INITIALIZER, variable = PTHREAD_MUTEX_INITIALIZER;
sem_t cliente, provehedor;

void fumar();

int main(void)
{
	int p0=0, p1=1, p2=2, i;
	extern sem_t cliente, proveedor;
	void *func_vender(void *), *func_fumar(void *);
	pthread_t vendedor, fumador[3];
	
	pthread_attr_t attributes;
	pthread_attr_init(&attributes);
	
	sem_init(&cliente,0,0);
	sem_init(&provehedor,0,0);
	
	srand(time(NULL));
	
	pthread_create(&vendedor,&attributes,func_vender,NULL);
	
	pthread_create(&fumador[0],&attributes,func_fumar,&p0);
	pthread_create(&fumador[1],&attributes,func_fumar,&p1);
	pthread_create(&fumador[2],&attributes,func_fumar,&p2);
	
	pthread_join(vendedor,NULL);
	for(i=0;i<3;i++)
	{
		pthread_join(fumador[i],NULL);
	}
}

void *func_vender(void *p)
{
	extern int papel, tabaco, cerillas, var;
	extern pthread_mutex_t poner_papel, poner_tabaco, poner_cerillas;
	extern sem_t cliente, provehedor;
	int opcion, cantidad;
	
	while(var >= 0)
	{
		sem_wait(&cliente);
		opcion = rand()%3 ;
		cantidad = (rand()%5) +1;
		
		switch(opcion)
		{
			case 0:
				pthread_mutex_lock(&poner_papel);
					papel += cantidad;
					fprintf(stdout, "El provehedor a puesto %d papeles sobre la mesa\n", papel);
				pthread_mutex_unlock(&poner_papel);
				break;
			case 1:
				pthread_mutex_lock(&poner_cerillas);
					cerillas += cantidad;
					fprintf(stdout, "El provehedor a puesto %d cerillas sobre la mesa\n", cerillas);
				pthread_mutex_unlock(&poner_cerillas);
				break;
			case 2:
				pthread_mutex_lock(&poner_tabaco);
					tabaco += cantidad;
					fprintf(stdout, "El provehedor a puesto %d tabacos sobre la mesa\n", tabaco);
				pthread_mutex_unlock(&poner_tabaco);
				break;
			default:
				puts("aqui no debe entrar");
		}	
		pthread_mutex_lock(&variable);
			var--;
		pthread_mutex_unlock(&variable);
		sem_post(&provehedor);
	}
}

void *func_fumar(void *p)
{
	extern int papel, tabaco, cerillas, var;
	extern pthread_mutex_t poner_papel, poner_tabaco, poner_cerillas;
	extern sem_t cliente, provehedor;
	int *i, num_papel, num_tabaco, num_cerillas;
	
	i = (int *) p;
	
	switch(*i)
	{
		case 0:
			num_papel = 50;
			num_tabaco = 50;
			num_cerillas = 0;
			break;
		case 1:
			num_papel = 50;
			num_tabaco = 0;
			num_cerillas = 50;
			break;
		case 2:
			num_papel = 0;
			num_tabaco = 50;
			num_cerillas = 50;
			break;
		default:
			puts("aqui no debe entrar");
	}
	
	while(1)
	{
		if(num_papel>=1 && num_tabaco>=5 && num_cerillas >=2)
		{
			num_papel--;
			num_tabaco -= 5;
			num_cerillas -= 2;
			fprintf(stdout,"El fumador %d esta fumandooooooo....%d\n",*i,num_papel);
			fumar();
		}
		else
		{
			sem_post(&cliente);
			sem_wait(&provehedor);
			if(num_papel < 1)
			{
				pthread_mutex_lock(&poner_papel);
					num_papel += papel;
					fprintf(stdout," El fumador %d esta repostando %d papeles y ahora tiene %d\n",*i,papel,num_papel);
					papel = 0;
				pthread_mutex_unlock(&poner_papel);
			}
			if(num_tabaco < 5)
			{
				pthread_mutex_lock(&poner_tabaco);
					num_tabaco += tabaco;
					fprintf(stdout," El fumador %d esta repostando %d tabacos y ahora tiene %d\n",*i,tabaco,num_tabaco);
					tabaco = 0;
				pthread_mutex_unlock(&poner_tabaco);
			}
			if(num_cerillas < 2)
			{
				pthread_mutex_lock(&poner_cerillas);
					num_cerillas += cerillas;
					fprintf(stdout," El fumador %d esta repostando %d cerillas y ahora tiene %d\n",*i,cerillas,num_cerillas);
					cerillas = 0;
				pthread_mutex_unlock(&poner_cerillas);
			}
		
		}
	}
}

void fumar()
{
	sleep(rand()%5);
}
