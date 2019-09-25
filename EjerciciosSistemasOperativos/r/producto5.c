// PRODUCTORES-CONSUMIDORES
//
// Todos los consumidores consument los ítems.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define N 10
#define ITER 100
#define C 3

int bufer[N], contador[N];

sem_t full[C], empty;
pthread_mutex_t ex_buf = PTHREAD_MUTEX_INITIALIZER,
  ex_cont = PTHREAD_MUTEX_INITIALIZER;

int
main(void)
{
   int i;
   extern sem_t full[C], empty;
   extern int contador[N];
   pthread_t consumidor[C], productor;
   int v[C];
   void *Productor (void *), *Consumidor (void *);
   pthread_attr_t atributos;

   /* Fija la concurrencia inicial. 
   thr_setconcurrency (C + 2);*/
   pthread_attr_init (&atributos);

   /* Inicialización de semáforos y variables globales. */
   sem_init (&empty, 0, N);

   for(i = 0; i < N; i++)
      contador[i] = 0;

   for(i = 0; i < C; i++)
      sem_init(&full[i], 0, 0);

   srandom(-time (NULL));

   /* Inicio de hilos. */
   pthread_create(&productor, &atributos, Productor, NULL);

   for(i = 0; i < C; i++)
   {
      v[i] = i;
      pthread_create(&consumidor[i], &atributos, Consumidor,
         &v[i]);
   }

   /* Espera fin de hilos. */
   pthread_join (productor, NULL);

   for(i = 0; i < C; i++)
      pthread_join (consumidor[i], NULL);
}

void *
Productor (void *p)
{
   int p_index = 0, item, i, j, suma = 0;
   extern sem_t full[C], empty;
   extern pthread_mutex_t ex_buf;
   extern int bufer[N];

   for(i = 0; i < ITER; i++)
   {
      /* Produce item. */
      suma += (item = random () % 100);
      sem_wait (&empty);
      pthread_mutex_lock (&ex_buf);
      bufer[p_index] = item;
      pthread_mutex_unlock (&ex_buf);

      for(j = 0; j < C; j++)
         sem_post (&full[j]);

      p_index = (p_index + 1) % N;
      fprintf (stdout, "Pro: Item %d\n", item);
   }

   fprintf (stdout, "Pro: Suma %d\n", suma);
}

void *
Consumidor (void *p)
{
   int c_index = 0, item, i, *index, suma = 0;
   extern sem_t full[C], empty;
   extern pthread_mutex_t ex_buf, ex_cont;
   extern int bufer[N], contador[N];
   index = (int *) p;

   for(i = 0; i < ITER; i++)
   {
      sem_wait (&full[*index]);
      pthread_mutex_lock (&ex_buf);
      item = bufer[c_index];
      pthread_mutex_unlock (&ex_buf);
      pthread_mutex_lock (&ex_cont);
      if(++contador[c_index] == C)
      {
         contador[c_index] = 0;
         sem_post (&empty);
      }

      pthread_mutex_unlock (&ex_cont);
      c_index = (c_index + 1) % N;
      suma += item;

      fprintf (stdout, "C%2d: Item %d\n", *index, item);
   }

   fprintf (stdout, "C%2d: Suma %d\n", *index, suma);
}
