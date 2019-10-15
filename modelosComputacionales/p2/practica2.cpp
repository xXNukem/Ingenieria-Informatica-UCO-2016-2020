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
    bool Tflag = 0, wflag = 0, pflag = 0,tflag=0;
    char *Tvalue = NULL, *wvalue = NULL, *tvalue=NULL;
    int c;

    //Valores Con el valor predeterminado
        float dEta = 0.70;
        float dMu = 1;
        float dValidacion = 0.0;
        float dDecremento = 1;
        int numIteraciones=1000;
        int numcapasOcultas=1;
        int numNeuronasCapaOculta=5;
        //Parametros por defecto de la practica2
        bool online=false;
        bool funcError=false;
        bool funcActiv=false;

    opterr = 0;

    // a: opción que requiere un argumento
    // a:: el argumento requerido es opcional
    while ((c = getopt(argc, argv, "t:i:l:h:e:m:v:d:T:f::o::s::")) != -1)
    {
        // Se han añadido los parámetros necesarios para usar el modo opcional de predicción (kaggle).
        // Añadir el resto de parámetros que sean necesarios para la parte básica de las prácticas.
        switch(c){

            case 't':
            //fichero train
                tflag = true;
                tvalue = optarg;
                break;
            case 'i':
            //numero de iteraciones
                numIteraciones = atoi(optarg);
                break;
            case 'l':
            //numero de capas ocultas
                numcapasOcultas = atoi(optarg);
                if(numcapasOcultas < 1)
                {
                    cout<<" El numero de capa oculta tiene que ser mayor que 1.\n";
                    exit(-1);
                }
                break;
            case 'h':
            //neuronas en capa oculta
                numNeuronasCapaOculta = atoi(optarg);
                if(numNeuronasCapaOculta < 1)
                {
                    cout<<" El numero de neuronas en capa oculta tiene que ser mayor que 1.\n";
                    exit(-1);
                }
                break;
            case 'e':
            //valor parametro eta
                dEta = atof(optarg);
                break;
            case 'm':
            //valor parametro mu
                dMu = atof(optarg);;
                break;
            case 'v':
            //conjunto de validacion a utilizar
                dValidacion = atof(optarg);;
                break;
            case 'd':
            //factor de decremento
                dDecremento = atof(optarg);;
                break; 
            //Conjunto de test  
            case 'T':
                Tflag = true;
                Tvalue = optarg;
                break;
            case 'o':
                //Booleano que indica si se utiliza entrenamiento online y offline por defecto offline (FALSE)
                online=true;
                break;

            case 'f':
                //Boleano que indica que funcion de error se va a utilizar 0 para MSE y 1 para ENtropia, por defecto MSE(FALSE)
                funcError=true;
                break;
            case 's':
                //Boleano que indica la funcion de activacion si es softmax o sigmoide. por defecto sigmoide (FALSE)
                funcActiv=true;
                break;
            case 'w':
                wflag = true;
                wvalue = optarg;
                break;
            case 'p':
                pflag = true;
                break;
            case '?':
                if (optopt == 'T' || optopt == 'w' || optopt == 'p' || optopt == 't' || optopt == 'i')
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

    if (!pflag) 
    {

        ////////////////////////////////////////
        // MODO DE ENTRENAMIENTO Y EVALUACIÓN //
        ///////////////////////////////////////

    	// Lectura de datos de entrenamiento y test: llamar a mlp.leerDatos(...)
        if(tflag == false)
        {
            exit(-1);
        } 
    
        if(Tflag==false){
            Tvalue=tvalue; //Si no se mete un T le pasamos la t
        }
        // Objeto perceptrón multicapa
        PerceptronMulticapa mlp;
        // Parámetros del mlp. Por ejemplo, mlp.dEta = valorQueSea;
        mlp.dEta = dEta;
        mlp.dMu = dMu;
        mlp.dValidacion = dValidacion;
        mlp.dDecremento = dDecremento;
        mlp.bOnline=online;
        // Lectura de datos de entrenamiento y test: llamar a mlp.leerDatos(...)
        Datos *pDatosTrain;
        Datos *pDatosTest;
    
        pDatosTrain = mlp.leerDatos(tvalue);
        pDatosTest = mlp.leerDatos(Tvalue);
   
        if(pDatosTrain == NULL || pDatosTest == NULL)
        {
            cerr << "El conjunto de datos de test no es válido. No se puede continuar." << endl;
            exit(-1);
        }

    	// Inicializar vector topología
    	int *topologia = new int[numcapasOcultas+2];
    	topologia[0] = pDatosTrain->nNumEntradas;
    	for(int i=1; i<(numcapasOcultas+1); i++)
    		topologia[i] = numNeuronasCapaOculta;
    	topologia[numcapasOcultas+1] = pDatosTrain->nNumSalidas;

    	// Inicializar red con vector de topología
    	mlp.inicializar(numcapasOcultas+2,topologia,funcActiv);


        // Semilla de los números aleatorios
        int semillas[] = {1,2,3,4,5};
        double *erroresTest = new double[5];
        double *erroresTrain = new double[5];
        double *ccrsTest = new double[5];
        double *ccrsTrain = new double[5];
        //double mejorErrorTest = 1.0;
        int contVueltas=0;
            for(int i=0; i<5; i++)
            {
            	cout << "**********" << endl;
            	cout << "SEMILLA " << semillas[i] << endl;
            	cout << "**********" << endl;
        		srand(semillas[i]);
        		mlp.ejecutarAlgoritmo(pDatosTrain,pDatosTest,numIteraciones,&(erroresTrain[i]),&(erroresTest[i]),&(ccrsTrain[i]),&(ccrsTest[i]),funcError);
        		cout << "Finalizamos => CCR de test final: " << ccrsTest[i] << endl;

                    // (Opcional - Kaggle) Guardamos los pesos cada vez que encontremos un modelo mejor.
                   /* if(wflag && erroresTest[i] <= mejorErrorTest)
                    {
                        mlp.guardarPesos(wvalue);
                        mejorErrorTest = erroresTest[i];
                    }

                }*/


                double mediaErrorTest = 0, desviacionTipicaErrorTest = 0;
                double mediaErrorTrain = 0, desviacionTipicaErrorTrain = 0;
                double mediaCCRTest = 0, desviacionTipicaCCRTest = 0;
                double mediaCCRTrain = 0, desviacionTipicaCCRTrain = 0;

                // Calcular medias y desviaciones típicas de entrenamiento y test

                //medias
                for(int i=0; i<5; i++)
                {
                    mediaErrorTrain += erroresTrain[i];
                    mediaErrorTest += erroresTest[i];
                    mediaCCRTest += ccrsTest[i];
                    mediaCCRTrain += ccrsTrain[i];
                }
                    mediaErrorTest /= 5;
                    mediaErrorTrain /= 5;
                    mediaCCRTest/=5;
                    mediaCCRTrain /=5;

                //Desviacion tipica
                double auxTest = 0.0, auxTrain=0.0, auxCCRtrain=0.0, auxCCRtest=0.0;

                for(int i=0; i<5; i++)
                {
                    auxTest += pow(erroresTest[i] - mediaErrorTest,2);
                    auxTrain += pow(erroresTrain[i] - mediaErrorTrain, 2);
                    auxCCRtest+=pow(ccrsTest[i]-mediaCCRTest,2);
                    auxCCRtrain+=pow(ccrsTrain[i]-mediaCCRTrain,2);
                }
                    desviacionTipicaErrorTest = sqrt(auxTest);
                    desviacionTipicaErrorTrain = sqrt(auxTrain);
                    desviacionTipicaCCRTest=sqrt(auxCCRtest);
                    desviacionTipicaCCRTrain=sqrt(auxCCRtrain);


            cout << "HEMOS TERMINADO TODAS LAS SEMILLAS" << endl;

        	cout << "INFORME FINAL" << endl;
        	cout << "*************" << endl;
            cout << "Error de entrenamiento (Media +- DT): " << mediaErrorTrain << " +- " << desviacionTipicaErrorTrain << endl;
            cout << "Error de test (Media +- DT): " << mediaErrorTest << " +- " << desviacionTipicaErrorTest << endl;
            cout << "CCR de entrenamiento (Media +- DT): " << mediaCCRTrain << " +- " << desviacionTipicaCCRTrain << endl;
            cout << "CCR de test (Media +- DT): " << mediaCCRTest << " +- " << desviacionTipicaCCRTest << endl;
            contVueltas++;
            cout<<"Se han hecho hasta la semilla: "<<contVueltas<<endl;
        	//return EXIT_SUCCESS;
        }

    } 
    else 
    {

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

