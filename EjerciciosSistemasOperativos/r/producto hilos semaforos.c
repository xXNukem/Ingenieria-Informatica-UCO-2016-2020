/* Productor/Consumidor con semaforos e hilos.  */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define ITER	100
#define FIN	-1
#define N	10
#define Ncons 2
#define Nprod 4
#define NHILOS (Nprod+Ncons)

/* Bufer compartido. */
double bufer[N];

/* Semaforos. */
sem_t mutex, full, empty;
int p_index, c_index;


main ()
{
  extern sem_t mutex, full, empty;
  void *Productor (void *), *Consumidor (void *);
  int status, i, v[Ncons + Nprod];
  pthread_t hilos[Ncons + Nprod];
  double *p_suma, *c_suma, p_total = 0., c_total = 0.;
  extern int p_index, c_index;
  pthread_attr_t atributos;

  /* Fija la concurrencia inicial. */
  //thr_setconcurrency (NHILOS+1);
  pthread_attr_init (&atributos);

  /* Inicializa semaforos y variables globales. */
  sem_init (&mutex, 0, 1);
  sem_init (&full, 0, 0);
  sem_init (&empty, 0, N);

  p_index = c_index = 0;
  srand (-time(NULL));

  /* Inicia los hilos. */
  for (i = 0; i < Nprod; i++)
    {
      v[i] = i;
      if (status =
	  pthread_create (&hilos[i], &atributos, Productor, (void *) &v[i]))
	exit (status);
    }
  for (; i < Ncons + Nprod; i++)
    {
      v[i] = i - Nprod;
      if (status =
	  pthread_create (&hilos[i], &atributos, Consumidor, (void *) &v[i]))
	exit (status);
    }

  /* Espera a que finalicen. */
  for (i = 0; i < Nprod; i++)
    {
      pthread_join (hilos[i], (void *) &p_suma);
      p_total += *p_suma;
    }

  /* Indica el fin a los consumidores. */
  for (i = 0; i < Ncons; i++)
    {
      sem_wait (&empty);
      sem_wait (&mutex);

      bufer[p_index] = FIN;
      p_index = (p_index + 1) % N;

      sem_post (&mutex);
      sem_post (&full);
    }

  /* Espera a que finalicen. */
  for (i = Nprod; i < Nprod + Ncons; i++)
    {
      pthread_join (hilos[i], (void *) &c_suma);
      c_total += *c_suma;
    }

  fprintf (stdout, "Suma de productores: %f\n", p_total);
  fprintf (stdout, "Suma de consumidores: %f\n", c_total);
}


void *
Productor (void *p)
{
  extern sem_t mutex, full, empty;
  extern double bufer[N];
  int *it, i;
  extern int p_index;
  double valor, *suma;

  it = (int *) p;

  suma = malloc (sizeof (double));
  *suma = 0.0;

  for (i = 0; i < ITER; i++)
    {
      /* Producir item */
      *suma += (valor = (double) (rand () % 1000));

      sem_wait (&empty);
      sem_wait (&mutex);

      bufer[p_index] = valor;
      p_index = (p_index + 1) % N;

      sem_post (&mutex);
      sem_post (&full);

      fprintf (stdout, "P(%d): %f\n", *it, valor);

    }

  fprintf (stdout, "P(%d) Suma: %f\n", *it, *suma);
  pthread_exit ((void *) suma);
}

void *
Consumidor (void *p)
{
  extern sem_t mutex, full, empty;
  extern double bufer[N];
  int *it;
  extern int c_index;
  double valor = 0, *suma;

  it = (int *) p;

  suma = malloc (sizeof (double));
  *suma = 0.0;

  while (valor != FIN)
    {
      sem_wait (&full);
      sem_wait (&mutex);

      valor = bufer[c_index];
      c_index = (c_index + 1) % N;

      sem_post (&mutex);
      sem_post (&empty);

      /* Consumir item. */
      fprintf (stdout, "C(%d): %f\n", *it, valor);
      *suma += valor;
    }

  *suma += 1.0;
  fprintf (stdout, "C(%d) Suma: %f\n", *it, *suma);
  pthread_exit ((void *) suma);
}
