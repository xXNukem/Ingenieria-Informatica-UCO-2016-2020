#ifndef _FUNCIONES_AUXILIARES_H
#define _FUNCIONES_AUXILIARES_H
//Definición de algunos parámetros de la experimentación
#define MAX_SECONS_PER_RUN 10
#define MAX_SOLUTIONS_PER_RUN 10000
#define MAX_INITIAL_SOLUTIONS 30

#include "CNPEvaluator.h"
#include "CNPInstance.h"
#include "CNPSolGenerator.h"
#include "CNPSolution.h"
#include "CNPIteratedGreedy.h"
#include <CNPTabuSearch.h>
#include <CNPSimulatedAnnealing.h>
#include <CNPGeneticAlgorithm.h>
#include <CNPStopCondition.h>
#include <CNPLocalSearch.h>
#include <CNPSimpleFirstImprovementNO.h>
#include <CNPSimpleBestImprovementNO.h>
#include <Timer.h>
#include <iostream>
using namespace std;

/**
 * Función que ejecuta la búsqueda Iterated Greedy, durante MAX_SECONS_PER_RUN segundos, un máximo de MAX_SOLUTIONS_PER_RUN, para la instancia proporcionada
 * @param[out] currentResults vector donde se almacenarán los valores fitness de las soluciones que va aceptando el enfriamiento simulado.
 * @param[out] bestSoFarResults vector donde se almacenarán los mejores valores fitness generados hasta el momento
 * @param[in] instance Instancia del problema de la mochila cuadrática múltiple
 */
void runAIGExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, CNPInstance &instance);

/**
 * Función que libera la memoria de un vector 3D
 * @param[in] array matriz 3D que se va a liberar de memoria
 */
template<typename T>
void free3Darray(vector<vector<vector<T>*>*> &array) ;

/**
 * Función que libera la memoria de un vector 2D
 * @param[in] array vector 2D que se va a liberar de memoria
 */
template< typename T >
void free2Darray(vector<vector<T>*> &array);

/**
 * Función que ejecuta todos los experimentos para los argumentos pasados al programa principal
 * @param[out] results matriz 3D donde se almacenarán los resultados. El primer índice será para la instancia considerada. El segundo para el experimento sobre dicha instancia. El tercero para la solución generada en dicho experimento
 * @param[in] mainArgs Argumentos de la función main (argv). En los argumentos vienen, desde el índice 1, <nombre del fichero de la instancia 1> <número de mochilas> <nombre del fichero de la instancia 2> <número de mochilas>...
 * @param[in] numMainArgs Número de argumentos de la función main (argc)
 */
void runExperiments(vector<vector<vector<double>*>*> &results, char **mainArgs, unsigned int numMainArgs); 
/**
 * Función que ejecuta el algoritmo evolutivo, durante MAX_SECONS_PER_RUN segundos, un máximo de MAX_SOLUTIONS_PER_RUN, para la instancia proporcionada
 * @param[out] currentResults vector donde se almacenarán los valores fitness de las soluciones que se van generando.
 * @param[out] bestSoFarResults vector donde se almacenarán los mejores valores fitness generados hasta el momento
 * @param[out] bestPerIterations vector donde se almacenarán los mejores valores fitness de cada generación
 * @param[out] popMean vector donde se almacenarán los valores fitness medios de cada generación
 * @param[out] offMean vector donde se almacenarán los valores fitness medios de la población de descendientes
 * @param[in] instance Instancia del problema de la mochila cuadrática múltiple
 */
void runAGAExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, vector<double> &bestPerIterations,
		vector<double> &popMean, vector<double> &offMean,
		CNPInstance &instance);

/**
 * Función que ejecuta el enfriamiento simulado, durante MAX_SECONS_PER_RUN segundos, un máximo de MAX_SOLUTIONS_PER_RUN, para la instancia proporcionada
 * @param[out] currentResults vector donde se almacenarán los valores fitness de las soluciones que va aceptando el enfriamiento simulado.
 * @param[out] bestSoFarResults vector donde se almacenarán los mejores valores fitness generados hasta el momento
 * @param[in] instance Instancia del problema CNP
 */
void runASAExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, CNPInstance &instance);

/**
 * Función que ejecuta la búsqueda tabú, durante MAX_SECONS_PER_RUN segundos, un máximo de MAX_SOLUTIONS_PER_RUN, para la instancia proporcionada
 * @param[out] currentResults vector donde se almacenarán los valores fitness de las soluciones que va aceptando el enfriamiento simulado.
 * @param[out] bestSoFarResults vector donde se almacenarán los mejores valores fitness generados hasta el momento
 * @param[in] instance Instancia del problema de la mochila cuadrática múltiple
 */
void runATSExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, CNPInstance &instance);

/**
 * Función que realiza varias optimizaciones locales de soluciones aleatorias, durante MAX_SECONS_PER_RUN segundos, un máximo de MAX_SOLUTIONS_PER_RUN y un máximo de MAX_INITIAL_SOLUTIONS optimizaciones locales, para la instancia proporcionada
 * @param[out] currentResults vector donde se almacenarán los valores fitness de las soluciones que la búsqueda local va aceptando en todo momento.
 * @param[out] bestSoFarResults vector donde se almacenarán los mejores valores fitness generados hasta el momento
 * @param[in] instance Instancia del problema de la mochila cuadrática múltiple
 * @param[in] explorer Operador de exploración de vecindarios a utilizar
 */
void runALSExperiment(vector<double> &currentResults,
                      vector<double> &bestSoFarResults, CNPInstance &instance,
CNPNeighExplorer &explorer);


#endif