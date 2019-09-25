/*
 * FuncionesAuxiliares.cpp
 *
 * Final Practice CNP Problem
 *
 * @author José Luis Gordillo Relaño
 */
#include "funcionesAuxiliares.h"

int numNodes = 0;
void runAIGExperiment(vector<double> &currentResults, vector<double> &bestSoFarResults, CNPInstance &instance) {

	//Inicialización
	CNPSolution initialSolution(instance);	
	CNPIteratedGreedy ig;
	CNPStopCondition stopCond;
	CNPEvaluator::resetNumEvaluations();
	
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);
	//Generar solución aleatoria para inicialiar la mejor solución y sobre la cual iterar
	
	ig.buildInitialSol(instance, initialSolution);
	//Si no pasamos ninguna flag estamos ejecutando el IG puro
	ig.initialise(0.25, instance, initialSolution);
	//Si pasamos una flag a TRUE estamos ejecutando el IG variando la ProbDestrucción
	//ig.initialise(0.9, instance, initialSolution, true);
	
	double currentFitness = CNPEvaluator::computeFitness(instance, initialSolution);

	initialSolution.setFitness(currentFitness);
	double bestFitness = currentFitness;
	
	currentResults.push_back(currentFitness);
	bestSoFarResults.push_back(bestFitness);

	//Aplicar IG
	ig.run(stopCond);
	//Almacenar los resultados
	vector<double> &resultsIG = ig.getResults();
	for (auto aResult : resultsIG) {
		currentResults.push_back(aResult);
		bestSoFarResults.push_back(min(bestSoFarResults.back(), aResult));
	}
}



void runExperiments(vector<vector<vector<double>*>*> &results, char **mainArgs,
		unsigned int numMainArgs) {

    CNPSimpleFirstImprovementNO firstExplorer;
	CNPSimpleBestImprovementNO bestExplorer;
	//Para cada instancia del problema
	for (unsigned int iInstance = 1; iInstance < numMainArgs; iInstance += 2) {
		//Leer la instancia y crear la estructuras de datos necesarias para guardar los resultados
		CNPInstance instance;
		vector<vector<double>*>* resultsOnThisInstance = new vector<vector<double>*>;
		results.push_back(resultsOnThisInstance);

		char *instanceName = mainArgs[iInstance];
		instance.readInstance(mainArgs[1]);
		numNodes = atoi(mainArgs[2]);
		instance.setNumNodesSol(numNodes);

        //Ejecutar la búsqueda local escalada simple
        vector<double> *theseFirstResults = new vector<double>;
        vector<double> *bestFirstResults = new vector<double>;
        resultsOnThisInstance->push_back(theseFirstResults);
        resultsOnThisInstance->push_back(bestFirstResults);
        runALSExperiment(*theseFirstResults, *bestFirstResults, instance, firstExplorer);

        //Ejecutar la búsqueda local maxima pendiente
        vector<double> *theseBestResults = new vector<double>;
        vector<double> *bestBestResults = new vector<double>;
        resultsOnThisInstance->push_back(theseBestResults);
        resultsOnThisInstance->push_back(bestBestResults);
        runALSExperiment(*theseBestResults, *bestBestResults, instance, bestExplorer);

        //Ejecutar el enfriamientoSimulado
        theseFirstResults = new vector<double>;
        bestFirstResults = new vector<double>;
        resultsOnThisInstance->push_back(theseFirstResults);
        resultsOnThisInstance->push_back(bestFirstResults);
        runASAExperiment(*theseFirstResults, *bestFirstResults, instance);
        
        //Ejecutar la búsqueda tabú
        theseFirstResults = new vector<double>;
        bestFirstResults = new vector<double>;
        resultsOnThisInstance->push_back(theseFirstResults);
        resultsOnThisInstance->push_back(bestFirstResults);
		runATSExperiment(*theseFirstResults, *bestFirstResults, instance);

		//Ejecutar la búsqueda Iterated Greedy
		theseFirstResults = new vector<double>;
		bestFirstResults = new vector<double>;
		resultsOnThisInstance->push_back(theseFirstResults);
		resultsOnThisInstance->push_back(bestFirstResults);
		runAIGExperiment(*theseFirstResults, *bestFirstResults, instance);

		//Ejecutar el algoritmo evolutivo
		vector<double> *theseResults = new vector<double>;
		vector<double> *bestResults = new vector<double>;
		vector<double> *bestPerIterations = new vector<double>;
		vector<double> *popMeanResults = new vector<double>;
		vector<double> *offMeanResults = new vector<double>;
		resultsOnThisInstance->push_back(theseResults);
		resultsOnThisInstance->push_back(bestResults);
		resultsOnThisInstance->push_back(bestPerIterations);
		resultsOnThisInstance->push_back(popMeanResults);
		resultsOnThisInstance->push_back(offMeanResults);
		runAGAExperiment(*theseResults, *bestResults, *bestPerIterations,
				*popMeanResults, *offMeanResults, instance);
	}
}


void runAGAExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, vector<double> &bestPerIterations,
		vector<double> &popMean, vector<double> &offMean,
		CNPInstance &instance) {

	//Inicialización
	CNPGeneticAlgorithm ga;
	CNPStopCondition stopCond;
	CNPEvaluator::resetNumEvaluations();
	//Initialise por defecto (población = soluciones random)
	ga.initialise(60, instance);
	//Initialise usando 10% de soluciones greedy
	//ga.initialise(60, instance, true);
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

	//Ejecutar el GA

	ga.run(stopCond);
	
	//Almacenar los resultados
	vector<double> &resultsGA = ga.getResults();

	for (double aResult : resultsGA) {
		currentResults.push_back(aResult);

		if (bestSoFarResults.size() > 0)
			bestSoFarResults.push_back(min(bestSoFarResults.back(), aResult));
		else
			bestSoFarResults.push_back(aResult);
	}

	bestPerIterations = ga.getBestsPerIterations();
	popMean = ga.getPopMeanResults();
	offMean = ga.getOffMeanResults();
}

void runASAExperiment(vector<double> &currentResults,
                      vector<double> &bestSoFarResults, CNPInstance &instance)
{

    //Inicialización
    CNPSolution initialSolution(instance);
    CNPSimulatedAnnealing sa;
    CNPStopCondition stopCond;
    CNPEvaluator::resetNumEvaluations();
    sa.initialise(0.9, 100, 0.9999, 50, instance);
    stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);
    //Generar solución aleatoria
    CNPSolGenerator::genRandomSol(instance, initialSolution);
    double currentFitness = CNPEvaluator::computeFitness(instance,
                                                         initialSolution);
    initialSolution.setFitness(currentFitness);
    double bestFitness = currentFitness;
    currentResults.push_back(currentFitness);
    bestSoFarResults.push_back(bestFitness);
    sa.setSolution(&initialSolution);
    //Aplicar SA
    sa.run(stopCond);

    //Almacenar los resultados
    vector<double> &resultsSA = sa.getResults();

    for (auto aResult : resultsSA)
    {
        currentResults.push_back(aResult);
        bestSoFarResults.push_back(min(bestSoFarResults.back(), aResult)); //min para sacar el minimo de lost resultados, CNP es de minimización y por ello se usa min().
    }
}

void runATSExperiment(vector<double> &currentResults,
                      vector<double> &bestSoFarResults, CNPInstance &instance)
{

    //Inicialización
    CNPSolution initialSolution(instance);
    CNPTabuSearch ts;
    CNPStopCondition stopCond;
    CNPEvaluator::resetNumEvaluations();
    ts.initialise(&instance, ((unsigned)(instance.getNumNodes() / 2.5)));
    stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

    //Generar solución aleatoria
    CNPSolGenerator::genRandomSol(instance, initialSolution);
    double currentFitness = CNPEvaluator::computeFitness(instance,
                                                         initialSolution);
    initialSolution.setFitness(currentFitness);
    double bestFitness = currentFitness;
    currentResults.push_back(currentFitness);
    bestSoFarResults.push_back(bestFitness);
    ts.setSolution(&initialSolution);

    //Aplicar TS
    ts.run(stopCond);

    //Almacenar los resultados
    vector<double> &resultsTS = ts.getResults();

    for (auto aResult : resultsTS)
    {
        currentResults.push_back(aResult);
        bestSoFarResults.push_back(min(bestSoFarResults.back(), aResult));
    }
}

void runALSExperiment(vector<double> &currentResults,
                      vector<double> &bestSoFarResults, CNPInstance &instance,
                      CNPNeighExplorer &explorer)
{

    //Inicialización
    CNPLocalSearch ls;
    CNPSolution initialSolution(instance);
    Timer t;
    CNPEvaluator::resetNumEvaluations();
    //Generar una primera solución aleatoria para inicializar bestFitness
    CNPSolGenerator::genRandomSol(instance, initialSolution);
    double currentFitness = CNPEvaluator::computeFitness(instance,
                                                         initialSolution);
    double bestFitness = currentFitness;
    initialSolution.setFitness(currentFitness);
    currentResults.push_back(currentFitness);
    bestSoFarResults.push_back(bestFitness);
    int numInitialSolutions = 0;
    //Mientras no se acabe el tiempo y no se generen demasiadas soluciones,	generar solución aleatoria, aplicarle la optimización y guardar el resultado
    while (t.elapsed_time(Timer::VIRTUAL) <= MAX_SECONS_PER_RUN && CNPEvaluator::getNumEvaluations() < MAX_SOLUTIONS_PER_RUN &&
           numInitialSolutions < MAX_INITIAL_SOLUTIONS)
    {
        CNPSolGenerator::genRandomSol(instance, initialSolution);
        currentFitness = CNPEvaluator::computeFitness(instance, initialSolution);
        initialSolution.setFitness(currentFitness);
        currentResults.push_back(currentFitness);
        bestSoFarResults.push_back(
            min(bestSoFarResults.back(), currentFitness));
        ls.optimise(instance, explorer, initialSolution);
        //Almacenar los resultados
        vector<double> &resultsLS = ls.getResults();
        for (auto aResult : resultsLS)
        {
            currentResults.push_back(aResult);
            bestSoFarResults.push_back(min(bestSoFarResults.back(), aResult));
        }
        numInitialSolutions++;
    }
}


template<typename T>
void free3Darray(vector<vector<vector<T>*>*> &array) {

	int numArrays = (int)(array.size());

	for (int i = 0; i < numArrays; i++) {
		free2Darray(*(array.at(i)));
		delete (array.at(i));
	}

	array.clear();
}
template<typename T>
void free2Darray(vector<vector<T>*> &array) {

	int numVectors = ((int)(array.size()));

	for (int i = 0; i < numVectors; i++) {
		array.at(i)->clear();
		delete (array.at(i));
	}

	array.clear();
}