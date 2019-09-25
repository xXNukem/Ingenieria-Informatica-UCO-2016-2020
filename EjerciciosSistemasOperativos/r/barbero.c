#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include<sys/ipc.h>
#include<semaphore.h>
 
#define N 5
 
time_t end_time;/*Tiempo de finalizacion*/
sem_t mutex,customers,barbers;/*Usamos 3 semaforos*/
int count=0;/*Numero de clientes en espera para el corte de pelo*/
 
void barber(void *arg);
void customer(void *arg);
 
int main(int argc,char *argv[])
{
	pthread_t id1,id2;
	int status=0;
	end_time=time(NULL)+20;/*Barberia hora es 20s*/
 
	/*Inicializacion semaforos*/
	sem_init(&mutex,0,1);
	sem_init(&customers,0,0);
	sem_init(&barbers,0,1);
 
	/*Barbero_thread inicializacion*/
	status=pthread_create(&id1,NULL,(void *)barber,NULL);
	if(status!=0)
		perror("create barbers is failure!\n");
	/*CLiente_thread inicializacion*/
	status=pthread_create(&id2,NULL,(void *)customer,NULL);
	if(status!=0)
		perror("create customers is failure!\n");
 
	/*Cliente_thread PRIMER bloqueo*/
	pthread_join(id2,NULL);
	pthread_join(id1,NULL);
 
	exit(0);
}
 
void barber(void *arg)/*Proceso Barbero*/
{
	while(time(NULL)<end_time || count>0)
	{
		sem_wait(&customers);/*P(clientes)*/            
		sem_wait(&mutex);/*P(mutex)*/
		count--;
		printf("Barber:cut hair,count is:%d.\n",count);
		sem_post(&mutex);/*V(mutex)*/
		sem_post(&barbers);/*V(barbero)*/
		sleep(3);       
	}
}
 
void customer(void *arg)/*Proceso CLientes*/
{
	while(time(NULL)<end_time)
	{
		sem_wait(&mutex);/*P(mutex)*/
		if(count<N)
		{
			count++;
			printf("Customer:add count,count is:%d\n",count);
			sem_post(&mutex);/*V(mutex)*/
			sem_post(&customers);/*V(clientes)*/
			sem_wait(&barbers);/*P(barbero)*/
		}
		else
			/*V(mutex)*/
			/*Si el número está lleno de clientes, sólo hay que poner el candado mutex */
			sem_post(&mutex);
		sleep(1);
	}
}
