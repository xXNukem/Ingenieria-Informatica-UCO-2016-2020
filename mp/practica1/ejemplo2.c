/* --------------------------------------
   Metodología de la Programacion   
   Ejemplo para usar el depurador gdb
      scanf dentro de una funcion  
   -------------------------------------*/

#include <stdio.h>

#define MAX 50

//Prototipos de funciones
void rellenaMatriz(int matriz[][MAX], int nfil, int ncol);

//Programa principal
int main(){
   int nfil, ncol;
   int matriz[MAX][MAX];
   int i,j;

   printf("Introduce el nº de filas: ");
   scanf("%d",&nfil);

   printf("Introduce el nº de columnas: ");
   scanf("%d",&ncol);   

   rellenaMatriz(matriz,nfil,ncol);
   
   return 0;
}

/* -------------------------------------------------
   Función que rellena una matriz
   Se le pasa: nfil -> nº filas
               ncol -> nº columnas
   Devuelve: matriz rellena
   Utiliza: nada
   -------------------------------------------------*/
void rellenaMatriz(int matriz[][MAX], int nfil, int ncol) {
   int i,j;

   for (i=0;i<nfil;i++){
      for (j=0;j<ncol;j++){
         printf("m[%d][%d]= ",i,j);
         scanf("%d",matriz[i][j]);
      }
   }
}
