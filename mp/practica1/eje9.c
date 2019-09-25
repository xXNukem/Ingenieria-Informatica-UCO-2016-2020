/*Implementa una función que responda al siguiente prototipo:  void dividir(char  *cadena, char  
*subcadena1, char *subcadena2, char caracter_separacion), que divida la cadena cadena en dos 
subcadenas, una con todos los caracteres hasta la primera aparición de caracter_separacion (sin 
incluir   dicho   carácter)   y   la   otra   con   todos   los   caracteres   a   partir   de  caracter_separacion 
(incluyendo dicho carácter). Por ejemplo, la cadena “esto es un ejemplo” quedaría dividida en las 
subcadenas “esto es ” y “un ejemplo”, si llamamos a la función con el carácter ‘u’ como carácter 
de separación */



#include <stdio.h>
#include <string.h>
void dividir(char *cadena, char *subcadena1, char *subcadena2, char caracter);

int main()
{
	char *cadena;
	char *subcadena1;
	char *subcadena2;
	char caracter;

		printf("introduce una cadena \n");
		gets(cadena);
		printf("introduce el caracter de separacion \n");
		scanf("%c", &caracter);
		
		dividir(&cadena,&subcadena1,&subcadena2,caracter);
		
		printf("las subcadenas son <%s >  y <%s > \n ", subcadena1, subcadena2);

return(0);

}



void dividir(char *cadena, char *subcadena1, char *subcadena2, char caracter)
{
	int i, j;
	
		for(i=0;cadena[i]!=caracter;i++)
		{
			subcadena1=cadena[i];
		}
		subcadena1[i]='\0';
		
		for(i=0,j=strlen(subcadena1);j<strlen(cadena);i++,j++)
		{
			subcadena2[i]=cadena[j];
		}
		subcadena2[i]='\0';
		
	

}

