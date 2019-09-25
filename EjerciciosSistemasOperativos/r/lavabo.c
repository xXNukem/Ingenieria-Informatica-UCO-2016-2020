#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

pthread_mutex_t mujeres = PTHREAD_MUTEX_INITIALIZER, hombres = PTHREAD_MUTEX_INITIALIZER, cruce = PTHREAD_MUTEX_INITIALIZER, mutex = PTHREAD_MUTEX_INITIALIZER, lavabo = PTHREAD_MUTEX_INITIALIZER;
int h = 0, m = 0, cruces = 0;

#define NH 5
#define NM 5
#define TOTAL ( NH + NM )

int aleatorio;
void cruzar();
void Hombre (int p);
void Mujer (int p);

int main(void)
{
    pthread_t babuinos[TOTAL];
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);
    void *proceso(void *);
    int i, j[TOTAL],status;
    extern int aleatorio;
	
	srand(time(NULL));
	aleatorio = (rand () % 10);
	//printf("aleatorio:%d",aleatorio);
   
    
	for(i=0;i<TOTAL;i++)
	{
		j[i] = i;
		if(status=pthread_create(&babuinos[i],&attributes,*proceso,&j[i]))
			exit(status);
	}
        
    for(i=0;i<TOTAL;i++)
        pthread_join(babuinos[i],NULL);
}

void *proceso(void *p)
{
	extern int aleatorio;
	extern int cruces;
	int i,*j;
	j = (int *) p;
	i = *j;
	
	
	while(cruces == 0)
	{
		if(aleatorio < 5)
		{
	
			 if(i < TOTAL / 2)
				Mujer(i);
			else	
				Hombre(i);
		
				cruces++;
		}
		else
		{
		
			if(i < TOTAL / 2)
				Hombre(i);
			else
				Mujer(i);
				
				cruces++;
		}
		
		
	}
}


void cruzar()
{
    sleep(1);
}


void Hombre (int p)
{
 	extern pthread_mutex_t hombres, lavabo, mutex;
	extern int h;

				        
 		 pthread_mutex_lock(&hombres);
                    h++;

                if(h == 1)
                    pthread_mutex_lock(&mutex);
                    
                                
            pthread_mutex_unlock(&hombres);
            

                if( h > 2  )
                    {
                    
                    		if (h == 3)
                    		;
                         	else
                         	 fprintf(stdout, "\nHombre:%d esta esperando a que salga hombre\n",p);
                         	 
                                 pthread_mutex_lock(&lavabo);
                    }  
                
                fprintf(stdout, "\n ====> Hombre[%d] entra lavabo\n",p);
                cruzar();
            
               
               pthread_mutex_unlock(&lavabo);
               
            pthread_mutex_lock(&hombres);
                h--;
                
                 fprintf(stdout,"\n\n<=====sale hombre:%d \n\n",p);
                 
                   
 
                if(h == 0)
                {	
                    fprintf(stdout,"\n\nSERVICIO LIBRE\n\n"); 
                    pthread_mutex_unlock(&mutex);
                }
       
            pthread_mutex_unlock(&hombres);
            
             
}
  

void Mujer (int p)
{
 	extern pthread_mutex_t mujeres, lavabo, mutex;
	extern int m;


	  pthread_mutex_lock(&mujeres);
                    m++;
                         
                if(m == 1)
                    pthread_mutex_lock(&mutex);
                  
                    
                      pthread_mutex_unlock(&mujeres);
                    
                    
                   
                if( m > 2  )
                    {
                    
                    		if (m == 3)
                    		;
                         	else
                         	 fprintf(stdout, "\nMujer:%d esta esperando a que salga mujer\n",p);
                         	 
                                 pthread_mutex_lock(&lavabo);
                    }  
                    
                    
                    fprintf(stdout, "\n ====> Mujer[%d] entra lavabo\n",p);
                cruzar();
                  
                      pthread_mutex_unlock(&lavabo);             
                   
            pthread_mutex_lock(&mujeres);
                m--;
                 fprintf(stdout,"\n\n<=======Sale mujer:%d \n\n",p);
                 
    
                   
                if(m == 0)
                {
                    fprintf(stdout,"\n\nSERVICIO LIBRE\n\n");
                    pthread_mutex_unlock(&mutex);
                }
                   
                
            pthread_mutex_unlock(&mujeres);
	
}
    
