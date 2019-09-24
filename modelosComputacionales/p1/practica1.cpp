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
#include <ctime>    // Para coger la hora time()
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <string.h>
#include <math.h>
#include "imc/PerceptronMulticapa.h"


using namespace imc;
using namespace std;

int main(int argc, char **argv) {
    // Procesar los argumentos de la línea de comandos
    bool Tflag = 0, wflag = 0, pflag = 0;
    char *Tvalue = NULL, *wvalue = NULL, *tvalue=NULL;
    int c;

    //valores iniciales

    float dEta=0.10;
    float dMu=0.90;
    float dValidacion=0.0;
    float dDecremento=1;
    int numIteraciones=1000;
    int numCapasOcultas=1;
    int numNeuronasCapasOcultas=5;

    opterr = 0;

    // a: opción que requiere un argumento
    // a:: el argumento requerido es opcional
    while ((c = getopt(argc, argv, "t:i::l::h::e::m::v::d::")) != -1)
    {
        // Se han añadido los parámetros necesarios para usar el modo opcional de predicción (kaggle).
        // Añadir el resto de parámetros que sean necesarios para la parte básica de las prácticas.
        switch(c){
            case 't': 
            //fichero con datos de entrenamiento
            tvalue=optarg;
                if(tvalue==NULL)
                {
                    cout<< " Es olbigatorio el paso de un fichero en el argumento t"<<endl;
                    exit(0);
                }
            break;

            case 'i':
            //numero de interaciones del bucle externo, sino se especifica vale 1000
            numIteraciones=atoi(optarg);

            break;

            case 'l':
            //capas ocultas de la red, si no se especifica utilizamos 1
            numCapasOcultas=atoi(optarg);
            break;

            case 'h':
            //neuronas de las capas ocultas, si no se especifica utilizaar 5
            numNeuronasCapasOcultas=atoi(optarg);
            break;

            case 'e':
            ////valor de eta, sino se especifica utilizar 0.1
            dEta=atof(optarg);
            break;

            case 'm':
            // valor de mu, si no se especifica utilizar 0.9
            dMu=atof(optarg);
            break;

            case 'v':
            //ratio de patrones de entrenamiento a utilizar como patrones de validacion
            //si no se especifica utilizar 0.0
            dValidacion=atof(optarg);

            break;

            case 'd':
            //valor por defecto del decremento, por defecto utilizar 1
            dDecremento=atoi(optarg);
            break;


        //Parametros opcionales de prediccion
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
        mlp.dEta=dEta;
        mlp.dMu=dMu;
        mlp.dValidacion=dValidacion;
        mlp.dDecremento=dDecremento;
        int iteraciones=numIteraciones;
        
        // Lectura de datos de entrenamiento y test: llamar a mlp.leerDatos(...)
        Datos *pDatosTrain;
        Datos *pDatosTest;
        pDatosTrain=mlp.leerDatos(tvalue);
        
        // Inicializar vector topología
        /*int *topologia = new int[capas+2];
        topologia[0] = pDatosTrain->nNumEntradas;
        for(int i=1; i<(capas+2-1); i++)
        	topologia[i] = neuronas;
        topologia[capas+2-1] = pDatosTrain->nNumSalidas;

        // Inicializar red con vector de topología
        mlp.inicializar(capas+2,topologia);*/


        // Semilla de los números aleatorios
        int semillas[] = {100,200,300,400,500};
        double *erroresTest = new double[5];
        double *erroresTrain = new double[5];
        double mejorErrorTest = 1.0;
        for(int i=0; i<5; i++){
        	cout << "**********" << endl;
        	cout << "SEMILLA " << semillas[i] << endl;
        	cout << "**********" << endl;
    		srand(semillas[i]);
    		mlp.ejecutarAlgoritmoOnline(pDatosTrain,pDatosTest,iteraciones,&(erroresTrain[i]),&(erroresTest[i]));
    		cout << "Finalizamos => Error de test final: " << erroresTest[i] << endl;

            // (Opcional - Kaggle) Guardamos los pesos cada vez que encontremos un modelo mejor.
            if(wflag && erroresTest[i] <= mejorErrorTest)
            {
                mlp.guardarPesos(wvalue);
                mejorErrorTest = erroresTest[i];
            }
    	}

        cout << "HEMOS TERMINADO TODAS LAS SEMILLAS" << endl;

        double mediaErrorTest = 0, desviacionTipicaErrorTest = 0;
        double mediaErrorTrain = 0, desviacionTipicaErrorTrain = 0;
        
        // Calcular medias y desviaciones típicas de entrenamiento y test

        cout << "INFORME FINAL" << endl;
        cout << "*************" << endl;
        cout << "Error de entrenamiento (Media +- DT): " << mediaErrorTrain << " +- " << desviacionTipicaErrorTrain << endl;
        cout << "Error de test (Media +- DT):          " << mediaErrorTest << " +- " << desviacionTipicaErrorTest << endl;
        return EXIT_SUCCESS;
    }
    else {

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

