#include <stdio.h>
#include <stdlib.h>
int **reservaMemoria(int **m, int nFil, int nCol);
int *reservaMemoriaV(int nFil);
void liberaMemoria(int**m, int nFil);
void liberarMemoriaV(int v);
void escribirMatriz(int **m, int nFil, int nCol);
void mostrarMatriz(int **m, int nFil, int nCol);
void maxFilas(int **m, int nFil, int nCol, int *max,int *v);
int main()
{
	int **m;
	int nFil, nCol; 
	int max;
	int *v;
		printf("escribe el numero de filas\n");
			scanf("%d", &nFil);
		printf("escribe el numero de columnas\n");
			scanf("%d", &nCol);
			m=reservaMemoria(m, nFil, nCol);
		printf("escribe la matriz");	
			escribirMatriz(m, nFil,nCol);
		printf("la matriz introducida es: \n");
			mostrarMatriz(m,nFil,nCol);
			v=reservaMemoriaV(nFil);
		printf("el minimo de los maximos de cada fila es\n");
			maxFilas(m, nFil, nCol, &max,v);
			printf("%d", max);
			liberarMemoriaV(v);
			liberaMemoria(m, nFil);
			



return (0);
}



//Matriz dinamica:
int **reservaMemoria(int **m, int nFil, int nCol)
{
	int i;

		m=(int**)malloc(nFil*sizeof(int*));
	
			for(i=0;i<nFil;i++)
			{
				m[i]=(int*)malloc(nCol*sizeof(int));
			}
		
return(m);
}

void liberaMemoria(int**m, int nFil)
{
	int i;
		for(i=0;i<nFil;i++)
		{
			free(m[i]);
		}
		free(*m);
}
//Vector dinamico
int *reservaMemoriaV(int nFil)
{
	return(int*)malloc(nFil*sizeof(int));
}

void liberarMemoriaV(int v)
{
	free(v);
}
//Funciones:


void escribirMatriz(int **m, int nFil, int nCol)
{

	int i, j;
	
	
		for(i=0;i<nFil;i++)
		{
			for(j=0;j<nCol;j++)
			{
				printf("M[%d][%d]\n",i,j);
				scanf("%d", &m[i][j]);
			}
		}
		

}

void mostrarMatriz(int **m, int nFil, int nCol)
{
	int i,j;
	
	
		
		for(i=0;i<nFil;i++)
		{
			
			for(j=0;j<nCol;j++)
			{
				printf("%d ", m[i][j]);
			}
		printf("\n");
		}
}


void maxFilas(int **m, int nFil, int nCol, int *max,int *v)
{

	int i, j,aux,aux2;
	
		for(i=0;i<nFil;i++)
		{
			aux=m[i][0];
			for(j=0;j<nCol;j++)
			{
				if(aux>m[i][j])
					v[i]=aux;
			}
		}
		aux2=v[0];
		for(i=0;i<nFil;i++)
		{
			if(aux2>v[i])
			*max=aux2;
		}
		
			
			
}
