/*Includes*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>

/*Variables Globales*/

#define N 10

int contador = 0;

/*Semáforos*/

sem_t max_capacidad;	
sem_t sofa;
sem_t silla_barbero;
sem_t cliente_listo;
sem_t mutex1;
sem_t mutex2;
sem_t coord;
sem_t recibo;
sem_t dejar_silla_barbero;
sem_t pago;
sem_t terminado[N];



/*Declaraciones de Funciones*/

void cliente();
void barbero();
void Cajero();

void entrar_tienda()
{printf("Un cliente ha entrado en la tienda\n");}
void sentarse_sofa()
{printf("Un cliente se ha sentado en el sofa\n");}
void levantarse_sofa()
{printf("Un cliente se ha levantado del sofa\n");}
void poner_cola(int numero_cliente)
{printf("El cliente %d tiene el turno\n",numero_cliente);}
void levantarse_silla_barbero()
{printf("Un cliente se ha levantado de la silla del barbero\n");}
void salir_tienda()
{printf("Un cliente ha salido de la tienda\n");}
void sacar_cola(int numero_cliente)
{printf("El cliente %d ya no tiene el turno\n",numero_cliente);}
void cortar_pelo()
{printf("Un cliente se está cortando el pelo\n");}
void aceptar_pago()
{printf("Un cliente ha pagado su corte de pelo\n");}
void Pagar()
{printf("Un cliente está pagando\n");}

/*Main*/

int main(int argc, char const *argv[])
{
	pthread_t clientes[N],barberos[3];
	int i,status;

	/*Inicialización de los Semáforos*/
	sem_init(&max_capacidad,0,20);													
	sem_init(&sofa,0,4);
	sem_init(&silla_barbero,0,3);
	sem_init(&cliente_listo,0,0);
	sem_init(&mutex1,0,1);
	sem_init(&mutex2,0,1);
	sem_init(&coord,0,3);
	sem_init(&recibo,0,0);
	sem_init(&dejar_silla_barbero,0,0);
	sem_init(&pago,0,0);

	for (i = 0; i < N; ++i)
	{
		sem_init(&terminado[i],0,0);
	}

	/*Creación de Hilos*/
	for(i=0; i<N; i++)
	{
		status=pthread_create(&clientes[i],NULL,(void *)cliente,NULL);//Creacíón de los Hilos
		if(status!=0)
		{
			printf("Error al crear hilos Clientes\n");
			exit(-1);
		}
	}

	for(i=0; i<3; i++)
	{
		status=pthread_create(&barberos[i],NULL,(void *)barbero,NULL);//Creacíón de los Hilos
		if(status!=0)
		{
			printf("Error al crear hilos Barberos\n");
			exit(-1);
		}
	}

	/*Cerrando Hilos*/
	for(i=0;i<N;i++)
		pthread_join(clientes[i],NULL);//Creación de los Joins
	
	for(i=0;i<3;i++)
		pthread_join(barberos[i],NULL);//Creación de los Joins

	return 0;
}


/*Funciones*/

void cliente()
{

	int numero_cliente;
	extern int contador;

	while(1)
	{
		wait(&max_capacidad);//Espera a que pueda entrar en la tienda
		entrar_tienda();//Funcion de un printf realizada arriba
		sem_wait(&mutex1);//Entramos en sección crítica para poder asignar número a cada cliente
		contador++;//Aumenta los clientes
		numero_cliente=contador;//Asignamos un numero a cada cliente
		sem_post(&mutex1);//Salimos de la sección crítica
		sem_wait(&sofa);//Esperamos a que podamos sentarnos en el sofá
		sentarse_sofa();//Funcion de un printf realizada arriba
		sem_wait(&silla_barbero);//Esperamos a que podamos sentarnos en la silla del Barbero
		levantarse_sofa();//Funcion de un printf realizada arriba
		sem_post(&sofa);//Avisamos de que pueden sentarse más gente en el sofá
		sem_wait(&mutex2);//Entramos en sección crítica 2 para poder todos en orden
		poner_cola(numero_cliente);//Funcion de un printf realizada arriba
		sem_post(&cliente_listo);//El cliente está listo para ser pelado y despierta al Barbero
		sem_post(&mutex2);//Salimos de la sección crítica 2
		sem_wait(&terminado[numero_cliente]);//Esperamos a que el cliente haya terminado
		levantarse_silla_barbero();//Funcion de un printf realizada arriba
		sem_post(&dejar_silla_barbero);//Avisamos de que el cliente ya ha dejado la silla
		Pagar();//Funcion de un printf realizada arriba
		sem_post(&pago);//Avisamos de que hemos efectuado el pago
		sem_wait(&recibo);//Esperamos el recibo de la venta
		salir_tienda();//Funcion de un printf realizada arriba
		sem_post(&max_capacidad);//Avisamos de que hemos salido de la tienda

	}
}

void barbero()
{

	int cliente_b;

	while(1)
	{
		sem_wait(&cliente_listo);//Espera a que el cliente esté listo
		sem_wait(&mutex2);//Entramos en Sección Crítica 2 para poder quitar al cliente de la cola
		sacar_cola(cliente_b);//Funcion de un printf realizada arriba
		sem_post(&mutex2);//Salimos de la Sección Crítica 2
		sem_wait(&coord);//Esta es una sección Crítica para poder elegir si el Barbero Corta o Cobra en este caso Corta
		cortar_pelo();//Funcion de un printf realizada arriba
		sleep(2);//Cortar el pelo lleva su tiempo
		sem_post(&coord);//Salimos de esa secció Crítica
		sem_post(&terminado[cliente_b]);//Avisamos de que un cliente ya ha sido pelado
		sem_wait(&dejar_silla_barbero);//Avisamos de que hemos dejado la silla del Barbero
		sem_post(&silla_barbero);//Avisamos de que una silla del Barbero está lista
	}

}

void Cajero()
{
	while(1)
	{
		sem_wait(&pago);//Esperamos a que un Cliente quiera que sea cobrado
		sem_wait(&coord);//Esta es una sección Crítica para poder elegir si el Barbero Corta o Cobra en este caso Cobra
		aceptar_pago();//Funcion de un printf realizada arriba
		sem_post(&coord);//Salimos de esa secció Crítica	
		sem_post(&recibo);//Damos su recibo al cliente
	}
}


