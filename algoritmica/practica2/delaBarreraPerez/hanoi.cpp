/*! 
   \file  estadistica.cpp
   \brief Fichero que contiene las funciones de hanoi
*/

#include "hanoi.hpp"

int t1,t2,t3,i,maxdiscos;
int disko=0;
static int movimientos;

int torresHanoi(int discos)
{
	int movimiento=1;
		 if (discos == 1)
		 {
		  	return movimiento;
		 }
		 else 
		 {
		  	movimiento += torresHanoi(discos - 1) + torresHanoi(discos - 1);
		  	return movimiento;
		 }
}

void ejecutarHanoiTexto(int discos)
{
	t1=0;
	t2=0;
	t3=0;
	movimientos=0;
	
 	int cantDiscos, movimientos=0;

	 t1=discos;
	 maxdiscos = discos;

 		std::cout<<BIBLUE<<"TORRE: "<<RESET<<std::endl;
 		muestra();


 		movimientos = hanoi(discos, TORRE_INICIAL, TORRE_AUXILIAR, TORRE_FINAL);
 		std::cout<<BIGREEN<<"Movimientos totales: "<<BIYELLOW<<movimientos<<RESET<<std::endl;



}

void muestra()
{
		 std::cout<<BIBLUE<<"TORRE 1: "<<RESET;
		 for(int i=1;i<=t1;i++)
		 {
		        std::cout<<BIYELLOW<<disko;
		 }
		 std::cout<<std::endl;

		 std::cout<<BIBLUE<<"TORRE 2: "<<RESET;
		 for(int i=1;i<=t2;i++)
		 {
		       std::cout<<BIYELLOW<<disko;
		 }
		 std::cout<<std::endl;

		 std::cout<<BIBLUE<<"TORRE 3: "<<RESET;
		 for(int i=1;i<=t3;i++)
		 {
		        std::cout<<BIYELLOW<<disko;
		 }
		 std::cout<<std::endl;
}

int hanoi(int numDiscos, int torreInicial, int torreAuxiliar, int torreFinal)
{

    
 if(numDiscos == 1) // solo hay un disco
 {
 	
  	std::cout<<BIBLUE<<movimientos+1<<"-"<<"Mover disco de "<<BIYELLOW<<torreInicial<<BIBLUE<<" a "<<BIYELLOW<<torreFinal<<RESET<<std::endl;
  	movimientos++;
        if(torreInicial==1)
            t1--;
        if(torreInicial==2)
            t2--;
        if(torreInicial==3)
            t3--;
        if(torreFinal==1)
            t1++;
        if(torreFinal==2)
            t2++;
        if(torreFinal==3)
            t3++;
 
  muestra();
 }
 else // mas de un disco
 {

  hanoi(numDiscos - 1, torreInicial, torreFinal, torreAuxiliar);
  std::cout<<BIBLUE<<movimientos+1<<"-"<<"Mover disco de "<<BIYELLOW<<torreInicial<<BIBLUE<<" a "<<BIYELLOW<<torreFinal<<RESET<<std::endl;
  movimientos++;
 
        if(torreInicial==1)
            t1--;
        if(torreInicial==2)
            t2--;
        if(torreInicial==3)
            t3--;
        if(torreFinal==1)
            t1++;
        if(torreFinal==2)
            t2++;
        if(torreFinal==3)
            t3++;
 
  muestra();

  hanoi(numDiscos - 1, torreAuxiliar, torreInicial, torreFinal);
 }
 return movimientos;
}




/*
int torresHanoiTexto(int discos, int inicio, int fin, int aux)
{
	if(discos > 0)
	{
		torresHanoiTexto(discos-1,inicio,aux,fin);
		std::cout<<BIBLUE<<"El disco de la torre "<<BIYELLOW<<inicio<<BIBLUE<<" se mueve hasta la torre "<<BIYELLOW<<fin<<RESET<<std::endl;
		torresHanoiTexto(discos-1,aux,fin,inicio);
	}	
}
*/