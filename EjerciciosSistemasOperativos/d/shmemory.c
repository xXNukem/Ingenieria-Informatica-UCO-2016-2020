#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>

#define ITER		10
#define CHILDREN	3

// The process finished correctly
#define Ok	7

int main()
{
    int i, shmid, status;
    key_t key;
    double *counter;
    void adder(int);
    struct shmid_ds buf;

    // Shared memory
    key = ftok("shmemory.c", 1);
    if ((shmid = shmget(key, sizeof(double), IPC_CREAT | 0777)/*Suma el IPC_CREAT y los permisos. Si existe la zona de memoria compartida, se accede a ella; sino la crea.*/) == -1)
	exit(1);

    counter = (double *) shmat(shmid, NULL, 0);/*Vincula puntero a la memoria compartida*/
    *counter = 0.0;

    // Run children
    for (i = 0; i < CHILDREN; i++) {
	if (!fork()) {/*Si soy el proceso hijo*/
	    adder(i);/*Llamo a la funcion adder*/
	    exit(0);
	}
    }

    // Wait to finish
    for (i = 0; i < CHILDREN; i++) {
	pid_t pid = wait(&status);
	printf("\nChild %d finished with status %d\n", pid, WEXITSTATUS(status));
    }/*Espero a que finalicen los hijos. WEXITSTATUS nos dice si el hijo ha finalizado correctamente*/

    // Final result
    fprintf(stdout, "Counter: %f\n", *counter);/*Valor del contador*/

    // Detach segment
    shmdt(counter);

    // Mark the segment to be destroyed
    shmctl(shmid, IPC_RMID, &buf);

    return 0;
}

void adder(int id)
{
    double x = 1.0, l;
    double *counter;
    int i, shmid;
    key_t key;

    // Shared memory
    key = ftok("shmemory.c", 1);
    if ((shmid = shmget(key, sizeof(double), 0)) == -1)
	perror("Child: ");
    counter = (double *) shmat(shmid, NULL, 0);

    for (i = 0; i < ITER; i++) {
	l = *counter;
	fprintf(stdout, "Process %d: %d \n", id, (int) *counter);
	l += x;
	*counter = l;
    }

    shmdt(counter);

    exit(Ok);
}

/*

Proceso padre y tres procesos hijos, con diez iteraciones cada uno. 

Uso de memoria compartida.

El orden de los procesos en la CPU no es en orden.

Contador compartido: cada proceso esta ejecutado en su orden y entra uno nuevo mientras que el anterior no se ha guardado, por lo tanto no se incrementa el contador cuando entra el nuevo proceso y se queda la cuenta anterior.
Para que se guarde hay que sincronizarlos.

IPC(Inter Process Comunication)
1-Semáforos: un semaforo con dos señales. Con una se puede entrar y con la otra no.
Cabecera: sys/sem.h
Creacion: semget()
Control terminacion: semctl()

2-Colas de mensajes: una cola; si tiene mensaje se puede entrar en la zona compartida, sino no.
Cabecera: sys/msg.h
Creacion: msgget()
Control terminacion: msgctl()

3-Memoria compartida: memoria dinamica, con un identificador unico.
Cabecera: sys/shm.h sys/ipc.h
Creacion: shmget()
Control terminacion: shmctl()

Pasos en memoria compartida:
1º)Obtener la clave. [ftok(ruta fichero,bit menos significativo)] Devuelve un key_t y genera la clave.
2º)Reservar memoria compartida. [shmget(clave key_t,tamaño,bandera)]
3º)Vincular puntero a memoria compartida. [shmat(id,localizacion de memoria,bandera)]
4º)Proceso hijo se desvincula de memoria compartida [shmdt(localizacion de memoria)]
5º)Elimino memoria compartida. [shmctl(id,argumento para codificar,estructura)]

*/
