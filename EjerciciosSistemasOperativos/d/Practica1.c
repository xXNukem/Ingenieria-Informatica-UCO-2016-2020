/*1) Implementar un proceso padre que cree 3 hijos y luego espera a que finalicen antes de finalizar el mismo.
2) Los tres hijos comparten un vector de 100 enteros. Cada uno de ellos ha de realizar una de las siguientes tareas:
- Pedir un indice del vector y un valor entero por teclado y almacenar en la posicion correspondiente el valor leido. Esta operacion se ha de repetir 10 veces.
- Cambiar aleatoriamente un elemento del vector y bloquearse durante 1 segundo. Esta operacion se ha de repetir 100 veces.
- Sumar todos los elementos del vector, mostrar la suma por pantalla y luego bloquearse durante 30 segundos. Esta operacion se ha de repetir 5 veces.
3) El vector es inicialmente rellenado por el proceso padre con valores aleatorios.*/

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

#define CHILDREN	3

void hijo1();
void hijo2();
void hijo3();

int main()
{
	int i, shmid, status;
	key_t key;
	int *vector;
	struct shmid_ds buf;
	srand(time(NULL));

	// Reserva memoria compartida
	//2) Los tres hijos comparten un vector de 100 enteros. Cada uno de ellos ha de realizar una de las siguientes tareas:
	key = ftok("Practica1.c", 1);
	if ((shmid = shmget(key, sizeof(int)*100, IPC_CREAT | 0777)) == -1)
		exit(1);

	vector = (int *) shmat(shmid, NULL, 0);

	//3) El vector es inicialmente rellenado por el proceso padre con valores aleatorios.
	for(i=0;i<100;i++)
	{
		vector[i]=rand()%100;
	}
	
	//1) Implementar un proceso padre que cree 3 hijos y luego espera a que finalicen antes de finalizar el mismo.
	//Primer hijo
	//Pedir un indice del vector y un valor entero por teclado y almacenar en la posicion correspondiente el valor leido. Esta operacion se ha de repetir 10 veces.
	if (!fork()) 
	{
		hijo1();
		exit(0);
	}
	//Segundo hijo
	//Cambiar aleatoriamente un elemento del vector y bloquearse durante 1 segundo. Esta operacion se ha de repetir 100 veces.
	if(!fork())
	{
		hijo2();
		exit(0);
	}
	//Tercer hijo
	//Sumar todos los elementos del vector, mostrar la suma por pantalla y luego bloquearse durante 30 segundos. Esta operacion se ha de repetir 5 veces.
	if(!fork())
	{
		hijo3();
		exit(0);
	}
	
	// Wait to finish
	for (i = 0; i < CHILDREN; i++) {
		pid_t pid = wait(&status);
		printf("\nChild %d finished with status %d\n", pid, WEXITSTATUS(status));
	}
	/*printf("El vector final:\n");
	for(i=0;i<100;i++)
	{
		printf("%d ",vector[i]);
	}
	printf("\n");*/
	//Detach segment
	shmdt(vector);
	//Mark the segmet to be destroyed
	shmctl(shmid,IPC_RMID,&buf);

	return(0);
}

void hijo1()
{
	int i, shmid,indice=0,valor=0;
	key_t key;
	int *vector;
	struct shmid_ds buf;
	
	key = ftok("Practica1.c", 1);
	if ((shmid = shmget(key, sizeof(int)*100, 0)) == -1)
		exit(1);
	vector = (int *) shmat(shmid, NULL, 0);
	printf("Comienza hijo 1\n");
		for(i=0;i<10;i++)
		{
			printf("Introduce indice del vector [%d]\n",i);
			scanf("%d",&indice);
			printf("Introduce el valor del vector [%d]\n",i);
			scanf("%d",&valor);
			vector[indice]=valor;
		}
	shmdt(vector);
}

void hijo2()
{
	int i, shmid;
	key_t key;
	int *vector;
	struct shmid_ds buf;
	srand(time(NULL));
	
	key = ftok("Practica1.c", 1);
	if ((shmid = shmget(key, sizeof(int)*100, 0)) == -1)
		exit(1);
	vector = (int *) shmat(shmid, NULL, 0);
	
	printf("Comienza hijo 2\n");
	for(i=0;i<100;i++)
	{
		vector[rand()%100]=rand()%10;
		sleep(1);
	}
	shmdt(vector);
}

void hijo3()
{
	int i,j, shmid,suma=0;
	key_t key;
	int *vector;
	struct shmid_ds buf;

	key = ftok("Practica1.c", 1);
	if ((shmid = shmget(key, sizeof(int)*100, 0)) == -1)
		exit(1);
	vector = (int *) shmat(shmid, NULL, 0);
	
	printf("Comienza hijo 3\n");
	for(j=0;j<5;j++)
	{
		for(i=0;i<100;i++)
		{
			suma+=vector[i];	
		}
		printf("La suma es %d \n",suma);
		sleep(30);
		suma=0;
	}
	shmdt(vector);
}
