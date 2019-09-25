//MUSEO

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

/* Solucion al problema de Parque Jur sico. */
#define PLAZAS	2
#define VISITANTES 5
#define COCHES	3
#define CICLOS	10

sem_t s_visitante, s_coche;

main()
{
   pthread_t visi[VISITANTES], coche[COCHES];
   void *Coche (void *), *Visitante (void *);
   int i, v[VISITANTES];
   extern sem_t s_coche, s_visitante;
   srand(-time(NULL));
   /* Iniciar sem foros. */
   sem_init (&s_coche, 0, 0);
   sem_init (&s_visitante, 0, 0);

   for(i = 0; i < VISITANTES; i++)
   {
      v[i] = i;

      if(pthread_create (&visi[i], NULL, Visitante,
            &v[i]))
         exit(1);
   }
      
   for(i = 0; i < COCHES; i++)
   {
      v[i] = i;

      if(pthread_create(&coche[i], NULL, Coche, &v[i]))
         exit(1);
   }

   for(i = 0; i < VISITANTES; i++)
      pthread_join(visi[i], NULL);
    
   /* Los coches finalizan cuando dejan de ser necesarios. 
   for (i = 0; i < COCHES; i++)
      pthread_join (coche[i], NULL); */
}

void *
Visitante (void *p)
{
   int i, *index;
   extern sem_t s_coche, s_visitante;
   index = (int *)p;

   for(i = 0; i < CICLOS; i++)
   {
      /* Visitante en el museo. */
      fprintf (stdout, "Visitante %d en el museo\n", *index);
      sleep(rand() % 5);

      /* Espera para dar un paseo en coche. */
      sem_post(&s_coche);
      sem_wait(&s_visitante);
     
      /* Paseo. */
      fprintf(stdout, "Visitante %d en el safari fotografico\n",
         *index);
      sleep(rand() % 5);

      /* Libera el coche. */
   }
}

void *
Coche (void *p)
{
   int *index, paseos = 0;
   extern sem_t s_coche, s_visitante;
   index = (int *) p;

   for(;;)
   {
      /* Espera a ser necesitado. */
      sem_wait (&s_coche);      

      /* Espera a que haya dos viajeros. */
      sem_wait (&s_coche);
      
      paseos++;
      sem_post(&s_visitante);
      sem_post(&s_visitante);
   }
}
