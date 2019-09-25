// PRODUCTORES-CONSUMIDORES
//
// 1) 1 proceso productor y 1 proceso consumidor.

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define N 15
#define fin -1
#define ITER 10

double buffer[N];
sem_t mutex, lleno, vacio;
int productor, consumidor;

void *Productor(void * p)
{
   extern sem_t mutex, lleno, vacio;
   extern double buffer[N];
   extern int productor;
   int dato, *suma;
   int *it, i;
   it = (int *) p;
   suma = malloc (sizeof (int));
   *suma = 0;

   for(i = 0; i < ITER; i++)
   {
      //Produce dato
      *suma +=(dato = rand() %1001);
      sem_wait(&vacio);
      sem_wait(&mutex);

      //Entrar dato
      buffer[productor]=dato;
      productor = (productor + 1) % N;
      sem_post(&mutex);
      sem_post(&lleno);
    
      printf("Productor[%d], valor: %d \n", *it, dato);
   }

   printf("Productor[%d], suma: %d \n", *it, *suma);
   pthread_exit ((void *) suma);
}

void *
Consumidor (void *p)
{
   extern sem_t mutex, lleno, vacio;
   extern double buffer[N];
   int *it;
   extern int consumidor;
   int dato = 0, *suma;
   it = (int *) p;
   suma = malloc (sizeof (int));
   *suma = 0;

   while(dato != fin)
   {
      sem_wait (&lleno);
      sem_wait (&mutex);

      //Sacar dato
      dato = buffer[consumidor];
      consumidor = (consumidor + 1) % N;
      sem_post (&mutex);
      sem_post (&vacio);

      // Consume dato
      printf("Consumidor[%d] Valor: %d\n", *it, dato);
      *suma += dato;
   }

   (*suma) ++;
   printf("Consumidor[%d] Suma: %d\n", *it, *suma);
   pthread_exit ((void *) suma);
}

int
main(void)
{
   extern sem_t mutex, lleno, vacio;
   void *Productor (void *), *Consumidor (void *);
   int status, v[2];
   pthread_t hilos[2];
   int *p_suma, *c_suma;
   extern int productor, consumidor;
   pthread_attr_t atributos;
   srand(-time(NULL));
  
   productor = consumidor = 0;

   /* Fija la concurrencia inicial. */
   pthread_attr_init(&atributos);

   /* Inicializa semaforos y variables globales. */
   sem_init(&mutex, 0, 1);
   sem_init (&lleno, 0, 0);
   sem_init (&vacio, 0, N);
   //Inicia los hilos
   v[0] = 0;

   if(status = pthread_create(&hilos[0], &atributos, Productor,
       (void *) &v[0]))
      exit(status);
	
   v[1] = 1;

   if(status = pthread_create(&hilos[1], &atributos, Consumidor,
       (void *) &v[1]))
      exit(status);

   //Espera a que finalice el productor
   pthread_join (hilos[0], (void *) &p_suma);
      
   //Termina consumidores
   sem_wait (&vacio);
   sem_wait (&mutex);
   buffer[productor] = fin;
   productor = (productor + 1) % N;
   sem_post (&mutex);
   sem_post (&lleno);
   pthread_join(hilos[1], (void *) &c_suma);

   fprintf (stdout, "Suma de productores: %d\n", *p_suma);
   fprintf (stdout, "Suma de consumidores: %d\n", *c_suma);

   return 0;
}
