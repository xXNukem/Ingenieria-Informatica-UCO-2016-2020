// BABUINOS

#include <stdio.h>    // La función printf() requiere stdio.h
#include <stdlib.h>   // La función random() requiere stdlib.h
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>

#define BIZQ 2
#define BDER 2

sem_t mutex,izq,der;
void* BabuinoIzq(void*);
void* BabuinoDer(void*);

int
main(void)
{
   extern sem_t mutex, izq,der;
   sem_init(&mutex, 0, 1);
   sem_init(&izq, 0, 1);
   sem_init(&der, 0, 1);
   int i = 0, j = 0, sw = 0, bi[BIZQ], bd[BDER];
   pthread_t babi[BIZQ], babd[BDER];

   for(i = 0; i < BIZQ; i++)
   {
      bi[i] = i;
      sw = pthread_create(&babi[i], NULL, BabuinoIzq,(void*)&bi[i]);

      // Si "sw" es distinto de cero, el programa finaliza.
      if(sw != 0)
         exit(sw);
   }
	
   for(j = 0; j < BDER; j++)
   {
      bd[j] = j;
      sw = pthread_create(&babd[j], NULL, BabuinoDer,(void*)&bd[j]);

      // Si "sw" es distinto de cero, el programa finaliza.
      if(sw != 0)
         exit(sw);
   }
	
   for(i = 0; i < BIZQ; i++) pthread_join(babi[i], NULL);

   printf("\n\t Han cruzado todos los babuinos del lado izquierdo. \n");
	
   for(j = 0; j < BDER; j++) pthread_join(babd[j], NULL);

   printf("\n\t Han cruzado todos los babuinos del lado derecho.\n\n");

   // Devuelve 0, si el programa ha finalizado correctamente.
   return 0;
}

void*
BabuinoIzq(void*p)
{
   int ni = 0;
   int g;
   g = *((int*)p);
   sleep(random() % 3); // ¡¡OJO !!
   sem_wait(&izq);
   ni++;

   if(ni == 1)
      sem_wait(&mutex);

   printf("\n\t BABUINO IZQUIERDO <<%d>> VA A PASAR.", g);
   printf("\n\t BABUINO IZQUIERDO <<%d>> ESTA CRUZANDO EL PUENTE.", g);

   sem_post(&izq);
   ni--;

   printf("\n\t BABUINO IZQUIERDO <<%d>> SE A PASADO AL OTRO LADO. \n", g);

   if(ni == 0);
      sem_post(&mutex);

   sem_post(&izq);
}// ¡¡OJO !!

void*
BabuinoDer(void*p)
{
   int m;
   //extern int nd;
   m = *((int*)p);
   sleep(random() % 3);
   sem_wait(&der);
   //nd++;	
   //if(ni==1);
   sem_wait(&mutex);
	
   printf("\n\t BABUINO DERECHO <<%d>> VA A PASAR.", m);
   sem_post(&der);
   printf("\n\t BABUINO DERECHO <<%d>> ESTA CRUZANDO EL PUENTE.", m);
   sem_wait(&der);
   //nd--;

   printf("\n\t BABUINO DERECHO <<%d>> SE A PASADO AL OTRO LADO. \n", m);
   //if(nd==0)
      sem_post(&mutex);

   sem_post(&der);
} // ¡¡OJO !!
