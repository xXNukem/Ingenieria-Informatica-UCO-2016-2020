/*
 * MQKPIteratedGreedy.cpp
 *
 * Fichero que define las funciones de la clase MQKPIteratedGreedy. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <MQKPIteratedGreedy.h>
#include <MQKPObjectAssignmentOperation.h>
#include <MQKPSolution.h>
#include <iostream>

using namespace std;

void MQKPIteratedGreedy::chooseOperation(
		MQKPObjectAssignmentOperation& operation) {

	int bestObj = 0;
	int bestKnapsack = 0;
	double bestDensity = 0;
	double bestDeltaFitness = 0;
	bool initialisedBestDensity = false;
	unsigned numObjs = _instance->getNumObjs();
	unsigned numKnapsacks = _instance->getNumKnapsacks();

	for (unsigned i = 0; i < numObjs; i++) {

		int indexObj = i;

		if (_sol->whereIsObject(indexObj) == 0) { 

			for (unsigned j = 1; j <= numKnapsacks; j++) { 

				int indexKnapsack = j;

				double deltaFitness = MQKPEvaluator::computeDeltaFitness(*_instance, *_sol,indexObj, indexKnapsack);
				double density = deltaFitness / _instance->getWeight(indexObj);
				
				if (density > bestDensity || initialisedBestDensity == false) {
					initialisedBestDensity = true;
					bestDensity = density;
					bestObj = indexObj;
					bestKnapsack = indexKnapsack;
					bestDeltaFitness = deltaFitness;
				}
			}
		}
	}
	operation.setValues(bestObj, bestKnapsack, bestDeltaFitness);
}

void MQKPIteratedGreedy::rebuild() {

	/** Seleccionar la primera operación */
	MQKPObjectAssignmentOperation operation;
	chooseOperation(operation);

	while (operation.getDeltaFitness() > 0) {
		operation.apply(*_sol);
		_results.push_back(_sol->getFitness());
		chooseOperation(operation);
	}
}

void MQKPIteratedGreedy::destroy() {

	unsigned numObjs = _instance->getNumObjs();

	for (unsigned i = 0; i < numObjs; i++){

		double randSample = ((double)(rand())) / RAND_MAX;

		if (randSample <= _alpha){
			_sol->putObjectIn(i, 0);
		}
	}

	double fitness = MQKPEvaluator::computeFitness(*_instance, *_sol);
	_sol->setFitness(fitness);
	_results.push_back(_sol->getFitness());
}

void MQKPIteratedGreedy::initialise(double alpha, MQKPInstance& instance) {
	_sol = new MQKPSolution(instance);
	_bestSolution = new MQKPSolution(instance);
	_bestSolution->copy(*_sol);
	_instance = &instance;
	_alpha = alpha;
}

void MQKPIteratedGreedy::run(MQKPStopCondition& stopCondition) {

	if (_sol == NULL) {
		cerr << "IG was not initialised" << endl;
		exit(-1);
	}

	/** Crear la primera solución */
	rebuild();
	
	if (MQKPEvaluator::compare(_sol->getFitness(), _bestSolution->getFitness()) > 0)
		_bestSolution->copy(*_sol);

	while (stopCondition.reached() == false) {
		destroy();
		rebuild();
		_results.push_back(_sol->getFitness());

		if (MQKPEvaluator::compare(_sol->getFitness(), _bestSolution->getFitness()) > 0)
			_bestSolution->copy(*_sol);
		else
			_sol->copy(*_bestSolution);

		stopCondition.notifyIteration();
	}
}


