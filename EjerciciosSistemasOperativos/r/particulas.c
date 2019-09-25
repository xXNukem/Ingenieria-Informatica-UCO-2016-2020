// PARTICULAS

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>

#define ELECTRONES 10
#define POSITRONES 10

sem_t mutexe,mutexp,electron,positron,vacio;
int ne = 0, np = 0;
void*Electron(void*p);
void*Positron(void*p);

int
main(void)
{
   extern sem_t mutexe, mutexp, electron, positron, vacio;
   int error, i;
   pthread_t elec[ELECTRONES], pos[POSITRONES];
   int ve[ELECTRONES], vp[POSITRONES];
   sem_init(&mutexe, 0, 5);
   sem_init(&mutexp, 0, 5);
   sem_init(&electron, 0, 1);
   sem_init(&positron, 0, 1);
   sem_init(&vacio, 0, 1);

   for(i = 0; i < ELECTRONES; i++)
   {
      ve[i] = i;

      if(error = pthread_create(&elec[i], NULL, Electron,
       (void*)&ve[i]))
         exit(error);
   }	
	
   for(i = 0; i < POSITRONES; i++)
   {
      vp[i] = i;

      if(error = pthread_create(&pos[i], NULL, Positron,
       (void*)&vp[i]))
         exit(error);

   }

   for(i = 0; i < ELECTRONES; i++)
      pthread_join(elec[i], NULL);
	
   for(i = 0; i < POSITRONES; i++)
      pthread_join(pos[i], NULL);

   return 0;
}

void*Electron(void*p)
{
   extern sem_t mutexe, electron, vacio;
   extern int ne;
   int *it;
   it = (int*)p;

   printf("Electron %d quiere entrar a la fiesta.\n", *it);
   sem_wait(&mutexe);
   sem_wait(&electron);
   ne++;

   if(ne == 1)
      sem_wait(&vacio);

   sem_post(&electron);

   printf("Electron %d esta en la fiesta.\n", *it);
   sleep(1);

   printf("Electron %d se aburre y se va.\n", *it);
   sem_wait(&electron);
   ne--;

   if(ne == 0)
      sem_post(&vacio);

   sem_post(&mutexe);
   sem_post(&electron);
}

void*Positron(void*p)
{
   extern sem_t mutexp, positron, vacio;
   extern int np;
   int *it;
   it = (int*)p;

   printf("Positron %d quiere entrar a la fiesta.\n", *it);
   sem_wait(&mutexp);
   sem_wait(&positron);
   np++;

   if(np == 1)
      sem_wait(&vacio);

   sem_post(&positron);

   printf("Positron %d esta dentro de la fiesta.\n", *it);
   sleep(1);

   printf("Positron %d se aburre y se va.\n", *it);
   sem_wait(&positron);
   np--;

   if(np == 0)
      sem_post(&vacio);

   sem_post(&mutexp);
   sem_post(&positron);
}
