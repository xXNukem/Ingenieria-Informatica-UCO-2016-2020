/*********************************************************************
 * File  : PerceptronMulticapa.cpp
 * Date  : 2018
 *********************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <limits>
#include <math.h>

#include "PerceptronMulticapa.h"
#include "util.h"

using namespace imc;
using namespace std;
using namespace util;


// ------------------------------
// CONSTRUCTOR: Dar valor por defecto a todos los parámetros (dEta, dMu, dValidacion y dDecremento)
PerceptronMulticapa::PerceptronMulticapa(){
		dEta = 0.7;
		dMu = 1.0;
		nNumCapas = 3;
		bOnline = false;

}

// ------------------------------
// Reservar memoria para las estructuras de datos
// nl tiene el numero de capas y npl es un vector que contiene el número de neuronas por cada una de las capas
// tipo contiene el tipo de la ultima capa (0 => sigmoide, 1 => softmax)
// Rellenar vector Capa* pCapas
void PerceptronMulticapa::inicializar(int nl, int npl[], bool tipo) {
	nNumCapas = nl;
	//Reservamos memoria para el vector que tendra las capas.
	pCapas = (Capa *)calloc(nl,sizeof(Capa));
	//Primera capa con el numero de neuronas y su reserva de memoria, es la unica que no dispondra de sesgo.
	pCapas[0].nNumNeuronas = npl[0];
	pCapas[0].pNeuronas = (Neurona *)calloc(npl[0],sizeof(Neurona));

	int TEMP = 0;
	int sesgo = 1;
	for(int i = 1; i <nl; i++)//Bucle que usaremos para iniciar las i capas ocultas
	{	
		pCapas[i].nNumNeuronas = npl[i];
		pCapas[i].pNeuronas = (Neurona *)calloc(npl[i],sizeof(Neurona));
		pCapas[i].tipo = 0;	
			for(int j = 0; j < pCapas[i].nNumNeuronas; j++)//Bucle que usaremos para iniciar el tamaño de la capa oculta i
			{
				// En temp se guarda el numero de neuronas+sesgo de la cada capa oculta i.
				//Si por ejemplo estamos en la capa oculta numero 1 
				//esta tendra sus vectores de pesos a NumdeEntradas+1(+1 del Sesgo)
				TEMP = npl[i-1]+sesgo;
				pCapas[i].pNeuronas[j].w = (double*)calloc(TEMP,sizeof(double));           
				pCapas[i].pNeuronas[j].deltaW = (double*)calloc(TEMP,sizeof(double));        
				pCapas[i].pNeuronas[j].ultimoDeltaW = (double*)calloc(TEMP,sizeof(double));  
				pCapas[i].pNeuronas[j].wCopia = (double*)calloc(TEMP,sizeof(double)); 

					
					for(int k = 0; k < TEMP; k++)//Bucle que usaremos para iniciar el valor de la capa oculta i
					{
						pCapas[i].pNeuronas[j].w[k] = 0.0;           
						pCapas[i].pNeuronas[j].deltaW[k] = 0.0;        
						pCapas[i].pNeuronas[j].ultimoDeltaW[k] = 0.0;  
						pCapas[i].pNeuronas[j].wCopia[k] = 0.0; 
					}
					
			}
			TEMP = 0;
			//Reiniciamos el temporal por si acaso se quedan datos basura.
			
	}

	if(tipo){
		pCapas[nNumCapas-1].tipo = 1;
	}
}


// ------------------------------
// DESTRUCTOR: liberar memoria
PerceptronMulticapa::~PerceptronMulticapa() {
	liberarMemoria();
}


// ------------------------------
// Liberar memoria para las estructuras de datos
void PerceptronMulticapa::liberarMemoria() {

	for(int i = 0;i<nNumCapas;i++){
		//Vamos recorriendo todas las capas i para liberar memoria
		for(int j = 0;j<pCapas[i].nNumNeuronas;j++)
		{
			if(i!=0){//La primera capa no tiene inicializado ningun vector puesto que no hay neuronas predecesoras
			//Cada capa tiene un array de neuronas, las recorremos con j y liberamos cada vector
			free(pCapas[i].pNeuronas[j].w);
			free(pCapas[i].pNeuronas[j].deltaW);
			free(pCapas[i].pNeuronas[j].ultimoDeltaW);
			free(pCapas[i].pNeuronas[j].wCopia);
			}
		}
		//Se libera el vector de neuronas de la capa i
		free(pCapas[i].pNeuronas);
	}
	//Se livera el vector de capas
	free(pCapas);

}

// ------------------------------
// Rellenar todos los pesos (w) aleatoriamente entre -1 y 1
void PerceptronMulticapa::pesosAleatorios() {

	for(int i = 1; i <nNumCapas; i++)
	{	
	//Recorremos las capas desde la 1 hasta la nNumcapas
	//La capa 1 no tiene conexiones anteriores por ello no se inicalizan datos.		
		for(int j = 0; j < pCapas[i].nNumNeuronas; j++)
		{
		//Cada capa tiene un vector de neuronas donde cada una tiene un vector de pesos
		//pCapas[i-1].nNumNeuronas+1 guarda la cantidad de neuronas de la capa anterior + el sesgo
					
			for(int k = 0; k < pCapas[i-1].nNumNeuronas+1; k++)//Bucle que usaremos para iniciar el valor de la capa oculta i
			{
			//Por cada neurona j de la capa i recorremos con k los vectores de pesos w y su copia
			//Metemos valores aleatorios en estos arrays.
				double X = (double)rand() / RAND_MAX;
    			double Y = (-1.0) + X * ((1.0) - (-1.0));
				pCapas[i].pNeuronas[j].w[k] = Y;           
				pCapas[i].pNeuronas[j].wCopia[k] = Y; 
			}
					
			}
			
	}

}

// ------------------------------
// Alimentar las neuronas de entrada de la red con un patrón pasado como argumento
void PerceptronMulticapa::alimentarEntradas(double* input) {

	for (int i = 0; i <pCapas[0].nNumNeuronas; i++)
	{
		pCapas[0].pNeuronas[i].x=input[i];
		pCapas[0].pNeuronas[i].dX=input[i];
	}

}

// ------------------------------
// Recoger los valores predichos por la red (out de la capa de salida) y almacenarlos en el vector pasado como argumento
void PerceptronMulticapa::recogerSalidas(double* output){

	//La ultima capa es la nNumCapas-1
	for (int i = 0; i < pCapas[nNumCapas-1].nNumNeuronas; i++)
	{
		//Recogemos los valores out de la ultima capa por cada una de sus neuronas
		output[i] = pCapas[nNumCapas-1].pNeuronas[i].x;
	}

}

// ------------------------------
// Hacer una copia de todos los pesos (copiar w en copiaW)
void PerceptronMulticapa::copiarPesos() {

	for(int i = 1; i <nNumCapas; i++)
	{	
	//Recorremos las capas desde la 1 hasta la nNumcapas
	//La capa 1 no tiene conexiones anteriores por ello no se inicalizan datos.		
		for(int j = 0; j < pCapas[i].nNumNeuronas; j++)
		{
		//Cada capa tiene un vector de neuronas donde cada una tiene un vector de pesos
		//pCapas[i-1].nNumNeuronas+1 guarda la cantidad de neuronas de la capa anterior + el sesgo
					
			for(int k = 0; k < pCapas[i-1].nNumNeuronas+1; k++)//Bucle que usaremos para iniciar el valor de la capa oculta i
			{
				//Por cada neurona j de la capa i recorremos con k los vectores de pesos w y su copia
				//Metemos valores de w en copia por si hace falta restaurar.
				pCapas[i].pNeuronas[j].wCopia[k] = pCapas[i].pNeuronas[j].w[k]; 
			}
					
			}
			
	}

}

// ------------------------------
// Restaurar una copia de todos los pesos (copiar copiaW en w)
void PerceptronMulticapa::restaurarPesos() {

	for(int i = 1; i <nNumCapas; i++)
	{	
	//Recorremos las capas desde la 1 hasta la nNumcapas
	//La capa 1 no tiene conexiones anteriores por ello no se inicalizan datos.		
		for(int j = 0; j < pCapas[i].nNumNeuronas; j++)
		{
		//Cada capa tiene un vector de neuronas donde cada una tiene un vector de pesos
		//pCapas[i-1].nNumNeuronas+1 guarda la cantidad de neuronas de la capa anterior + el sesgo
					
			for(int k = 0; k < pCapas[i-1].nNumNeuronas+1; k++)//Bucle que usaremos para iniciar el valor de la capa oculta i
			{
				//Por cada neurona j de la capa i recorremos con k los vectores de pesos w y su copia
				//Metemos valores de copia en w para su restauracion.
				pCapas[i].pNeuronas[j].w[k] = pCapas[i].pNeuronas[j].wCopia[k];
			}
					
			}
			
	}

}

// ------------------------------
// Calcular y propagar las salidas de las neuronas, desde la primera capa hasta la última
void PerceptronMulticapa::propagarEntradas() {

	double c=0.0;
	double accNet = 0.0;
	double net[pCapas[nNumCapas-1].nNumNeuronas];
	for (int i = 1; i <nNumCapas; i++)
	{
		
		for (int j = 0; j < pCapas[i].nNumNeuronas; j++)
		{
		
			//pCapas[i-1].nNumNeuronas+1 , simboliza capa anterior y su sesgo que es el +1
			//Este bucle recorre la capa anterior a i, i-1
			for (int k = 1; k < pCapas[i-1].nNumNeuronas+1; k++)
			{
				//cout<<"Neurona capa anterior: "<<pCapas[i-1].nNumNeuronas<<"\n";
				// [k-1].x , porque de la capa anterior tenemos que empezar por la neurona 0
				// pNeuronas[j].w[k] , porque en la capa i la neurona j su peso w[0] es el sesgo y no se tiene en cuenta
		
				c += pCapas[i-1].pNeuronas[k-1].x*pCapas[i].pNeuronas[j].w[k];

			}
			//SESGO
			c += pCapas[i].pNeuronas[j].w[0];
			
			//Si estamos en la ultima iteracion y la ultima capa es de sipo softmax, hacemos el calculo segun visto en clase
			if(i == nNumCapas-1 && pCapas[nNumCapas-1].tipo == 1){
				net[j] = exp(c);
				accNet += exp(c);
			}else{
				pCapas[i].pNeuronas[j].x = (1/(1 + exp((-1)*c)));
			}
			
			c = 0.0;
		}
		
		
	}

	//Comprobamos fuera de los bucles de propagacion si la ultima capa es de tipo softmax
	//Si es asi calculamos el valor de la neurona usando la formula explicada en clase
	if(pCapas[nNumCapas-1].tipo == 1){
		for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++){
			pCapas[nNumCapas-1].pNeuronas[i].x = net[i]/accNet;
		}
	}

}

// ------------------------------
// Calcular el error de salida del out de la capa de salida con respecto a un vector objetivo y devolverlo
// funcionError=1 => EntropiaCruzada // funcionError=0 => MSE
double PerceptronMulticapa::calcularErrorSalida(double* target, int funcionError) {

	double ERROR=0.0;

	//Comprobamos que tipo de funcion es la de error
	if(funcionError==0){
		
		//nNumCapas-1, por que la notacion vector es tenemos 5 capas pero en vector es la capa 4

		for (int i = 0; i<pCapas[nNumCapas-1].nNumNeuronas; i++)
		{

			ERROR += pow(target[i] - pCapas[nNumCapas-1].pNeuronas[i].x, 2);
		}
		ERROR=ERROR/pCapas[nNumCapas-1].nNumNeuronas;
	

	}else{
		//Se utilizara la entropia cruzada que viene en la exposicion de clase
		for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++){
			ERROR += target[i] * log(pCapas[nNumCapas-1].pNeuronas[i].x);
		}

	}
	
	return ERROR;
}


// ------------------------------
// Retropropagar el error de salida con respecto a un vector pasado como argumento, desde la última capa hasta la primera
// funcionError=1 => EntropiaCruzada // funcionError=0 => MSE
void PerceptronMulticapa::retropropagarError(double* objetivo, int funcionError) {

	//Hay que tener en cuenta el tipo de funcion de error a usar y sobre todo el tipo de salida que tiene la ultimna capa (Softmax u sigmoide)
	//funcion tipo 0 sigmoide, 1 softmax
	//funcionError tipo 0 MSE , 1 Entropia cruzada
	double ACC1 = 0.0;
	double ACC2 = 0.0;
	//Explicacion diapositiva 26 de la presentación
	if(pCapas[nNumCapas-1].tipo == 0)//Sigmoide
	{
		for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++)
		{
			if(funcionError == 0)//MSE
			{
				pCapas[nNumCapas-1].pNeuronas[i].dX =  (-1)*(objetivo[i] - pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[i].x);
			}else//Entropia Cruzada
			{
				pCapas[nNumCapas-1].pNeuronas[i].dX =  (-1)*(objetivo[i]/pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[i].x);
			}
		}
	}else//Softmax
	{
		//La explicacion en las diapositivas de clase 15 y 16
		//Debemos de considerar dos casos y dentro de estos otros dos casos
		//Primero se considerara si i=j y luego i!=j , luego por cada comprobacion hay que hacer la funcion de error correspondiente
		//Esto es para la capa de salida unicamente
		for(int i = 0; i < pCapas[nNumCapas-1].nNumNeuronas; i++)
		{
			for(int j = 0; j < pCapas[nNumCapas-1].nNumNeuronas; j++)
			{
				
				if (i==j)//Derivada de la salida (o j ) respecto a algo que est ́a por detras de la neurona j
				{
					if(funcionError==0)
					{
						ACC2 += (objetivo[j]-pCapas[nNumCapas-1].pNeuronas[j].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[j].x);
					}else
					{
						ACC2 += (objetivo[j]/pCapas[nNumCapas-1].pNeuronas[j].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[j].x);
					}

				}else//Derivada de la salida (o j ) respecto a algo que est ́a por detras de cualquier neurona i que no sea j
				{
					if(funcionError==0)
					{
						ACC2 += (objetivo[j]-pCapas[nNumCapas-1].pNeuronas[j].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (0 - pCapas[nNumCapas-1].pNeuronas[j].x);
					}else
					{
						ACC2 += (objetivo[j]/pCapas[nNumCapas-1].pNeuronas[j].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (0 - pCapas[nNumCapas-1].pNeuronas[j].x);
					}

				}
				
			}

			pCapas[nNumCapas-1].pNeuronas[i].dX = (-1)*ACC2;
			//OJO es posible que haya que quitarlo
			ACC2 = 0.0;
		}
		

	}

	for(int i=nNumCapas-2; i>=0; i--)
	{
		for(int j=0; j<pCapas[i].nNumNeuronas; j++)
		{
			//Se calcula el sumatorio de las entradas y su derivada en la siguiente capa
			for(int k=0; k<pCapas[i+1].nNumNeuronas; k++)
			{
				ACC1 += pCapas[i+1].pNeuronas[k].w[j+1] * pCapas[i+1].pNeuronas[k].dX;
			}

			pCapas[i].pNeuronas[j].dX = ACC1 * pCapas[i].pNeuronas[j].x * (1-pCapas[i].pNeuronas[j].x);

			//OJO es posible que haya que quitarlo
			ACC1 = 0.0;
		}
	}



}

// ------------------------------
// Acumular los cambios producidos por un patrón en deltaW
void PerceptronMulticapa::acumularCambio() {
	for(int i=1; i<nNumCapas; i++)
	{
		for(int j=0; j<pCapas[i].nNumNeuronas; j++)
		{
			for(int k=1; k<pCapas[i-1].nNumNeuronas+1; k++)
			{
				pCapas[i].pNeuronas[j].deltaW[k] +=  pCapas[i].pNeuronas[j].dX * pCapas[i-1].pNeuronas[k-1].x;
			}
			pCapas[i].pNeuronas[j].deltaW[0] += pCapas[i].pNeuronas[j].dX;
				

		}
	}

}

// ------------------------------
// Actualizar los pesos de la red, desde la primera capa hasta la última
void PerceptronMulticapa::ajustarPesos() {
	
	double _deltaW,_ultimoDeltaW;
	float eta = 0.0;
	for(int i=1; i<nNumCapas; i++)
	{
		
		for(int j=0; j<pCapas[i].nNumNeuronas; j++)
		{
			eta=this->dEta*pow(this->dDecremento, -(this->nNumCapas-1-i));
			for(int k=0; k<pCapas[i-1].nNumNeuronas+1; k++)
			{
				_deltaW = pCapas[i].pNeuronas[j].deltaW[k];

				_ultimoDeltaW = pCapas[i].pNeuronas[j].ultimoDeltaW[k];
				
				if(bOnline)//Ajuste de pesos para metodo online
				{
					pCapas[i].pNeuronas[j].w[k] -= eta * _deltaW + dMu * eta * _ultimoDeltaW;
					pCapas[i].pNeuronas[j].ultimoDeltaW[k] = pCapas[i].pNeuronas[j].deltaW[k];
				}else{//Ajuste de pesos para metodo off-line, Como el error usado es un error medio,dividimos  el cambio realizado por el nmero de patrones de entrenamiento

					pCapas[i].pNeuronas[j].w[k] -= eta * (_deltaW/int(nNumPatronesTrain)) + dMu * eta * (_ultimoDeltaW/int(nNumPatronesTrain));
					pCapas[i].pNeuronas[j].ultimoDeltaW[k] = pCapas[i].pNeuronas[j].deltaW[k];
				}
				

			}
			

		}
	}
}

// ------------------------------
// Imprimir la red, es decir, todas las matrices de pesos
void PerceptronMulticapa::imprimirRed() {

	//Se omite la capa 0, ya que es la de entrada.
	for (int i = 1; i < nNumCapas; i++)
	{
		cout<<"------Capa("<<i<<")------\n";
		for (int j = 0; j < pCapas[i].nNumNeuronas; j++)
		{
			//pCapas[i-1].nNumNeuronas, porque en la capa 1, tendra un vector de pesos de tantas entradas en la capa 0
			for (int k = 0; k < pCapas[i-1].nNumNeuronas; k++)
			{
				cout<<"["<<pCapas[i].pNeuronas[j].w[k]<<"] ";
			}
			cout<<"\n";

		}
		
	}

}

// ------------------------------
// Simular la red: propragar las entradas hacia delante, computar el error, retropropagar el error y ajustar los pesos
// entrada es el vector de entradas del patrón, objetivo es el vector de salidas deseadas del patrón.
// El paso de ajustar pesos solo deberá hacerse si el algoritmo es on-line
// Si no lo es, el ajuste de pesos hay que hacerlo en la función "entrenar"
// funcionError=1 => EntropiaCruzada // funcionError=0 => MSE
void PerceptronMulticapa::simularRed(double* entrada, double* objetivo, int funcionError) {

	//Entradas son el Train->Entradas , Objetivo es el Train->Salidas, del dataset leido por fichero
	//Se omite la capa 0, ya que es la de entrada.	
	
	//Comprobamos si el algoritmo es online
	
	if(bOnline){
		for(int capa=1;capa<nNumCapas;capa++)
		{
			for(int neurona=0;neurona<pCapas[capa].nNumNeuronas;neurona++)
			{
				for(int k=0;k<pCapas[capa-1].nNumNeuronas;k++)
				{
					pCapas[capa].pNeuronas[neurona].ultimoDeltaW[k]=pCapas[capa].pNeuronas[neurona].deltaW[k];
					pCapas[capa].pNeuronas[neurona].deltaW[k]=0;
				}

				
					pCapas[capa].pNeuronas[neurona].ultimoDeltaW[pCapas[capa-1].nNumNeuronas]=pCapas[capa].pNeuronas[neurona].deltaW[pCapas[capa-1].nNumNeuronas];
					pCapas[capa].pNeuronas[neurona].deltaW[pCapas[capa-1].nNumNeuronas]=0;
				

			}
		}
	}

	alimentarEntradas(entrada);
	propagarEntradas();
	retropropagarError(objetivo,funcionError);
	acumularCambio();
	if(bOnline)
	{
		ajustarPesos();
	}


}

// ------------------------------
// Leer una matriz de datos a partir de un nombre de fichero y devolverla
Datos* PerceptronMulticapa::leerDatos(const char *archivo) {
	Datos *data = new Datos();
		std::ifstream leer;
		leer.open(archivo);

	leer >> data->nNumEntradas;

	leer >> data->nNumSalidas;
	
	leer >> data->nNumPatrones;
	std::cout<<"  -->Entradas:" << data->nNumEntradas<< std::endl;
	std::cout<<"  -->Salidas:" << data->nNumSalidas<< std::endl;
	std::cout<<"  -->Patrones:" << data->nNumPatrones<< std::endl;
	nNumPatronesTrain = data->nNumPatrones;
	data->entradas = (double **)malloc (data->nNumPatrones*sizeof(double *));

	for (int i=0;i<data->nNumPatrones;i++)//Entradas
		data->entradas[i] = (double *) malloc (data->nNumEntradas*sizeof(double));

	data->salidas = (double **)malloc (data->nNumPatrones*sizeof(double *));

	for (int i=0;i<data->nNumPatrones;i++)//Salidas
		data->salidas[i] = (double *) malloc (data->nNumSalidas*sizeof(double));
	//Rellenamos matriz de entrada y salida de datos.
   int i = 0;
   int j = 0;
   
   //int linea=0;
   while (!leer.eof())
   {
     //std::cout<<"Linea("<<linea<<"): -- [ ";
	 for(int x = 0; x < data->nNumEntradas; x++)
	 {
		 leer >> data->entradas[i][x];
		 //std::cout<<"("<<data->entradas[i][x]<<") ";
	 }
	//std::cout<<"] <---> [";
	 for(int y = 0; y < data->nNumSalidas; y++)
	 {
		 leer >> data->salidas[j][y];
		 //std::cout<<"("<<data->salidas[j][y]<<") ";
		 
	 }
	 //std::cout<<"]\n";
      
      i++;
	  j++;
	  //linea++;
   }
   leer.close(); 

	return data;
}


// ------------------------------
// Entrenar la red para un determinado fichero de datos (pasar una vez por todos los patrones)
void PerceptronMulticapa::entrenar(Datos* pDatosTrain, int funcionError) {

	if(!bOnline){

		for (int i = 1; i < nNumCapas; i++)
		{
		
			for (int j = 0; j < pCapas[i].nNumNeuronas; j++)
			{
				//pCapas[i-1].nNumNeuronas, porque en la capa 1, tendra un vector de pesos de tantas entradas en la capa 0
				for (int k = 0; k < pCapas[i-1].nNumNeuronas+1; k++)
				{
					pCapas[i].pNeuronas[j].deltaW[k] = 0.0;

				}
			

			}
			
		}
	}

	for(int i=0; i<pDatosTrain->nNumPatrones; i++){
			simularRed(pDatosTrain->entradas[i], pDatosTrain->salidas[i],funcionError);
		}
	//Si es offline ajusta pesos al final
	if(!bOnline){
	
		ajustarPesos();

	}
}

// ------------------------------
// Probar la red con un conjunto de datos y devolver el error cometido
// funcionError=1 => EntropiaCruzada // funcionError=0 => MSE
double PerceptronMulticapa::test(Datos* pDatosTest, int funcionError) {

	double ERROR = 0.0;

	for(int i=0; i<pDatosTest->nNumPatrones; i++)
	{
		// Cargamos las entradas y propagamos el valor
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		ERROR += calcularErrorSalida(pDatosTest->salidas[i],funcionError);

	}

	if(funcionError == 0)
	{
		ERROR /= pDatosTest->nNumPatrones;
	}else
	{
		ERROR /= (-1)*pDatosTest->nNumPatrones * pCapas[nNumCapas-1].nNumNeuronas;
	}
	
	return ERROR;
	
}

// OPCIONAL - KAGGLE
// Imprime las salidas predichas para un conjunto de datos.
// Utiliza el formato de Kaggle: dos columnas (Id y Predicted)
void PerceptronMulticapa::predecir(Datos* pDatosTest)
{
	int i;
	int j;
	int numSalidas = pCapas[nNumCapas-1].nNumNeuronas;
	double * salidas = new double[numSalidas];
	
	cout << "Id,Predicted" << endl;
	
	for (i=0; i<pDatosTest->nNumPatrones; i++){

		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		recogerSalidas(salidas);

		int maxIndex = 0;
		for (j = 0; j < numSalidas; j++)
			if (salidas[j] >= salidas[maxIndex])
				maxIndex = j;
		
		cout << i << "," << maxIndex << endl;

	}
}

// ------------------------------
// Probar la red con un conjunto de datos y devolver el CCR
double PerceptronMulticapa::testClassification(Datos* pDatosTest) {

	double ccr = 0.0;

	//Se debe comparar el indice del valor maximo del vector dP,
	// y el indice de del valor maximo de oP (Neurona neurona de salida que obtiene la maxima probabilidad para el patron p)
	// Si los indices de ambos concuerdan sicnifica que la neurona de salida con maxima probabilidad e indice 'j' 
	// ha sido capaz de predecir con los datos de test de manera correcta y por ello el valor CCR debe aumentar

	int indiceDp = 0;//Indice del vector de test de salidas
	int indiceOp = 0;//Indice de la neurona con mayor salida
	double maxTest = 0.0;
	double maxNeurona = 0.0;

	for(int i=0; i<pDatosTest->nNumPatrones; i++){
		indiceOp = 0;
		indiceDp = 0;
		maxTest = 0.0;
		maxNeurona = 0.0;
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		

		// Una vez propagadas las entradas necesitamos buscar en la capa de salida cual es el mayor indice para la comparacion posterior.
		for(int j=0; j<pCapas[nNumCapas-1].nNumNeuronas; j++){

			//Buscamos el maximo de las salidas de la neurona y almacenamos su indice y su valor para seguir comparando
			//Este indice se usara para para comparar si la salida devuelve el mismo indice, donde en tal caso es un acierto CCR++
			if(pCapas[nNumCapas-1].pNeuronas[j].x > maxNeurona){
				maxNeurona = pCapas[nNumCapas-1].pNeuronas[j].x;
				indiceOp = j;
			}
			//Buscamos el maximo de las salidas del test para comparar despues los indices, esto sicnifica que la
			//neurona con mayor activación sera comparada con la salida activada a 1 en el test
			//si esto sucede sicnifica que el acierto ha sido correcto
			if(pDatosTest->salidas[i][j] > maxTest){
				maxTest = pDatosTest->salidas[i][j];
				indiceDp = j;
			}
		}

		//Si son el mismo se demuesra que la neurona con mayor activacion e indiceOP es igual a la salida del test con indiceDP
		//La red neuronal ha sido capaz de acertar con la clasificación.
		if(indiceOp == indiceDp){
			ccr++;
		}
	}
	//Aplicamos al ccr el efecto porcentaje
	ccr = 100 * ccr/pDatosTest->nNumPatrones;
	return ccr;
}

// ------------------------------
// Ejecutar el algoritmo de entrenamiento durante un número de iteraciones, utilizando pDatosTrain
// Una vez terminado, probar como funciona la red en pDatosTest
// Tanto el error MSE de entrenamiento como el error MSE de test debe calcularse y almacenarse en errorTrain y errorTest
// funcionError=1 => EntropiaCruzada // funcionError=0 => MSE
void PerceptronMulticapa::ejecutarAlgoritmo(Datos * pDatosTrain, Datos * pDatosTest, int maxiter, double *errorTrain, double *errorTest, double *ccrTrain, double *ccrTest, int funcionError)
{
	int countTrain = 0;

	// Inicialización de pesos
	pesosAleatorios();

	double minTrainError = 0.0;
	double minValError = 0.0;
	int numSinMejorar = 0;
	int numSinMejorarValidacion = 0;
	double testError = 0.0;
	Datos * pDatosValidacion = new Datos(); 
	double validationError = 0.0;
	

	// Generar datos de validación
	if(dValidacion > 0 && dValidacion < 1){
		int nNumVal = dValidacion * pDatosTrain->nNumPatrones;
		int * vector = vectorAleatoriosEnterosSinRepeticion(0,pDatosTrain->nNumPatrones-1,nNumVal);
		pDatosValidacion = new Datos();
		pDatosValidacion->nNumEntradas = pDatosTrain->nNumEntradas;
		pDatosValidacion->nNumSalidas = pDatosTrain->nNumSalidas;
		pDatosValidacion->nNumPatrones = nNumVal;
		
		pDatosValidacion->entradas = (double **)calloc (pDatosValidacion->nNumPatrones,sizeof(double *));

		for (int i=0;i<pDatosValidacion->nNumPatrones;i++)//Entradas
			pDatosValidacion->entradas[i] = (double *) calloc (pDatosValidacion->nNumEntradas,sizeof(double));

		pDatosValidacion->salidas = (double **)calloc (pDatosValidacion->nNumPatrones,sizeof(double *));
	
		for (int i=0;i<pDatosValidacion->nNumPatrones;i++)//Salidas
			pDatosValidacion->salidas[i] = (double *) calloc (pDatosValidacion->nNumSalidas,sizeof(double));

		
		for(int i = 0; i < nNumVal; i++)
		{
			
			//Entradas
			for(int X = 0; X < pDatosValidacion->nNumEntradas; X++)
			{
	
			
				pDatosValidacion->entradas[i][X] = pDatosTrain->entradas[vector[i]][X];
				
			}
			//Salidas
			for(int Y = 0; Y < pDatosValidacion->nNumSalidas; Y++)
			{
				
				pDatosValidacion->salidas[i][Y] = pDatosTrain->salidas[vector[i]][Y];
				
			}

		
	
		}
		
		
		validationError = test(pDatosValidacion,funcionError);
	}

		std::ofstream leer;
		leer.open("log.txt");

	// Aprendizaje del algoritmo
	do {

		entrenar(pDatosTrain,funcionError);

		double trainError = test(pDatosTrain,funcionError);

		if(dValidacion > 0.0 && dValidacion < 1.0){
			entrenar(pDatosValidacion,funcionError);
			validationError = test(pDatosValidacion,funcionError);
			if( countTrain==0 || validationError < minValError){
				copiarPesos();
				minValError = validationError;
				numSinMejorarValidacion = 0;
			}else if( (validationError-minValError) < 0.00001)
			{
				numSinMejorarValidacion=0;
			}
			else{
				numSinMejorarValidacion=numSinMejorarValidacion+1;
			}

			if(numSinMejorarValidacion==50){
				cout << "Salida porque no mejora el entrenamiento!!"<< endl;
				restaurarPesos();
				countTrain = maxiter;
				break;
			}
		}


		if(countTrain==0 || trainError < minTrainError){
			minTrainError = trainError;
			copiarPesos();
			numSinMejorar = 0;
		}
		else if( (trainError-minTrainError) < 0.00001)
			numSinMejorar = 0;
		else
			numSinMejorar++;

		if(numSinMejorar==50){
			cout << "Salida porque no mejora el entrenamiento!!"<< endl;
			restaurarPesos();
			countTrain = maxiter;
		}

		testError = test(pDatosTest,funcionError);
		countTrain++;

		// Comprobar condiciones de parada de validación y forzar
		//Iteracion, error entrenamiento, error test, error validacion. 
		cout << countTrain << "\t" << trainError << "\t" << testError << "\t" << validationError << endl;

	} while ( countTrain<maxiter );

	if ( (numSinMejorarValidacion!=50) && (numSinMejorar!=50))
		restaurarPesos();

	cout << "PESOS DE LA RED" << endl;
	cout << "===============" << endl;
	imprimirRed();

	cout << "Salida Esperada Vs Salida Obtenida (test)" << endl;
	cout << "=========================================" << endl;
	for(int i=0; i<pDatosTest->nNumPatrones; i++){
		double* prediccion = new double[pDatosTest->nNumSalidas];

		// Cargamos las entradas y propagamos el valor
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		recogerSalidas(prediccion);
		for(int j=0; j<pDatosTest->nNumSalidas; j++)
			cout << pDatosTest->salidas[i][j] << " -- " << prediccion[j] << " \\\\ " ;
		cout << endl;
		delete[] prediccion;

	}

	*errorTest=test(pDatosTest,funcionError);;
	*errorTrain=minTrainError;
	*ccrTest = testClassification(pDatosTest);
	*ccrTrain = testClassification(pDatosTrain);

}

// OPCIONAL - KAGGLE
//Guardar los pesos del modelo en un fichero de texto.
bool PerceptronMulticapa::guardarPesos(const char * archivo)
{
	// Objeto de escritura de fichero
	ofstream f(archivo);

	if(!f.is_open())
		return false;

	// Escribir el numero de capas, el numero de neuronas en cada capa y el tipo de capa en la primera linea.
	f << nNumCapas;

	for(int i = 0; i < nNumCapas; i++)
	{
		f << " " << pCapas[i].nNumNeuronas;
		f << " " << pCapas[i].tipo;
	}
	f << endl;

	// Escribir los pesos de cada capa
	for(int i = 1; i < nNumCapas; i++)
		for(int j = 0; j < pCapas[i].nNumNeuronas; j++)
			for(int k = 0; k < pCapas[i-1].nNumNeuronas + 1; k++)
				f << pCapas[i].pNeuronas[j].w[k] << " ";

	f.close();

	return true;

}


// OPCIONAL - KAGGLE
//Cargar los pesos del modelo desde un fichero de texto.
bool PerceptronMulticapa::cargarPesos(const char * archivo)
{
	// Objeto de lectura de fichero
	ifstream f(archivo);

	if(!f.is_open())
		return false;

	// Número de capas y de neuronas por capa.
	int nl;
	int *npl;
	int *tipos;

	// Leer número de capas.
	f >> nl;

	npl = new int[nl];
	tipos = new int[nl];

	// Leer número de neuronas en cada capa y tipo de capa.
	for(int i = 0; i < nl; i++)
	{
		f >> npl[i];
		f >> tipos[i];
	}

	// Inicializar vectores y demás valores.
	inicializar(nl, npl, tipos);

	// Leer pesos.
	for(int i = 1; i < nNumCapas; i++)
		for(int j = 0; j < pCapas[i].nNumNeuronas; j++)
			for(int k = 0; k < pCapas[i-1].nNumNeuronas + 1; k++)
				f >> pCapas[i].pNeuronas[j].w[k];

	f.close();
	delete[] npl;

	return true;
}