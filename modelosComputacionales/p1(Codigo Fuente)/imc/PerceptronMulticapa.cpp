<<<<<<< Updated upstream:modelosComputacionales/p1/imc/PerceptronMulticapa.cpp
/*********************************************************************
* File : PerceptronMulticapa.cpp
* Date : 2018
*********************************************************************/

#include "PerceptronMulticapa.h"
#include "util.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <limits>
#include <math.h>


using namespace imc;
using namespace std;
using namespace util;

// ------------------------------
// CONSTRUCTOR: Dar valor por defecto a todos los parámetros
PerceptronMulticapa::PerceptronMulticapa(){
	dEta = 0.1;
	dMu = 0.9;
	//deltaW=0-0;
	nNumCapas = 3;

}

// ------------------------------
// Reservar memoria para las estructuras de datos
void PerceptronMulticapa::inicializar(int nl, int npl[]) {
	//pasamos al numero de capas totales las que vienen por argumento
	nNumCapas = nl;
	//reservamos memoria para el vector de capas
	pCapas = (Capa *)calloc(nl,sizeof(Capa));

	//Se reserva memoria para la primera capa independientemente, ya que no tendrá sesgo
	pCapas[0].nNumNeuronas = npl[0];
	pCapas[0].pNeuronas = (Neurona *)calloc(npl[0],sizeof(Neurona));

	int aux, sesgo=1;
	for(int i = 1; i <nl; i++)
	{	
		pCapas[i].nNumNeuronas = npl[i]; //Asignamos el numero de neuronas
		pCapas[i].pNeuronas = (Neurona *)calloc(npl[i],sizeof(Neurona)); //reservamos memoria para el vector de neuronas de la capa i
			
			for(int j = 0; j < pCapas[i].nNumNeuronas; j++)//Bucle que usaremos para iniciar el tamaño de la capa oculta i
			{
				//guardamos en aux el numero de neuronas de la capa i-1 + sesgo
				//Reservamos memoria para cada uno de los vectores de pesos de esas neuronas
				aux = npl[i-1]+sesgo;
				pCapas[i].pNeuronas[j].w = (double*)calloc(aux,sizeof(double));           
				pCapas[i].pNeuronas[j].deltaW = (double*)calloc(aux,sizeof(double));        
				pCapas[i].pNeuronas[j].ultimoDeltaW = (double*)calloc(aux,sizeof(double));  
				pCapas[i].pNeuronas[j].wCopia = (double*)calloc(aux,sizeof(double)); 

					for(int k = 0; k < aux; k++)
					{
						//Inicializamos los vectores depesos a 0.0
						pCapas[i].pNeuronas[j].w[k] = 0.0;           
						pCapas[i].pNeuronas[j].deltaW[k] = 0.0;        
						pCapas[i].pNeuronas[j].ultimoDeltaW[k] = 0.0;  
						pCapas[i].pNeuronas[j].wCopia[k] = 0.0; 
					}
					
			}
			aux = 0;
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
void PerceptronMulticapa::recogerSalidas(double* output)
{
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

	double sumatorio=0.0;
	for (int i = 1; i <nNumCapas; i++)
	{
		
		for (int j = 0; j < pCapas[i].nNumNeuronas; j++)
		{
		
			for (int k = 1; k < pCapas[i-1].nNumNeuronas+1; k++)
			{
					//comenzamos en la neurona 0					No tenemos en cuenta el sesgo
				sumatorio += pCapas[i-1].pNeuronas[k-1].x*pCapas[i].pNeuronas[j].w[k];

			}
			//aqui hacemos el sesgo
			sumatorio += pCapas[i].pNeuronas[j].w[0];

			pCapas[i].pNeuronas[j].x = (1/(1 + exp((-1)*sumatorio)));
			sumatorio = 0.0;
		}
	}
}

// ------------------------------
// Calcular el error de salida (MSE) del out de la capa de salida con respecto a un vector objetivo y devolverlo
double PerceptronMulticapa::calcularErrorSalida(double* target) {

	double errorMSE=0.0;
	//nNumCapas-1porque estamos en la salida

	for (int i = 0; i<pCapas[nNumCapas-1].nNumNeuronas; i++)
	{

		errorMSE += pow(target[i] - pCapas[nNumCapas-1].pNeuronas[i].x, 2);
	}

		errorMSE=errorMSE/pCapas[nNumCapas-1].nNumNeuronas;
	return errorMSE;
}


// ------------------------------
// Retropropagar el error de salida con respecto a un vector pasado como argumento, desde la última capa hasta la primera
void PerceptronMulticapa::retropropagarError(double* objetivo) {
	double sumatorio = 0.0;

	//HAcemos la derivada de la capa de salida
	for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++)
	{
		pCapas[nNumCapas-1].pNeuronas[i].dX =  (-1)*(objetivo[i] - pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[i].x);
	}

	//La hacemos para el resto de capas hacia atras
	for(int i=nNumCapas-2; i>=0; i--)
	{
		for(int j=0; j<pCapas[i].nNumNeuronas; j++)
		{
			//Se calcula el sumatorio de las entradas y su derivada en la siguiente capa
			for(int k=0; k<pCapas[i+1].nNumNeuronas; k++)
			{
				sumatorio += pCapas[i+1].pNeuronas[k].w[j+1] * pCapas[i+1].pNeuronas[k].dX;
			}

			pCapas[i].pNeuronas[j].dX = sumatorio * pCapas[i].pNeuronas[j].x * (1-pCapas[i].pNeuronas[j].x);
			//ojo cuidao sumatorio=0;
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
// Simular la red: propagar las entradas hacia delante, retropropagar el error y ajustar los pesos
// entrada es el vector de entradas del patrón y objetivo es el vector de salidas deseadas del patrón
void PerceptronMulticapa::simularRedOnline(double* entrada, double* objetivo) {

	//Entradas son el Train->Entradas , Objetivo es el Train->Salidas, del dataset leido por fichero
	//Se omite la capa 0, ya que es la de entrada.
	
	for (int i = 1; i < nNumCapas; i++)
	{
	
		for (int j = 0; j < pCapas[i].nNumNeuronas; j++)
		{
			//Inicializamos el cambio de peso y el ultimo cambio
			for (int k = 0; k < pCapas[i-1].nNumNeuronas+1; k++)
			{
				pCapas[i].pNeuronas[j].ultimoDeltaW[k] = pCapas[i].pNeuronas[j].deltaW[k];
				pCapas[i].pNeuronas[j].deltaW[k] = 0.0;

			}
		
		}
		
	}

	alimentarEntradas(entrada);
	propagarEntradas();
	retropropagarError(objetivo);
	acumularCambio();
	ajustarPesos();

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
	data->entradas = (double **)malloc (data->nNumPatrones*sizeof(double *));

	for (int i=0;i<data->nNumPatrones;i++)
		data->entradas[i] = (double *) malloc (data->nNumEntradas*sizeof(double));


	//Reserva de memoria para las salidas
	data->salidas = (double **)malloc (data->nNumPatrones*sizeof(double *));

	for (int i=0;i<data->nNumPatrones;i++)
		data->salidas[i] = (double *) malloc (data->nNumSalidas*sizeof(double));
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
// Entrenar la red on-line para un determinado fichero de datos
void PerceptronMulticapa::entrenarOnline(Datos* pDatosTrain) {
	int i;
	for(i=0; i<pDatosTrain->nNumPatrones; i++){
		simularRedOnline(pDatosTrain->entradas[i], pDatosTrain->salidas[i]);
	}
}

// ------------------------------
// Probar la red con un conjunto de datos y devolver el error MSE cometido
double PerceptronMulticapa::test(Datos* pDatosTest) {

	double error = 0.0;

	for(int i=0; i<pDatosTest->nNumPatrones; i++)
	{
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		error += calcularErrorSalida(pDatosTest->salidas[i]);

	}

	error /= pDatosTest->nNumPatrones;
	return error;
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
		
		cout << i;

		for (j = 0; j < numSalidas; j++)
			cout << "," << salidas[j];
		cout << endl;

	}
}

// ------------------------------
// Ejecutar el algoritmo de entrenamiento durante un número de iteraciones, utilizando pDatosTrain
// Una vez terminado, probar como funciona la red en pDatosTest
// Tanto el error MSE de entrenamiento como el error MSE de test debe calcularse y almacenarse en errorTrain y errorTest
void PerceptronMulticapa::ejecutarAlgoritmoOnline(Datos * pDatosTrain, Datos * pDatosTest, int maxiter, double *errorTrain, double *errorTest)
{
	int countTrain = 0;
	Datos * valData=new Datos(); //Esctructuras de datos para el conjunto de validacion

	// Inicialización de pesos
	pesosAleatorios();

	double minValError = 0;
	double minTrainError = 0;
	
	int numsinMejorarValidationError;
	int numSinMejorar;
	
	double testError = 0;
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
		
		
		validationError = test(valData);
	}

		std::ofstream leer;
		leer.open("log.txt",ios::app);
	// Aprendizaje del algoritmo
	do {

		
		entrenarOnline(pDatosTrain);
		double trainError = test(pDatosTrain);

	   //Condicion de parada del conjunto de validacion
		if(dValidacion > 0.0 && dValidacion < 1.0){
			entrenarOnline(valData);
			validationError = test(valData);
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
		double testError = test(pDatosTest);
		
		leer<<trainError<<" "<<validationError<<" "<<testError<<endl;

		//Iteracion - Error de entrenamiento - Eror de validacion - Error de Test
		//cout << countTrain << "\t"<< trainError <<"\t"<< validationError <<"\t"<<testError<< endl;

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

	testError = test(pDatosTest);
	*errorTest=testError;
	*errorTrain=minTrainError;

}

// OPCIONAL - KAGGLE
//Guardar los pesos del modelo en un fichero de texto.
bool PerceptronMulticapa::guardarPesos(const char * archivo)
{
	// Objeto de escritura de fichero
	ofstream f(archivo);

	if(!f.is_open())
		return false;

	// Escribir el numero de capas y el numero de neuronas en cada capa en la primera linea.
	f << nNumCapas;

	for(int i = 0; i < nNumCapas; i++)
		f << " " << pCapas[i].nNumNeuronas;
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

	// Leer número de capas.
	f >> nl;

	npl = new int[nl];

	// Leer número de neuronas en cada capa.
	for(int i = 0; i < nl; i++)
		f >> npl[i];

	// Inicializar vectores y demás valores.
	inicializar(nl, npl);

	// Leer pesos.
	for(int i = 1; i < nNumCapas; i++)
		for(int j = 0; j < pCapas[i].nNumNeuronas; j++)
			for(int k = 0; k < pCapas[i-1].nNumNeuronas + 1; k++)
				f >> pCapas[i].pNeuronas[j].w[k];

	f.close();
	delete[] npl;

	return true;
=======
/*********************************************************************
* File : PerceptronMulticapa.cpp
* Date : 2018
*********************************************************************/

#include "PerceptronMulticapa.h"
#include "util.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <limits>
#include <math.h>


using namespace imc;
using namespace std;
using namespace util;

// ------------------------------
// CONSTRUCTOR: Dar valor por defecto a todos los parámetros
PerceptronMulticapa::PerceptronMulticapa(){
	dEta = 0.1;
	dMu = 0.9;
	//deltaW=0-0;
	nNumCapas = 3;

}

// ------------------------------
// Reservar memoria para las estructuras de datos
void PerceptronMulticapa::inicializar(int nl, int npl[]) {
	//pasamos al numero de capas totales las que vienen por argumento
	nNumCapas = nl;
	//reservamos memoria para el vector de capas
	pCapas = (Capa *)calloc(nl,sizeof(Capa));

	//Se reserva memoria para la primera capa independientemente, ya que no tendrá sesgo
	pCapas[0].nNumNeuronas = npl[0];
	pCapas[0].pNeuronas = (Neurona *)calloc(npl[0],sizeof(Neurona));

	int aux, sesgo=1;
	for(int i = 1; i <nl; i++)
	{	
		pCapas[i].nNumNeuronas = npl[i]; //Asignamos el numero de neuronas
		pCapas[i].pNeuronas = (Neurona *)calloc(npl[i],sizeof(Neurona)); //reservamos memoria para el vector de neuronas de la capa i
			
			for(int j = 0; j < pCapas[i].nNumNeuronas; j++)//Bucle que usaremos para iniciar el tamaño de la capa oculta i
			{
				//guardamos en aux el numero de neuronas de la capa i-1 + sesgo
				//Reservamos memoria para cada uno de los vectores de pesos de esas neuronas
				aux = npl[i-1]+sesgo;
				pCapas[i].pNeuronas[j].w = (double*)calloc(aux,sizeof(double));           
				pCapas[i].pNeuronas[j].deltaW = (double*)calloc(aux,sizeof(double));        
				pCapas[i].pNeuronas[j].ultimoDeltaW = (double*)calloc(aux,sizeof(double));  
				pCapas[i].pNeuronas[j].wCopia = (double*)calloc(aux,sizeof(double)); 

					for(int k = 0; k < aux; k++)
					{
						//Inicializamos los vectores depesos a 0.0
						pCapas[i].pNeuronas[j].w[k] = 0.0;           
						pCapas[i].pNeuronas[j].deltaW[k] = 0.0;        
						pCapas[i].pNeuronas[j].ultimoDeltaW[k] = 0.0;  
						pCapas[i].pNeuronas[j].wCopia[k] = 0.0; 
					}
					
			}
			aux = 0;
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
void PerceptronMulticapa::recogerSalidas(double* output)
{
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

	double sumatorio=0.0;
	for (int i = 1; i <nNumCapas; i++)
	{
		
		for (int j = 0; j < pCapas[i].nNumNeuronas; j++)
		{
		
			for (int k = 1; k < pCapas[i-1].nNumNeuronas+1; k++)
			{
					//comenzamos en la neurona 0					No tenemos en cuenta el sesgo
				sumatorio += pCapas[i-1].pNeuronas[k-1].x*pCapas[i].pNeuronas[j].w[k];

			}
			//aqui hacemos el sesgo
			sumatorio += pCapas[i].pNeuronas[j].w[0];

			pCapas[i].pNeuronas[j].x = (1/(1 + exp((-1)*sumatorio)));
			sumatorio = 0.0;
		}
	}
}

// ------------------------------
// Calcular el error de salida (MSE) del out de la capa de salida con respecto a un vector objetivo y devolverlo
double PerceptronMulticapa::calcularErrorSalida(double* target) {

	double errorMSE=0.0;
	//nNumCapas-1porque estamos en la salida

	for (int i = 0; i<pCapas[nNumCapas-1].nNumNeuronas; i++)
	{

		errorMSE += pow(target[i] - pCapas[nNumCapas-1].pNeuronas[i].x, 2);
	}

		errorMSE=errorMSE/pCapas[nNumCapas-1].nNumNeuronas;
	return errorMSE;
}


// ------------------------------
// Retropropagar el error de salida con respecto a un vector pasado como argumento, desde la última capa hasta la primera
void PerceptronMulticapa::retropropagarError(double* objetivo) {
	double sumatorio = 0.0;

	//HAcemos la derivada de la capa de salida
	for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++)
	{
		pCapas[nNumCapas-1].pNeuronas[i].dX =  (-1)*(objetivo[i] - pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[i].x);
	}

	//La hacemos para el resto de capas hacia atras
	for(int i=nNumCapas-2; i>=0; i--)
	{
		for(int j=0; j<pCapas[i].nNumNeuronas; j++)
		{
			//Se calcula el sumatorio de las entradas y su derivada en la siguiente capa
			for(int k=0; k<pCapas[i+1].nNumNeuronas; k++)
			{
				sumatorio += pCapas[i+1].pNeuronas[k].w[j+1] * pCapas[i+1].pNeuronas[k].dX;
			}

			pCapas[i].pNeuronas[j].dX = sumatorio * pCapas[i].pNeuronas[j].x * (1-pCapas[i].pNeuronas[j].x);
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
// Simular la red: propagar las entradas hacia delante, retropropagar el error y ajustar los pesos
// entrada es el vector de entradas del patrón y objetivo es el vector de salidas deseadas del patrón
void PerceptronMulticapa::simularRedOnline(double* entrada, double* objetivo) {

	//Entradas son el Train->Entradas , Objetivo es el Train->Salidas, del dataset leido por fichero
	//Se omite la capa 0, ya que es la de entrada.
	
	for (int i = 1; i < nNumCapas; i++)
	{
	
		for (int j = 0; j < pCapas[i].nNumNeuronas; j++)
		{
			//Inicializamos el cambio de peso y el ultimo cambio
			for (int k = 0; k < pCapas[i-1].nNumNeuronas+1; k++)
			{
				pCapas[i].pNeuronas[j].ultimoDeltaW[k] = pCapas[i].pNeuronas[j].deltaW[k];
				pCapas[i].pNeuronas[j].deltaW[k] = 0.0;

			}
		
		}
		
	}

	alimentarEntradas(entrada);
	propagarEntradas();
	retropropagarError(objetivo);
	acumularCambio();
	ajustarPesos();

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
	data->entradas = (double **)malloc (data->nNumPatrones*sizeof(double *));

	for (int i=0;i<data->nNumPatrones;i++)
		data->entradas[i] = (double *) malloc (data->nNumEntradas*sizeof(double));


	//Reserva de memoria para las salidas
	data->salidas = (double **)malloc (data->nNumPatrones*sizeof(double *));

	for (int i=0;i<data->nNumPatrones;i++)
		data->salidas[i] = (double *) malloc (data->nNumSalidas*sizeof(double));
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
// Entrenar la red on-line para un determinado fichero de datos
void PerceptronMulticapa::entrenarOnline(Datos* pDatosTrain) {
	int i;
	for(i=0; i<pDatosTrain->nNumPatrones; i++){
		simularRedOnline(pDatosTrain->entradas[i], pDatosTrain->salidas[i]);
	}
}

// ------------------------------
// Probar la red con un conjunto de datos y devolver el error MSE cometido
double PerceptronMulticapa::test(Datos* pDatosTest) {

	double error = 0.0;

	for(int i=0; i<pDatosTest->nNumPatrones; i++)
	{
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		error += calcularErrorSalida(pDatosTest->salidas[i]);

	}

	error /= pDatosTest->nNumPatrones;
	return error;
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
		
		cout << i;

		for (j = 0; j < numSalidas; j++)
			cout << "," << salidas[j];
		cout << endl;

	}
}

// ------------------------------
// Ejecutar el algoritmo de entrenamiento durante un número de iteraciones, utilizando pDatosTrain
// Una vez terminado, probar como funciona la red en pDatosTest
// Tanto el error MSE de entrenamiento como el error MSE de test debe calcularse y almacenarse en errorTrain y errorTest
void PerceptronMulticapa::ejecutarAlgoritmoOnline(Datos * pDatosTrain, Datos * pDatosTest, int maxiter, double *errorTrain, double *errorTest)
{
	int countTrain = 0;
	Datos * valData=new Datos(); //Esctructuras de datos para el conjunto de validacion

	// Inicialización de pesos
	pesosAleatorios();

	double minValError = 0;
	double minTrainError = 0;
	
	int numsinMejorarValidationError;
	int numSinMejorar;
	
	double testError = 0;
	double validationError=0.0;

	// Generar datos de validación
	if(dValidacion > 0 && dValidacion < 1){
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
		
		
		validationError = test(valData);
	}

		std::ofstream leer;
		leer.open("log.txt",ios::app);
	// Aprendizaje del algoritmo
	do {

		
		entrenarOnline(pDatosTrain);
		double trainError = test(pDatosTrain);

	   //Condicion de parada del conjunto de validacion
		if(dValidacion > 0.0 && dValidacion < 1.0){
			entrenarOnline(valData);
			validationError = test(valData);
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
		double testError = test(pDatosTest);
		
		leer<<trainError<<" "<<validationError<<" "<<testError<<endl;

		//Iteracion - Error de entrenamiento - Eror de validacion - Error de Test
		//cout << countTrain << "\t"<< trainError <<"\t"<< validationError <<"\t"<<testError<< endl;

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

	testError = test(pDatosTest);
	*errorTest=testError;
	*errorTrain=minTrainError;

}

// OPCIONAL - KAGGLE
//Guardar los pesos del modelo en un fichero de texto.
bool PerceptronMulticapa::guardarPesos(const char * archivo)
{
	// Objeto de escritura de fichero
	ofstream f(archivo);

	if(!f.is_open())
		return false;

	// Escribir el numero de capas y el numero de neuronas en cada capa en la primera linea.
	f << nNumCapas;

	for(int i = 0; i < nNumCapas; i++)
		f << " " << pCapas[i].nNumNeuronas;
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

	// Leer número de capas.
	f >> nl;

	npl = new int[nl];

	// Leer número de neuronas en cada capa.
	for(int i = 0; i < nl; i++)
		f >> npl[i];

	// Inicializar vectores y demás valores.
	inicializar(nl, npl);

	// Leer pesos.
	for(int i = 1; i < nNumCapas; i++)
		for(int j = 0; j < pCapas[i].nNumNeuronas; j++)
			for(int k = 0; k < pCapas[i-1].nNumNeuronas + 1; k++)
				f >> pCapas[i].pNeuronas[j].w[k];

	f.close();
	delete[] npl;

	return true;
>>>>>>> Stashed changes:modelosComputacionales/p1(Codigo Fuente)/imc/PerceptronMulticapa.cpp
}