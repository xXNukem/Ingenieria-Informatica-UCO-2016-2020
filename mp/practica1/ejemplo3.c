/* --------------------------------------
   Metodología de la Programacion   
   Ejemplo para usar el depurador gdb
      Nos salimos de rango  
   -------------------------------------*/

#include <stdio.h>

int main(){
   char cadena[15];   
   int i;
   char c;
   
   printf("Introduce una cadena: ");
   
   while((c=getchar())!='\n'){
      cadena[i]=c;
      i++;
   }
   cadena[i]='\0';

   printf("La cadena introducida es: %s\n",cadena);
   
   return 0;
}
