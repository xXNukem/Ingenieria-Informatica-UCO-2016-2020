// PRODUCTORES-CONSUMIDORES
//
// 2) P productores y C consumidores.

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define ITER	5
#define FIN	-1
#define N	10
#define Ncons 2
#define Nprod 3
#define NHILOS (Nprod+Ncons)

//Buffer
double buffer[N];

// Semaforos
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
      *suma +=(dato= rand()%1001);
      sem_wait(&vacio);
      sem_wait(&mutex);
  
      //Entrar dato
      buffer[productor] = dato;
      productor = (productor + 1) % N;
  
      sem_post(&mutex);
      sem_post(&lleno);
  
      //Seccion residual
      printf("Productor[%d], valor: %d\n", *it, dato);
   }

   printf("\tProductor[%d], suma: %d\n", *it, *suma);
   pthread_exit ((void *) suma);
}

void *Consumidor(void * p)
{
   extern sem_t mutex, lleno, vacio;
   extern double buffer[N];
   extern int consumidor;
   int dato, *suma;
   int *it, i;
   it = (int *) p;
   suma = malloc(sizeof (int));
   *suma = 0;
  
   while(dato != FIN)
   {
      //Consume dato
      sem_wait(&lleno);
      sem_wait(&mutex);
  
      //Entrar dato
      dato = buffer[consumidor];
      consumidor = (consumidor + 1) % N;
      sem_post(&mutex);
      sem_post(&vacio);
  
      //Seccion residual
      printf("Consumidor[%d], valor: %d\n", *it, dato);
      *suma += dato;
   }

   *suma += 1.0;

   printf("\tConsumidor[%d], suma: %d\n", *it, *suma);
   pthread_exit((void *) suma);
}

main()
{
   extern sem_t mutex, lleno, vacio;
   void *Productor (void *), *Consumidor (void *);
   int status, i, v[Ncons + Nprod];
   pthread_t hilos[Ncons + Nprod];
   int *p_suma, *c_suma, p_total = 0, c_total = 0;
   extern int productor, consumidor;
   pthread_attr_t atributos;

   /* Fija la concurrencia inicial. */
   //thr_setconcurrency (NHILOS+1);
   pthread_attr_init (&atributos);

   /* Inicializa semaforos y variables globales. */
   sem_init (&mutex, 0, 1);
   sem_init (&lleno, 0, 0);
   sem_init (&vacio, 0, N);

   productor = consumidor = 0;
   srand(-time(NULL));

   /* Inicia los hilos. */
   for(i = 0; i < Nprod; i++)
   {
      v[i] = i;

      if(status = pthread_create(&hilos[i], &atributos, Productor,
       (void *) &v[i]))
         exit(status);
   }

   for(; i < Ncons + Nprod; i++)
   {
      v[i] = i - Nprod;

      if(status = pthread_create(&hilos[i], &atributos, Consumidor,
       (void *) &v[i]))
         exit (status);
   }

   /* Espera a que finalicen. */
   for(i = 0; i < Nprod; i++)
   {
      pthread_join(hilos[i], (void *) &p_suma);
      p_total += *p_suma;
   }

   /* Indica el fin a los consumidores. */
   for(i = 0; i < Ncons; i++)
   {
      sem_wait(&vacio);
      sem_wait(&mutex);
      buffer[productor] = FIN;
      productor = (productor + 1) % N;
      sem_post (&mutex);
      sem_post (&lleno);
   }

   /* Espera a que finalicen. */
   for(i = Nprod; i < Nprod + Ncons; i++)
   {
      pthread_join (hilos[i], (void *) &c_suma);
      c_total += *c_suma;
   }

   fprintf(stdout, "Suma de productores: %d\n", p_total);
   fprintf(stdout, "Suma de consumidores: %d\n", c_total);
}
