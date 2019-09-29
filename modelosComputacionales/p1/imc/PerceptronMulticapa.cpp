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

	dEta=0.1;
	dMu=0.9;
	pCapas=NULL;
	nNumCapas=3;
}

// ------------------------------
// Reservar memoria para las estructuras de datos
void PerceptronMulticapa::inicializar(int nl, int npl[]) {

	//Reserva de memoria para el vector de capas
	pCapas=(Capa* )malloc(nl*sizeof(Capa));

	//Reserva de memporia para la capa de entrada, lo hacemos aqui porque esta capa no dispondrá de sesgo
	pCapas[0].nNumNeuronas=npl[0];
	pCapas[0].pNeuronas=(Neurona* )malloc(npl[0]*sizeof(Neurona));

		int aux=0,sesgo=1;
		//Reserva de memoria para las capas ocultas
		for(int i=1; i<nl;i++)
		{	
			//Iniciando de las capas ocultas a la ultima
			pCapas[i].nNumNeuronas=npl[i];
			pCapas[i].pNeuronas=(Neurona *)malloc(npl[i]*sizeof(Neurona));

				for(int j=0;j<pCapas[i].nNumNeuronas;j++)
				{
						aux=npl[i-1]+sesgo; //guardamos en aux el numero de neuronas de la capa mas el sesgo
						pCapas[i].pNeuronas[j].w=(double* )malloc(aux*sizeof(double));
						pCapas[i].pNeuronas[j].deltaW=(double* )malloc(aux*sizeof(double));
						pCapas[i].pNeuronas[j].ultimoDeltaW=(double* )malloc(aux*sizeof(double));
						pCapas[i].pNeuronas[j].wCopia=(double* )malloc(aux*sizeof(double));

						for(int k=0;k<aux;k++)
						{
							pCapas[i].pNeuronas[j].w[k]=0.0;
							pCapas[i].pNeuronas[j].deltaW[k]=0.0;
							pCapas[i].pNeuronas[j].ultimoDeltaW[k]=0.0;
							pCapas[i].pNeuronas[j].wCopia[k]=0.0;
						}
				}

			aux=0;
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

	for(int i=0;i<nNumCapas;i++)//Recorremos todas las capas liberando memoria en todos los arrays que tienen sus estructuras de datos
	{
		for(int j=0;j<pCapas[i].nNumNeuronas;j++)
		{
			if(i!=0)//La primera capa no se toca porque no tiene nada
			{
				free(pCapas[i].pNeuronas[j].w);
				free(pCapas[i].pNeuronas[j].deltaW);
				free(pCapas[i].pNeuronas[j].ultimoDeltaW);
				free(pCapas[i].pNeuronas[j].wCopia);
			}
		}
		free(pCapas[i].pNeuronas);
	}

}

// ------------------------------
// Rellenar todos los pesos (w) aleatoriamente entre -1 y 1
void PerceptronMulticapa::pesosAleatorios() {

	for(int i=1;i<nNumCapas;i++)
	{
		for(int j=0;j<pCapas[i].nNumNeuronas;j++)
		{
			for(int k=0;k<pCapas[i-1].nNumNeuronas+1;k++)
			{
				double RANDOM=(double)rand()/RAND_MAX;//Generacion y asignacion de los pesos aleatorios
				double numero=(-1.0)+RANDOM*((1.0)-(-1.0));

				pCapas[i].pNeuronas[j].w[k]=numero;
				pCapas[i].pNeuronas[j].deltaW[k]=numero;
			}
		}
	}

}

// ------------------------------
// Alimentar las neuronas de entrada de la red con un patrón pasado como argumento
void PerceptronMulticapa::alimentarEntradas(double* input) {

    for(int i=0; i<pCapas[0].nNumNeuronas; i++)
    {
        //Tenemos que tener en cuenta que solo es la capa de entrada
        pCapas[0].pNeuronas[i].x = input[i];
        pCapas[0].pNeuronas[i].dX = input[i];
    }
}

// ------------------------------
// Recoger los valores predichos por la red (out de la capa de salida) y almacenarlos en el vector pasado como argumento
void PerceptronMulticapa::recogerSalidas(double* output)
{
    //La salida "x" se guarda en el vector output
    for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++)
    {
        output[i] = pCapas[nNumCapas-1].pNeuronas[i].x;
    }
}

// ------------------------------
// Hacer una copia de todos los pesos (copiar w en copiaW)
void PerceptronMulticapa::copiarPesos() {

	for(int i=1;i<nNumCapas;i++)
		{
			for(int j=0;j<pCapas[i].nNumNeuronas;j++)
			{
				for(int k=0;k<pCapas[i-1].nNumNeuronas+1;k++)
				{
					pCapas[i].pNeuronas[j].wCopia[k]=pCapas[i].pNeuronas[j].w[k];
				}
			}
		}
}

// ------------------------------
// Restaurar una copia de todos los pesos (copiar copiaW en w)
void PerceptronMulticapa::restaurarPesos() {

        for(int i=1;i<nNumCapas;i++)
		{
			for(int j=0;j<pCapas[i].nNumNeuronas;j++)
			{
				for(int k=0;k<pCapas[i-1].nNumNeuronas+1;k++)
				{
					pCapas[i].pNeuronas[j].w[k]=pCapas[i].pNeuronas[j].wCopia[k];
				}
			}
		}
}

// ------------------------------
// Calcular y propagar las salidas de las neuronas, desde la primera capa hasta la última
void PerceptronMulticapa::propagarEntradas() {
	
}

// ------------------------------
// Calcular el error de salida (MSE) del out de la capa de salida con respecto a un vector objetivo y devolverlo
double PerceptronMulticapa::calcularErrorSalida(double* target) {
    double aux = 0.0;
    for(int i=1; i<nNumCapas; i++){
        for(int j=0; j<pCapas[i].nNumNeuronas; j++)
        {

            for(int k=1; k<pCapas[i-1].nNumNeuronas+1; k++)
            {
                aux += pCapas[i].pNeuronas[j].w[k] * pCapas[i-1].pNeuronas[k-1].x;
            }

                aux += pCapas[i].pNeuronas[j].w[0];

            pCapas[i].pNeuronas[j].x = (1/(1 + exp((-1)*aux)));
            aux = 0.0;
        }
    }
	return -1;
}


// ------------------------------
// Retropropagar el error de salida con respecto a un vector pasado como argumento, desde la última capa hasta la primera
void PerceptronMulticapa::retropropagarError(double* objetivo) {

    //Primero se hace para cada neurona de salida

    for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++){
        pCapas[nNumCapas-1].pNeuronas[i].dX =  (-1)*(objetivo[i] - pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[i].x);
    }

    double sumatorio = 0.0;

    //Despues aplicamos el procedimiento al resto de capas
    for(int i=nNumCapas-2; i>=0; i--){//Recorremos las capas
        for(int j=0; j<pCapas[i].nNumNeuronas; j++){//Recorremos las neuronas de cada capa
            //Calculamos el sumatorio de las entradas y la derivada de la capa siguiente
            for(int k=0; k<pCapas[i+1].nNumNeuronas; k++){//pasamos por las neuronas de la capa h+1 Calculando el sumatorio de las entradas
                                                            //Calculamos la derivada de la capa siguiente ya de paso
                sumatorio += pCapas[i+1].pNeuronas[k].w[j+1] * pCapas[i+1].pNeuronas[k].dX;
            }

            pCapas[i].pNeuronas[j].dX = sumatorio * pCapas[i].pNeuronas[j].x * (1 -pCapas[i].pNeuronas[j].x);
        }
    }
	
}

// ------------------------------
// Acumular los cambios producidos por un patrón en deltaW
void PerceptronMulticapa::acumularCambio() {

    //Recorremos las capas y las neuronas de la misma forma que siempre
    for(int i=1; i<nNumCapas; i++){
        for(int j=0; j<pCapas[i].nNumNeuronas; j++){
            for(int k=1; k<pCapas[i-1].nNumNeuronas+1; k++){
                pCapas[i].pNeuronas[j].deltaW[k] +=  pCapas[i].pNeuronas[j].dX * pCapas[i-1].pNeuronas[k-1].x;
            }

            pCapas[i].pNeuronas[j].deltaW[0] += pCapas[i].pNeuronas[j].dX; //Sesgo
        }
    }

}

// ------------------------------
// Actualizar los pesos de la red, desde la primera capa hasta la última
void PerceptronMulticapa::ajustarPesos() {
    for(int i=1; i<nNumCapas; i++){
        for(int j=0; j<pCapas[i].nNumNeuronas; j++){

            for(int k=1; k<pCapas[i-1].nNumNeuronas+1; k++){
                pCapas[i].pNeuronas[j].w[k] += (-1)*dEta * pCapas[i].pNeuronas[j].deltaW[k] - dMu * (dEta*pCapas[i].pNeuronas[j].ultimoDeltaW[k]);
            }

            pCapas[i].pNeuronas[j].w[0] += (-1)*dEta * pCapas[i].pNeuronas[j].deltaW[0] - dMu * (dEta*pCapas[i].pNeuronas[j].ultimoDeltaW[0]);//Sesgo
        }
    }

}

// ------------------------------
// Imprimir la red, es decir, todas las matrices de pesos
void PerceptronMulticapa::imprimirRed() {
    cout << "Entradas de las neuronas" << endl << endl;

    for(int i=1; i<nNumCapas; i++)
    {
        cout << "Capa: " << i << endl;
        for(int j=0; j<pCapas[i].nNumNeuronas; j++)
        {
            for(int k=0; k<pCapas[i-1].nNumNeuronas; k++)
            {
                cout << pCapas[i].pNeuronas[j].w[k] << " ";
            }
            cout << endl;

        }
    }
}

// ------------------------------
// Simular la red: propagar las entradas hacia delante, retropropagar el error y ajustar los pesos
// entrada es el vector de entradas del patrón y objetivo es el vector de salidas deseadas del patrón
void PerceptronMulticapa::simularRedOnline(double* entrada, double* objetivo) {
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
    alimentarEntradas(entrada);
    propagarEntradas();
    retropropagarError(objetivo);
    acumularCambio();
    ajustarPesos();
}

// ------------------------------
// Leer una matriz de datos a partir de un nombre de fichero y devolverla
Datos* PerceptronMulticapa::leerDatos(const char *archivo) {

	Datos *datosAux;
	int entradas,salidas,patrones;

		ifstream leer;
		leer.open(archivo);

	leer >> entradas;
	leer >> salidas;
	leer >> patrones;

		datosAux->nNumEntradas=entradas;
		datosAux->nNumSalidas=salidas;
		datosAux->nNumPatrones=patrones;

	//Reservando memoria para la matriz de entrada

	//Filas	
	datosAux->entradas=(double** )malloc(patrones*sizeof(double*));
	//Columnas
	for(int i=0;patrones;i++)
	datosAux->entradas[i]=(double* )malloc(entradas*sizeof(double));

	//reservando memoria para la matriz de salida
	
	//Filas
	datosAux->salidas=(double** )malloc(patrones*sizeof(double*));
	//Columnas
	for(int i=0;datosAux->nNumPatrones;i++)
	datosAux->salidas[i]=(double* )malloc(salidas*sizeof(double));

	//Metiendo los datos en la matriz
	int i=0,j=0;
	while(!leer.eof())
	{
		for(int x=0;x<entradas;x++)
		{
			leer>>datosAux->entradas[i][x];
		}

		for(int y=0;y<salidas;y++)
		{
			leer>>datosAux->salidas[j][y];
		}
		i++;
		j++;
	}

	leer.close();

	return datosAux;
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
	return -1.0;
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

	// Inicialización de pesos
	pesosAleatorios();

	double minTrainError = 0;
	int numSinMejorar;
	double testError = 0;

	double validationError;

	// Generar datos de validación
	if(dValidacion > 0 && dValidacion < 1){
		// .......
	}


	// Aprendizaje del algoritmo
	do {

		entrenarOnline(pDatosTrain);
		double trainError = test(pDatosTrain);
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

		countTrain++;

		// Comprobar condiciones de parada de validación y forzar
		// OJO: en este caso debemos guardar el error de validación anterior, no el mínimo
		// Por lo demás, la forma en que se debe comprobar la condición de parada es similar
		// a la que se ha aplicado más arriba para el error de entrenamiento

		cout << "Iteración " << countTrain << "\t Error de entrenamiento: " << trainError << "\t Error de validación: " << validationError << endl;

	} while ( countTrain<maxiter );

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
}