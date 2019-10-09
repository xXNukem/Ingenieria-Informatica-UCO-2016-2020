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
	dEta=0.7;
	dMu=1;
	bOnline=0;
	nNumCapas=3;
}

// ------------------------------
// Reservar memoria para las estructuras de datos
// nl tiene el numero de capas y npl es un vector que contiene el número de neuronas por cada una de las capas
// tipo contiene el tipo de cada capa (0 => sigmoide, 1 => softmax)
// Rellenar vector Capa* pCapas
int PerceptronMulticapa::inicializar(int nl, int npl[], bool tipo) {

	//pCapas = (Capa *)malloc(nl*sizeof(Capa));
	nNumCapas = nl;
	int aux = 0;
	pCapas = (Capa *)calloc(nl,sizeof(Capa));
	//Ahora rellenamos el pCapas
	pCapas[0].nNumNeuronas = npl[0];
	pCapas[0].pNeuronas = (Neurona *)calloc(npl[0],sizeof(Neurona));


	for(int i=1; i<nl; i++)
	{
		pCapas[i].nNumNeuronas = npl[i];
		pCapas[i].pNeuronas = (Neurona *)calloc(npl[i],sizeof(Neurona));
		pCapas[i].tipo = 0; //Asignamos el tipo sigmoide
			for(int j=0; j<npl[i]; j++)
			{
				aux = npl[i-1] + 1;
				pCapas[i].pNeuronas[j].w = (double *)calloc(aux,sizeof(double));
				pCapas[i].pNeuronas[j].deltaW = (double *)calloc(aux,sizeof(double));
				pCapas[i].pNeuronas[j].ultimoDeltaW = (double *)calloc(aux,sizeof(double));
				pCapas[i].pNeuronas[j].wCopia = (double *)calloc(aux,sizeof(double));

				for(int k=0; k<aux; k++)
				{
					pCapas[i].pNeuronas[j].w[k] = 0.0;
					pCapas[i].pNeuronas[j].deltaW[k] = 0.0;
					pCapas[i].pNeuronas[j].ultimoDeltaW[k] = 0.0;
					pCapas[i].pNeuronas[j].wCopia[k] = 0.0;
				}
			}
			aux = 0;
	}
	if(tipo)
	{
		pCapas[nNumCapas-1].tipo = 1; //Asignamos softmax a la ultima capa 
	}

	return 1;
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
		//Se recorren todas las capas
		for(int j = 0;j<pCapas[i].nNumNeuronas;j++)
		{//Para cada capa recorremos su numero de neuronas
			if(i!=0)
			{//Ignoramos la primera capa que no tiene neuronas predecesoras y liberamos los vectores de pesos de las siguientes
				free(pCapas[i].pNeuronas[j].w);
				free(pCapas[i].pNeuronas[j].deltaW);
				free(pCapas[i].pNeuronas[j].ultimoDeltaW);
				free(pCapas[i].pNeuronas[j].wCopia);
			}
		}
		//Liberamos los vectores de neuronas de cada capa
		free(pCapas[i].pNeuronas);
	}
	//Liberamos el vector de capas
	free(pCapas);

}

// ------------------------------
// Rellenar todos los pesos (w) aleatoriamente entre -1 y 1
void PerceptronMulticapa::pesosAleatorios() {
//Esta será la forma habitual de recorrer la red
	for(int i = 1; i <nNumCapas; i++)
	{	
		//Empezamos recorriendo por la capa 1, ya que la capa 0 no tiene conexiones anteriores		
		for(int j = 0; j < pCapas[i].nNumNeuronas; j++)
		{
			//Recorremos las neuronas de cada capa, que cada una tendra un vector de pesos
					
			for(int k = 0; k < pCapas[i-1].nNumNeuronas+1; k++)//bucle que utilizamos para recorrer las capas ocultas, por eso ponemos i-1, y le sumamos 1 por el sesgo
			{
				//Generamos un aleatorio entre -1 y 1 para despues meterlo en el peso y la copia del peso
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
//metemos en la salida y la derivada el patron que llega por argumento
	for (int i = 0; i <pCapas[0].nNumNeuronas; i++)
	{
		pCapas[0].pNeuronas[i].x=input[i];
		pCapas[0].pNeuronas[i].dX=input[i];
	}
}

// ------------------------------
// Recoger los valores predichos por la red (out de la capa de salida) y almacenarlos en el vector pasado como argumento
void PerceptronMulticapa::recogerSalidas(double* output){
//Recorremos el numero de neuronas de la capa de salida (nNumCapas-1)
	for (int i = 0; i < pCapas[nNumCapas-1].nNumNeuronas; i++)
	{
		//Metemos en output los valores de la salida de cada neuronas de la capa de salida
		output[i] = pCapas[nNumCapas-1].pNeuronas[i].x;
	}
}

// ------------------------------
// Hacer una copia de todos los pesos (copiar w en copiaW)
void PerceptronMulticapa::copiarPesos() {

	for(int i = 1; i <nNumCapas; i++)//Recorremos todas las capas
		{		
			for(int j = 0; j < pCapas[i].nNumNeuronas; j++)
			{
				//Recorremos el numero de neuronas de cada capa			
				for(int k = 0; k < pCapas[i-1].nNumNeuronas+1; k++)//pCapas[i-1].nNumNeuronas+1 son el numero de neuronas de la capa anterior mas el sesgo
				{
					//guardamos el peso en la copia 
					pCapas[i].pNeuronas[j].wCopia[k] = pCapas[i].pNeuronas[j].w[k]; 
				}		
			}
				
		}
}

// ------------------------------
// Restaurar una copia de todos los pesos (copiar copiaW en w)
void PerceptronMulticapa::restaurarPesos() {
//Se recorre la red como siempre
	for(int i = 1; i <nNumCapas; i++)
	{	
		for(int j = 0; j < pCapas[i].nNumNeuronas; j++)
		{		
			for(int k = 0; k < pCapas[i-1].nNumNeuronas+1; k++)
			{
				//devolvemos el peso a su estado anterior, que es el que teniamos en la copia
				pCapas[i].pNeuronas[j].w[k] = pCapas[i].pNeuronas[j].wCopia[k];
			}
					
		}
			
	}

}

// ------------------------------
// Calcular y propagar las salidas de las neuronas, desde la primera capa hasta la última
void PerceptronMulticapa::propagarEntradas() {

//Hay que cambiar esta funcion para la ultima capa
double aux = 0.0;
double sumatorioNet = 0.0;
double net[pCapas[nNumCapas-1].nNumNeuronas];
	for(int i=1; i<nNumCapas; i++)
	{
		for(int j=0; j<pCapas[i].nNumNeuronas; j++)
		{
			for(int k=1; k<pCapas[i-1].nNumNeuronas+1; k++)
			{
					aux += pCapas[i].pNeuronas[j].w[k] * pCapas[i-1].pNeuronas[k-1].x;
			}

				aux += pCapas[i].pNeuronas[j].w[0];//Sesgo

			if(i == nNumCapas-1 && pCapas[nNumCapas-1].tipo == 1)//Consideramos que la ultima capa sea softmax
			{
				net[j] = exp(aux);
				sumatorioNet += exp(aux);
			}
			else //Sino es softmax pues la hacemos sigmoide como toda la vida
			{
				pCapas[i].pNeuronas[j].x = (1/(1 + exp((-1)*aux)));
			}
			aux = 0.0;
		}
	}

	//Operaciones para cuando la ultima capa es softmax
	if(pCapas[nNumCapas-1].tipo == 1){
		for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++){
			pCapas[nNumCapas-1].pNeuronas[i].x = net[i]/sumatorioNet;
		}
	}

}

// ------------------------------
// Calcular el error de salida del out de la capa de salida con respecto a un vector objetivo y devolverlo
// funcionError=1 => EntropiaCruzada // funcionError=0 => MSE
double PerceptronMulticapa::calcularErrorSalida(double* target, bool funcionError) {

double error = 0.0;

	if(funcionError == 0) //Se calcula MSE
	{

		for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++)
		{
			error += pow(target[i] - pCapas[nNumCapas-1].pNeuronas[i].x, 2);
		}
		error = error/pCapas[nNumCapas-1].nNumNeuronas;
	}
	else //Se calcula entropia cruzada
	{
		//Se calcula el error por entropiacruzada
		for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++)
		{
			error += target[i] * log(pCapas[nNumCapas-1].pNeuronas[i].x);
		}
	}

	return error;

}


// ------------------------------
// Retropropagar el error de salida con respecto a un vector pasado como argumento, desde la última capa hasta la primera
// funcionError=1 => EntropiaCruzada // funcionError=0 => MSE
void PerceptronMulticapa::retropropagarError(double* objetivo, bool funcionError) {

	double sumatorio2=0.0;
	//Si la capa de salida es softmax habra que cambiar las derivadas
	//Tenemos en cuenta la funcion de error
	
	if(pCapas[nNumCapas-1].tipo == 0) //SALIDA TIPO SIGMOIDE
	{
		for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++)
		{
			if(funcionError == 0)//MSE
			{
				pCapas[nNumCapas-1].pNeuronas[i].dX =  (-1)*(objetivo[i] - pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[i].x);
			}
			else //ENTROPIA CRUZADA
			{
				pCapas[nNumCapas-1].pNeuronas[i].dX =  (-1)*(objetivo[i]/pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[i].x);
			}
		}
	}
	else //SALIDA TIPO SOFTMAX
	{
		for(int j=0; j<pCapas[nNumCapas-1].nNumNeuronas; j++)
		{
			for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++)
			{
				if(i==j)
				{
					if(funcionError == 0)//ERROR MSE
					{
						sumatorio2 += (objetivo[i]-pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[j].x * (1 - pCapas[nNumCapas-1].pNeuronas[i].x);
					}
					else //ENTROPIA CRUZADA
					{
						sumatorio2 += (objetivo[i]/pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[j].x * (1 - pCapas[nNumCapas-1].pNeuronas[i].x);
					}
				}
				else
				{
					if(funcionError == 0)//ERROR MSE
					{
						sumatorio2 += (objetivo[i]-pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[j].x * (0 - pCapas[nNumCapas-1].pNeuronas[i].x);
					}
					else //ENTROPIA CRUZADA
					{
						sumatorio2 += (objetivo[i]/pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[j].x * (0 - pCapas[nNumCapas-1].pNeuronas[i].x);
					}
				}
			}
			pCapas[nNumCapas-1].pNeuronas[j].dX = (-1)*sumatorio2;
			sumatorio2 = 0.0;
		}
	}


	double sumatorio = 0.0;

	//Una vez tenemos el error sea sigmoide o softmax lo pasamos hacia las otras capas
	for(int i=nNumCapas-2; i>=0; i--)
	{
		for(int j=0; j<pCapas[i].nNumNeuronas; j++)
		{
			for(int k=0; k<pCapas[i+1].nNumNeuronas; k++) //Calculamos sumatorio de las capas y derivada de la salida producida por esa neurona
			{
				sumatorio += pCapas[i+1].pNeuronas[k].w[j+1] * pCapas[i+1].pNeuronas[k].dX;
			}

			pCapas[i].pNeuronas[j].dX = sumatorio * pCapas[i].pNeuronas[j].x * (1 -pCapas[i].pNeuronas[j].x);
			sumatorio = 0.0;
		}
	}

}

// ------------------------------
// Acumular los cambios producidos por un patrón en deltaW
void PerceptronMulticapa::acumularCambio() {
//HAcemos el sumatorio del cambiio recorriendo la red como siempre

	for(int i=1; i<nNumCapas; i++)
	{
		for(int j=0; j<pCapas[i].nNumNeuronas; j++)
		{
			for(int k=1; k<pCapas[i-1].nNumNeuronas+1; k++)
			{
				pCapas[i].pNeuronas[j].deltaW[k] +=  pCapas[i].pNeuronas[j].dX * pCapas[i-1].pNeuronas[k-1].x;
			}
			pCapas[i].pNeuronas[j].deltaW[0] += pCapas[i].pNeuronas[j].dX;//Aqui el sesgo

		}
	}
}

// ------------------------------
// Actualizar los pesos de la red, desde la primera capa hasta la última
void PerceptronMulticapa::ajustarPesos() {

	double _deltaW,_ultimoDeltaW;
	float etaAux = 0.0;
	for(int i=1; i<nNumCapas; i++)
	{
		for(int j=0; j<pCapas[i].nNumNeuronas; j++)
		{
			//eta la hacemos auxiliar porque sino no va el decremento, a saber el motivo
			etaAux=this->dEta*pow(this->dDecremento, -(this->nNumCapas-1-i));
			for(int k=0; k<pCapas[i-1].nNumNeuronas+1; k++)
			{
				_deltaW = pCapas[i].pNeuronas[j].deltaW[k];
				_ultimoDeltaW = pCapas[i].pNeuronas[j].ultimoDeltaW[k];
				pCapas[i].pNeuronas[j].w[k] -= etaAux * _deltaW + dMu * etaAux * _ultimoDeltaW;
				pCapas[i].pNeuronas[j].ultimoDeltaW[k] = pCapas[i].pNeuronas[j].deltaW[k];
			}
		}
	}

}

// ------------------------------
// Imprimir la red, es decir, todas las matrices de pesos
void PerceptronMulticapa::imprimirRed() {
//Impresion de los pesos de la red
	for (int i = 1; i < nNumCapas; i++)
	{
		cout<<"Capa("<<i<<")------\n";
		for (int j = 0; j < pCapas[i].nNumNeuronas; j++)
		{
			for (int k = 0; k < pCapas[i-1].nNumNeuronas; k++)
			{
				cout<<"[-"<<pCapas[i].pNeuronas[j].w[k]<<"-] ";
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
void PerceptronMulticapa::simularRed(double* entrada, double* objetivo, bool funcionError) {

			for(int i=1; i<nNumCapas; i++)
			{
				for(int j=0; j<pCapas[i].nNumNeuronas; j++)
				{
					for(int k=0; k<pCapas[i-1].nNumNeuronas; k++)
					{
						pCapas[i].pNeuronas[j].ultimoDeltaW[k] = pCapas[i].pNeuronas[j].deltaW[k];
						pCapas[i].pNeuronas[j].deltaW[k] = 0.0;
					}
				}
			}


		if(bOnline)
		{

			alimentarEntradas(entrada);
			propagarEntradas();
			retropropagarError(objetivo, funcionError);
			acumularCambio();
			ajustarPesos();

		}
		else
		{
			alimentarEntradas(entrada);
			propagarEntradas();
			retropropagarError(objetivo, funcionError);
			acumularCambio();
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
	//std::cout<<"  -->Entradas:" << data->nNumEntradas<< std::endl;
	//std::cout<<"  -->Salidas:" << data->nNumSalidas<< std::endl;
	//std::cout<<"  -->Patrones:" << data->nNumPatrones<< std::endl;

	//Reserva de memoria para las entrads
	data->entradas = (double **)calloc (data->nNumPatrones,sizeof(double *));

	for (int i=0;i<data->nNumPatrones;i++)
		data->entradas[i] = (double *) calloc (data->nNumEntradas,sizeof(double));


	//Reserva de memoria para las salidas
	data->salidas = (double **)calloc (data->nNumPatrones,sizeof(double *));

	for (int i=0;i<data->nNumPatrones;i++)
		data->salidas[i] = (double *) calloc (data->nNumSalidas,sizeof(double));
	//Rellenamos matriz de entrada y salida de datos.
   int i = 0;
   int j = 0;
   

   //Rellenamos las matrices con la informacion
   while (!leer.eof())
   {

	 for(int x = 0; x < data->nNumEntradas; x++)
	 {
		 leer >> data->entradas[i][x];

	 }

	 for(int y = 0; y < data->nNumSalidas; y++)
	 {
		 leer >> data->salidas[j][y];

		 
	 }
      
      i++;
	  j++;

   }
   leer.close(); 

	return data;
}


// ------------------------------
// Entrenar la red para un determinado fichero de datos (pasar una vez por todos los patrones)
void PerceptronMulticapa::entrenar(Datos* pDatosTrain, bool funcionError) {

	for(int i=0; i<pDatosTrain->nNumPatrones; i++)
	{
		simularRed(pDatosTrain->entradas[i], pDatosTrain->salidas[i],funcionError);
	}

	if(!bOnline)
	{	//Si es modo offline ajustaremos los pesos al final
		ajustarPesos();		
	}


}

// ------------------------------
// Probar la red con un conjunto de datos y devolver el error cometido
// funcionError=1 => EntropiaCruzada // funcionError=0 => MSE
double PerceptronMulticapa::test(Datos* pDatosTest, bool funcionError) {

	//Tenemos que probar para todos los patrones
	double dAvgTestError = 0;
	for(int i=0; i<pDatosTest->nNumPatrones; i++){
		//Alimentamos entradas y propagamos para despues sacar el error
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		dAvgTestError += calcularErrorSalida(pDatosTest->salidas[i], funcionError);
	}

	//Despues de probar para todos los patrones, miramos la funcion error, porque cada una se divide por una cosa distinta
	if(funcionError)
	{
		dAvgTestError /= (-1)*pDatosTest->nNumPatrones * pCapas[nNumCapas-1].nNumNeuronas;
	}
	else
	{
		dAvgTestError /= pDatosTest->nNumPatrones;
	}

	return dAvgTestError;

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

	//Tenemos que mirar las salidas tanto de nuestra red neuronal como del test y quedarnos con la mas grande
	//si dicha neurona es la misma entonces aumentamos el ccr

	int indiceDatosTest = 0;
	int indiceNeuronas = 0;
	double maximoTest = 0.0, maximoNeuronas =0.0;

	for(int i=0; i<pDatosTest->nNumPatrones; i++)
	{
		indiceNeuronas = 0;
		indiceDatosTest = 0;
		maximoTest = 0.0;
		maximoNeuronas = 0.0;
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();

		for(int j=0; j<pCapas[nNumCapas-1].nNumNeuronas; j++)
		{

			//Nos vamos quedando con el mayor indice
			if(pCapas[nNumCapas-1].pNeuronas[j].x > maximoNeuronas)
			{
				maximoNeuronas = pCapas[nNumCapas-1].pNeuronas[j].x;
				indiceNeuronas = j;
			}

			if(pDatosTest->salidas[i][j] > maximoTest)
			{
				maximoTest = pDatosTest->salidas[i][j];
				indiceDatosTest = j;
			}
		}

		//Ahora comprobamos si son el mismo y actuamos en consecuencia
		if(indiceNeuronas == indiceDatosTest)
		{
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
void PerceptronMulticapa::ejecutarAlgoritmo(Datos * pDatosTrain, Datos * pDatosTest, int maxiter, double *errorTrain, double *errorTest, double *ccrTrain, double *ccrTest,bool funcionError)
{

	int countTrain = 0;
	Datos * valData=new Datos(); //Esctructuras de datos para el conjunto de validacion

	// Inicialización de pesos
	pesosAleatorios();

	double minValError = 0;
	double minTrainError = 0;
	
	int numsinMejorarValidationError;
	int numSinMejorar;
	
	double validationError=0.0;

	// Generar datos de validación
	if(dValidacion > 0 && dValidacion < 1)
	{
		int nNumVal = dValidacion * pDatosTrain->nNumPatrones;
		int * vector = vectorAleatoriosEnterosSinRepeticion(0,pDatosTrain->nNumPatrones-1,nNumVal);
		valData->nNumEntradas = pDatosTrain->nNumEntradas;
		valData->nNumSalidas = pDatosTrain->nNumSalidas;
		valData->nNumPatrones = nNumVal;
		
		//Para el conjunto de validacion se generan las matrices como anteriormente
		valData->entradas = (double **)calloc (valData->nNumPatrones,sizeof(double *));

		for (int i=0;i<valData->nNumPatrones;i++)
			valData->entradas[i] = (double *) calloc (valData->nNumEntradas,sizeof(double));

		valData->salidas = (double **)calloc (valData->nNumPatrones,sizeof(double *));
	
		for (int i=0;i<valData->nNumPatrones;i++)
			valData->salidas[i] = (double *) calloc (valData->nNumSalidas,sizeof(double));

		
		for(int i = 0; i < nNumVal; i++)
		{
			
			for(int j = 0; j < valData->nNumEntradas; j++)
			{
				valData->entradas[i][j] = pDatosTrain->entradas[vector[i]][j];
			}

			for(int k = 0; k < valData->nNumSalidas; k++)
			{
				valData->salidas[i][k] = pDatosTrain->salidas[vector[i]][k];
			}
		}
		
		
		validationError = test(valData,funcionError);
	}

		std::ofstream leer;
		leer.open("log.txt",ios::app);
	// Aprendizaje del algoritmo
	do {

		entrenar(pDatosTrain,funcionError);
		double trainError = test(pDatosTrain,funcionError);

	   //Condicion de parada del conjunto de validacion
		if(dValidacion > 0.0 && dValidacion < 1.0){
			entrenar(valData,funcionError);
			validationError = test(valData,funcionError);
			if( countTrain==0 || validationError < minValError){
				copiarPesos();
				minValError = validationError;
				numsinMejorarValidationError = 0;
			}else if( (validationError-minValError) < 0.00001)
			{
				numsinMejorarValidationError=0;
			}
			else{
				numsinMejorarValidationError=numsinMejorarValidationError+1;
			}

			if(numsinMejorarValidationError==50){
				cout << "Salida porque no mejora el entrenamiento!!"<< endl;
				restaurarPesos();
				countTrain = maxiter;
				break;
			}
		}


		//Condicion de parada train Error
		if(countTrain==0 || trainError < minTrainError){
			minTrainError = trainError;
			copiarPesos();
			numSinMejorar = 0;
		}else if( (trainError-minTrainError) < 0.00001)
			numSinMejorar=0;
		else
			numSinMejorar++;

		if(numSinMejorar==50){
			cout << "Salida porque no mejora el entrenamiento!!"<< endl;
			restaurarPesos();
			countTrain = maxiter;
			break;
		}

		countTrain++;

		// Comprobar condiciones de parada de validación y forzar
		// OJO: en este caso debemos guardar el error de validación anterior, no el mínimo
		// Por lo demás, la forma en que se debe comprobar la condición de parada es similar
		// a la que se ha aplicado más arriba para el error de entrenamiento
		double testError = test(pDatosTest,funcionError);
		
		leer<<trainError<<" "<<validationError<<" "<<testError<<endl;

		//Iteracion - Error de entrenamiento - Eror de validacion - Error de Test
		cout << countTrain << "\t"<< trainError <<"\t"<< validationError <<"\t"<<testError<< endl;

	} while (countTrain<maxiter);

	leer.close();
	cout << "PESOS DE LA RED" << endl;
	cout << "===============" << endl;
	//imprimirRed();

	cout << "Salida Esperada Vs Salida Obtenida (test)" << endl;
	cout << "=========================================" << endl;
	for(int i=0; i<pDatosTest->nNumPatrones; i++){
		double* prediccion = new double[pDatosTest->nNumSalidas];

		// Cargamos las entradas y propagamos el valor
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		recogerSalidas(prediccion);
		for(int j=0; j<pDatosTest->nNumSalidas; j++)
			cout << pDatosTest->salidas[i][j] << " -- " << prediccion[j] << " ";
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
