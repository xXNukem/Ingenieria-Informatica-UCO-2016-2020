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
#include <vector>
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
	//Reserva de memoria para el vector de capas
	pCapas = (Capa *)calloc(nl,sizeof(Capa));

	//Reserva para la primera capa y su numero de neuroas, que se hace independiente porque no tendra sesgo
	pCapas[0].nNumNeuronas = npl[0];
	pCapas[0].pNeuronas = (Neurona *)calloc(npl[0],sizeof(Neurona));

    int aux=0,sesgo=1;
	for(int i = 1; i <nl; i++)//Bucle que usaremos para iniciar las i capas ocultas
	{	
		pCapas[i].nNumNeuronas = npl[i];
		pCapas[i].pNeuronas = (Neurona *)calloc(npl[i],sizeof(Neurona));
		pCapas[i].tipo = 0;//Sigmoide

            //Se recorren las neuronas de la capa oculta i
			for(int j = 0; j < pCapas[i].nNumNeuronas; j++)
			{
			     //Guardamos en aux el numero de neuronas de la capa mas el sesgo, luego se reserva memoria
				aux = npl[i-1]+sesgo;
				pCapas[i].pNeuronas[j].w = (double*)calloc(aux,sizeof(double));           
				pCapas[i].pNeuronas[j].deltaW = (double*)calloc(aux,sizeof(double));        
				pCapas[i].pNeuronas[j].ultimoDeltaW = (double*)calloc(aux,sizeof(double));  
				pCapas[i].pNeuronas[j].wCopia = (double*)calloc(aux,sizeof(double)); 

					//Se rrecorren todas las neuronas mas el sesgo
					for(int k = 0; k < aux; k++)
					{
						pCapas[i].pNeuronas[j].w[k] = 0.0;           
						pCapas[i].pNeuronas[j].deltaW[k] = 0.0;        
						pCapas[i].pNeuronas[j].ultimoDeltaW[k] = 0.0;  
						pCapas[i].pNeuronas[j].wCopia[k] = 0.0; 
					}
					
			}
			aux = 0;
	}

    //Al terminar le decimos a la ultima capa si es de tipo softmax
	if(tipo==true){
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

		for(int j = 0;j<pCapas[i].nNumNeuronas;j++)
		{
			if(i!=0)
            {   //Como la primera capa no tiene inicializado ningun vector la ignoramos aqui
    			free(pCapas[i].pNeuronas[j].w);
    			free(pCapas[i].pNeuronas[j].deltaW);
    			free(pCapas[i].pNeuronas[j].ultimoDeltaW);
    			free(pCapas[i].pNeuronas[j].wCopia);
			}
		}
		//Liberamos el vector de la capa i
		free(pCapas[i].pNeuronas);
	}
	//Liberamos el vector de capas
	free(pCapas);

}

// ------------------------------
// Rellenar todos los pesos (w) aleatoriamente entre -1 y 1
void PerceptronMulticapa::pesosAleatorios() {
//La red se recorre siempre igual
	for(int i = 1; i <nNumCapas; i++)
	{		
		for(int j = 0; j < pCapas[i].nNumNeuronas; j++)
		{
			//Recorremos los vectores de las neuronas de la capa oculta i + el sesgo
			for(int k = 0; k < pCapas[i-1].nNumNeuronas+1; k++)
			{
				double random = (double)rand() / RAND_MAX;
    			double random2 = (-1.0) + random * ((1.0) - (-1.0));
				pCapas[i].pNeuronas[j].w[k] = random2;           
				pCapas[i].pNeuronas[j].wCopia[k] = random2; 
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

    //nNumCapas-1 es la ultima
    //Se recorre la ultima capa y recojemos sus salidas
	for (int i = 0; i < pCapas[nNumCapas-1].nNumNeuronas; i++)
	{
		output[i] = pCapas[nNumCapas-1].pNeuronas[i].x;
	}

}

// ------------------------------
// Hacer una copia de todos los pesos (copiar w en copiaW)
void PerceptronMulticapa::copiarPesos() {

	for(int i = 1; i <nNumCapas; i++)
	{		
		for(int j = 0; j < pCapas[i].nNumNeuronas; j++)
		{			
			for(int k = 0; k < pCapas[i-1].nNumNeuronas+1; k++)
			{
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
		for(int j = 0; j < pCapas[i].nNumNeuronas; j++)
		{
			for(int k = 0; k < pCapas[i-1].nNumNeuronas+1; k++)
			{
				pCapas[i].pNeuronas[j].w[k] = pCapas[i].pNeuronas[j].wCopia[k];
			}		
		}
	}
}

// ------------------------------
// Calcular y propagar las salidas de las neuronas, desde la primera capa hasta la última
void PerceptronMulticapa::propagarEntradas() {

	double sumatorio=0.0;
	double acumuladorSoftmax = 0.0; //Varaible acumuladora para el sumatorio de softmax
	double capaSoftmax[pCapas[nNumCapas-1].nNumNeuronas]; //Se declara un vector para el tipo softmax con el numero de neuronas de la ultima capa

	for (int i = 1; i <nNumCapas; i++)
	{
		
		for (int j = 0; j < pCapas[i].nNumNeuronas; j++)
		{
		
			for (int k = 1; k < pCapas[i-1].nNumNeuronas+1; k++)
			{
				// [k-1].x , porque de la capa anterior tenemos que empezar por la neurona 0

                //hacemos [k-1].x para empezar por la salida de la neurona 0 de la capa anterior

		                                                                          //Aqui empezamos en k=1 par ano tener en cuenta el peso del sesgo w[0]
				sumatorio += pCapas[i-1].pNeuronas[k-1].x*pCapas[i].pNeuronas[j].w[k];

			}
			//Aqui tenemos en cuenta el sesgo
			sumatorio += pCapas[i].pNeuronas[j].w[0];
			
			//Realizamos el calculo de la presentacion de la practica en caso de que estemos en la ultima capa y sea softmax
			if(i == nNumCapas-1 && pCapas[nNumCapas-1].tipo == 1)
            {
				capaSoftmax[j] = exp(sumatorio);
				acumuladorSoftmax += exp(sumatorio);
			}
            else
            {
				pCapas[i].pNeuronas[j].x = (1/(1 + exp((-1)*sumatorio)));
			}
			
			sumatorio = 0.0;
		}
	}

	//Calculamos la salida de la capa softmax
	if(pCapas[nNumCapas-1].tipo == 1)
    {
		for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++)
        {
			pCapas[nNumCapas-1].pNeuronas[i].x = capaSoftmax[i]/acumuladorSoftmax;
		}
	}

}

// ------------------------------
// Calcular el error de salida del out de la capa de salida con respecto a un vector objetivo y devolverlo
// funcionError=1 => EntropiaCruzada // funcionError=0 => MSE
double PerceptronMulticapa::calcularErrorSalida(double* target, int funcionError) {

    //El error puede ser entropia cruzada o mse, se utilizan los calculos de la presentacion de la practica
	double error=0.0;

	if(funcionError==0)//MSE
    {
		for (int i = 0; i<pCapas[nNumCapas-1].nNumNeuronas; i++)
		{
			error += pow(target[i] - pCapas[nNumCapas-1].pNeuronas[i].x, 2);
		}
		error=error/pCapas[nNumCapas-1].nNumNeuronas;
	}
    else //Entropia cruzada
    {
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
void PerceptronMulticapa::retropropagarError(double* objetivo, int funcionError) {

	//tipo 0 sigmoide, 1 softmax
	//funcionError 0 MSE , 1 Entropia cruzada

	double sumatorioEntradas =0.0,sumatorioSoftmax=0.0;


	if(pCapas[nNumCapas-1].tipo == 0)//Sigmoide
	{
		for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++)
		{
			if(funcionError == 0)//MSE
			{
				pCapas[nNumCapas-1].pNeuronas[i].dX =  (-1)*(objetivo[i] - pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[i].x);
			}
            else//Entropia Cruzada
			{
				pCapas[nNumCapas-1].pNeuronas[i].dX =  (-1)*(objetivo[i]/pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[i].x);
			}
		}
	}
    else//Softmax 
	{

		for(int i = 0; i < pCapas[nNumCapas-1].nNumNeuronas; i++)
		{
			for(int j = 0; j < pCapas[nNumCapas-1].nNumNeuronas; j++)
			{
				
				if (i==j)//Derivada de la salida Oj respecto a algo que esta por detras de la neurona j(diapositiva 16)
				{
					if(funcionError==0)//mse
					{
						sumatorioSoftmax += (objetivo[j]-pCapas[nNumCapas-1].pNeuronas[j].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[j].x);
					}
                    else//Entropia cruzada
					{
						sumatorioSoftmax += (objetivo[j]/pCapas[nNumCapas-1].pNeuronas[j].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[j].x);
					}

				}
                else//Derivada de la salida Oj respecto a algo que est ́a por detras de cualquier neurona i que no sea j (diapositiva 17)
				{
					if(funcionError==0)//mse
					{
						sumatorioSoftmax += (objetivo[j]-pCapas[nNumCapas-1].pNeuronas[j].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (0 - pCapas[nNumCapas-1].pNeuronas[j].x);
					}
                    else//entropia cruzada
					{
						sumatorioSoftmax += (objetivo[j]/pCapas[nNumCapas-1].pNeuronas[j].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (0 - pCapas[nNumCapas-1].pNeuronas[j].x);
					}

				}
				
			}

			pCapas[nNumCapas-1].pNeuronas[i].dX = (-1)*sumatorioSoftmax; //importante el signo de la derivada

			sumatorioSoftmax = 0.0;
		}
		
	}

	for(int i=nNumCapas-2; i>=0; i--)
	{
		for(int j=0; j<pCapas[i].nNumNeuronas; j++)
		{
			//Se calcula el sumatorio de las entradas y su derivada en la siguiente capa
			for(int k=0; k<pCapas[i+1].nNumNeuronas; k++)
			{
				sumatorioEntradas += pCapas[i+1].pNeuronas[k].w[j+1] * pCapas[i+1].pNeuronas[k].dX;
			}

			pCapas[i].pNeuronas[j].dX = sumatorioEntradas * pCapas[i].pNeuronas[j].x * (1-pCapas[i].pNeuronas[j].x);

			sumatorioEntradas = 0.0;
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
	
	double deltaWaux,ultimoDetalWaux;
	float eta = 0.0;
	for(int i=1; i<nNumCapas; i++)
	{
		
		for(int j=0; j<pCapas[i].nNumNeuronas; j++)
		{
			eta=this->dEta*pow(this->dDecremento, -(this->nNumCapas-1-i)); //Hacerla auxiliar porque no funciona la validacion 
			for(int k=0; k<pCapas[i-1].nNumNeuronas+1; k++)
			{
				deltaWaux = pCapas[i].pNeuronas[j].deltaW[k];

				ultimoDetalWaux = pCapas[i].pNeuronas[j].ultimoDeltaW[k];
				
				if(bOnline)//Online
				{
					pCapas[i].pNeuronas[j].w[k] -= eta * deltaWaux + dMu * eta * ultimoDetalWaux;
					pCapas[i].pNeuronas[j].ultimoDeltaW[k] = pCapas[i].pNeuronas[j].deltaW[k];
				}
                else
                {
					pCapas[i].pNeuronas[j].w[k] -= eta * (deltaWaux/int(nNumPatronesTrain)) + dMu * eta * (ultimoDetalWaux/int(nNumPatronesTrain)); //Hay que dividir por el numero de patrones (media de error)
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
void PerceptronMulticapa::entrenar(Datos* pDatosTrain, int funcionError) {

	if(!bOnline){

		for (int i = 1; i < nNumCapas; i++)
		{
		
			for (int j = 0; j < pCapas[i].nNumNeuronas; j++)
			{

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

	double error = 0.0;

	for(int i=0; i<pDatosTest->nNumPatrones; i++)
	{
		// Cargamos las entradas y propagamos el valor
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		error += calcularErrorSalida(pDatosTest->salidas[i],funcionError);

	}

	if(funcionError == 0)//MSE
	{
		error /= pDatosTest->nNumPatrones;
	}
    else//ENtropia cruzada
	{
		error /= (-1)*pDatosTest->nNumPatrones * pCapas[nNumCapas-1].nNumNeuronas;
	}
	
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

    matrizConfusion=std::vector<std::vector<int> >(pDatosTest->nNumSalidas, std::vector< int >(pDatosTest->nNumSalidas,0)); //MATRIZ DE CONFUSION
	double ccr = 0.0;
    std::vector<int> patronesMalClasificados;
    double maximoTest = 0.0;
    double maximoNeurona = 0.0;

    //Compararemos los indices declarados a continuacion y cuando concuerden el patron estará bien clasificado
	int indiceVectorTestSalidas = 0;
	int indiceNeuronaMayorSalida = 0;


	for(int i=0; i<pDatosTest->nNumPatrones; i++)
    {
		indiceNeuronaMayorSalida = 0;
		indiceVectorTestSalidas = 0;
		maximoTest = 0.0;
		maximoNeurona = 0.0;
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		


		for(int j=0; j<pCapas[nNumCapas-1].nNumNeuronas; j++)
        {
            //Busqueda de la maxima salida de las neuronas, que se comparará con el indice que devuelve la salida
			if(pCapas[nNumCapas-1].pNeuronas[j].x > maximoNeurona)
            {
				maximoNeurona = pCapas[nNumCapas-1].pNeuronas[j].x;
				indiceNeuronaMayorSalida = j;
			}
            //Busqueda del maximo de la salida de test para comparar con el indice anterior
			if(pDatosTest->salidas[i][j] > maximoTest)
            {
				maximoTest = pDatosTest->salidas[i][j];
				indiceVectorTestSalidas = j;
			}
		}
        matrizConfusion[indiceNeuronaMayorSalida][indiceVectorTestSalidas]++;

        //Si los indices coinciden ese patron esta bien clasificado
		if(indiceNeuronaMayorSalida == indiceVectorTestSalidas)
        { 
			ccr++;
		}
        else
        {
            patronesMalClasificados.push_back(i);
        }
	}
    /*
    cout << "Matriz de confusion" << endl;
    cout << "=========================================" << endl;
    for(int i=0;i<pDatosTest->nNumSalidas;i++)
    {
        for(int j=0;j<pDatosTest->nNumSalidas;j++)
        {
            cout<<"["<<matrizConfusion[i][j]<<"]"<<"\t";
        }
        cout<<endl;
    }
    for (int i = 0; i < patronesMalClasificados.size(); ++i)
    {
        cout<<"["<<patronesMalClasificados[i]<<"]";
    }
    cout<<endl;
    */

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

    Datos * pDatosValidacion = new Datos(); 

	int numSinMejorar = 0;
	int numSinMejorarValidationError = 0;

	double testError = 0.0;
	double validationError = 0.0;
    double minTrainError = 0.0;
    double minValError = 0.0;	

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
				numSinMejorarValidationError = 0;
			}else if( (validationError-minValError) < 0.00001)
			{
				numSinMejorarValidationError=0;
			}
			else{
				numSinMejorarValidationError++;
			}

			if(numSinMejorarValidationError==50){
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
		//cout << countTrain << "\t" << trainError << "\t" << testError << "\t" << validationError << endl;
        cout<<testClassification(pDatosTrain)<<"\t"<<testClassification(pDatosTest)<<"\t"<<testClassification(pDatosValidacion)<<endl;

	} while ( countTrain<maxiter );

	if ( (numSinMejorarValidationError!=50) && (numSinMejorar!=50))
		restaurarPesos();

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
			cout << pDatosTest->salidas[i][j] << " -- " << prediccion[j] << " -- " ;
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