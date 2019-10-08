//============================================================================
// Introducción a los Modelos Computacionales
// Name        : practica1.cpp
// Author      : Pedro A. Gutiérrez
// Version     :
// Copyright   : Universidad de Córdoba
//============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ctime>    // Para cojer la hora time()
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <string.h>
#include <math.h>
#include "imc/PerceptronMulticapa.h"

using namespace imc;
using namespace std;

int main(int argc, char **argv) {
	// Procesar los argumentos de la línea de comandos
    bool Tflag = 0, wflag = 0, pflag = 0;
    char *Tvalue = NULL, *wvalue = NULL;
    int c;

    opterr = 0;

    // a: opción que requiere un argumento
    // a:: el argumento requerido es opcional
    while ((c = getopt(argc, argv, "T:w:p")) != -1)
    {
        // Se han añadido los parámetros necesarios para usar el modo opcional de predicción (kaggle).
        // Añadir el resto de parámetros que sean necesarios para la parte básica de las prácticas.
        switch(c){
            case 'T':
                Tflag = true;
                Tvalue = optarg;
                break;
            case 'w':
                wflag = true;
                wvalue = optarg;
                break;
            case 'p':
                pflag = true;
                break;
            case '?':
                if (optopt == 'T' || optopt == 'w' || optopt == 'p')
                    fprintf (stderr, "La opción -%c requiere un argumento.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Opción desconocida `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Caracter de opción desconocido `\\x%x'.\n",
                             optopt);
                return EXIT_FAILURE;
            default:
                return EXIT_FAILURE;
        }
    }

    if (!pflag) {

        ////////////////////////////////////////
        // MODO DE ENTRENAMIENTO Y EVALUACIÓN //
        ///////////////////////////////////////

    	// Objeto perceptrón multicapa
    	PerceptronMulticapa mlp;

    	// Parámetros del mlp. Por ejemplo, mlp.dEta = valorQueSea;

    	// Lectura de datos de entrenamiento y test: llamar a mlp.leerDatos(...)

    	// Inicializar vector topología
    	//int *topologia = new int[capas+2];
    	//topologia[0] = pDatosTrain->nNumEntradas;
    	//for(int i=1; i<(capas+2-1); i++)
    	//	topologia[i] = neuronas;
    	//topologia[capas+2-1] = pDatosTrain->nNumSalidas;

    	// Inicializar red con vector de topología
    	//mlp.inicializar(capas+2,topologia);


        // Semilla de los números aleatorios
        int semillas[] = {1,2,3,4,5};
        double *errores = new double[5];
        double *erroresTrain = new double[5];
        double *ccrs = new double[5];
        double *ccrsTrain = new double[5];
        double mejorErrorTest = 1.0;
        for(int i=0; i<5; i++){
        	cout << "**********" << endl;
        	cout << "SEMILLA " << semillas[i] << endl;
        	cout << "**********" << endl;
    		srand(semillas[i]);
    		mlp.ejecutarAlgoritmo(pDatosTrain,pDatosTest,iteraciones,&(erroresTrain[i]),&(errores[i]),&(ccrsTrain[i]),&(ccrs[i]),error);
    		cout << "Finalizamos => CCR de test final: " << ccrs[i] << endl;

            // (Opcional - Kaggle) Guardamos los pesos cada vez que encontremos un modelo mejor.
            if(wflag && erroresTest[i] <= mejorErrorTest)
            {
                mlp.guardarPesos(wvalue);
                mejorErrorTest = erroresTest[i];
            }

        }


        double mediaError = 0, desviacionTipicaError = 0;
        double mediaErrorTrain = 0, desviacionTipicaErrorTrain = 0;
        double mediaCCR = 0, desviacionTipicaCCR = 0;
        double mediaCCRTrain = 0, desviacionTipicaCCRTrain = 0;

        // Calcular medias y desviaciones típicas de entrenamiento y test


        cout << "HEMOS TERMINADO TODAS LAS SEMILLAS" << endl;

    	cout << "INFORME FINAL" << endl;
    	cout << "*************" << endl;
        cout << "Error de entrenamiento (Media +- DT): " << mediaErrorTrain << " +- " << desviacionTipicaErrorTrain << endl;
        cout << "Error de test (Media +- DT): " << mediaError << " +- " << desviacionTipicaError << endl;
        cout << "CCR de entrenamiento (Media +- DT): " << mediaCCRTrain << " +- " << desviacionTipicaCCRTrain << endl;
        cout << "CCR de test (Media +- DT): " << mediaCCR << " +- " << desviacionTipicaCCR << endl;
    	return EXIT_SUCCESS;
    } else {

        /////////////////////////////////
        // MODO DE PREDICCIÓN (KAGGLE) //
        ////////////////////////////////

        // Desde aquí hasta el final del fichero no es necesario modificar nada.
        
        // Objeto perceptrón multicapa
        PerceptronMulticapa mlp;

        // Inicializar red con vector de topología
        if(!wflag || !mlp.cargarPesos(wvalue))
        {
            cerr << "Error al cargar los pesos. No se puede continuar." << endl;
            exit(-1);
        }

        // Lectura de datos de entrenamiento y test: llamar a mlp.leerDatos(...)
        Datos *pDatosTest;
        pDatosTest = mlp.leerDatos(Tvalue);
        if(pDatosTest == NULL)
        {
            cerr << "El conjunto de datos de test no es válido. No se puede continuar." << endl;
            exit(-1);
        }

        mlp.predecir(pDatosTest);

        return EXIT_SUCCESS;

    }
}

