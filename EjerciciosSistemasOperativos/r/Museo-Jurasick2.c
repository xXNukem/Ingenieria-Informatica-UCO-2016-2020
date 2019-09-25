#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

/* Soluci�n al problema de Parque Jur�sico. */

#define PLAZAS	2
#define VISITANTES 4
#define COCHES	6
#define CICLOS	3


sem_t s_visitante, s_coche, mutex;

int main ()
{

  pthread_t visi[VISITANTES], coche[COCHES];
  void *Coche (void *), *Visitante (void *);
  int i, v[VISITANTES];
  extern sem_t s_coche, s_visitante, mutex;
 
  srand (-time (NULL));
  
  /* Iniciar sem�foros. */
  sem_init (&s_coche, 0, 0);
  sem_init (&s_visitante, 0, 0);
	sem_init(&mutex, 0, 1);

  
  for (i=0; i<VISITANTES; i++)
    {
    v[i] = i;
    if (pthread_create (&visi[i], NULL, Visitante, &v[i]))
      exit (1);
      }
      
  for (i = 0; i < COCHES; i++)
    {
      v[i] = i;
      if (pthread_create (&coche[i], NULL, Coche, &v[i]))
	exit (1);
    }

  for (i=0; i<VISITANTES; i++)
    pthread_join (visi[i], NULL);
    
  /* Los coches finalizan cuando dejan de ser necesarios. 
  for (i = 0; i < COCHES; i++)
    pthread_join (coche[i], NULL); */

	return 0;
}


void *Visitante (void *p)
{
  int i, *index;
  extern sem_t s_coche, s_visitante, mutex;

  index = (int *)p;

  for (i = 0; i < CICLOS; i++)
    {
    
      /* Visitante en el museo. */
      fprintf (stdout, "Visitante %d en el museo\n", *index);
      sleep (rand()%5);

      /* Espera para dar un paseo en coche. */
      sem_post (&s_coche);
      sem_wait (&s_visitante);
     

      /* Paseo. */
      fprintf (stdout, "Visitante %d en el safari fotogr�fico\n", *index);
      sleep (rand() % 5);

      /* Libera el coche. */
      

    }

  

}

void *Coche (void *p)
{
  //int *index, paseos = 0;
  extern sem_t s_coche, s_visitante, mutex;

  //index = (int *) p;

  for (;;)
    {
      /* Espera a ser necesitado. */
	sem_wait(&mutex);
      sem_wait (&s_coche);      

      /* Espera a que haya dos viajeros. */
      sem_wait (&s_coche);
      
    //  paseos++;
      
      sem_post (&s_visitante);
      sem_post(&s_visitante);
	sem_post(&mutex);

      /* */
      
    }
}
