/* --------------------------------------
   Metodología de la Programacion   
   Ejemplo para usar el depurador gdb
      Se nos olvida un & en el scanf   
   -------------------------------------*/

#include <stdio.h>

#define MAX 50

int main(){
   int nfil, ncol;
   int matriz[MAX][MAX];
   int i,j;

   printf("Introduce el nº de filas: ");
   scanf("%d",nfil);

   printf("Introduce el nº de columnas: ");
   scanf("%d",ncol);   

   for (i=0;i<nfil;i++){
      for (j=0;j<ncol;j++){
         printf("m[%d][%d]= ",i,j);
         scanf("%d",&matriz[i][j]);
      }
   }
   
   return 0;
}
