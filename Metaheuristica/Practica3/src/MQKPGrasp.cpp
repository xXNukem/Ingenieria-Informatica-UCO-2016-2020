/*
 * MQKPGrasp.cpp
 *
 * Fichero que define las funciones de la clase MQKPGrasp. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <MQKPGrasp.h>
#include <vector>
#include <MQKPSimpleFirstImprovementNO.h>
#include <MQKPLocalSearch.h>
#include <iostream>

using namespace std;

void MQKPGrasp::chooseOperation(MQKPObjectAssignmentOperation& operation) {

	int bestObj = 0;
	int bestKnapsack = 0;
	double bestDensity = 0;
	double bestDeltaFitness = 0;
	bool initialisedBestDensity = false;
	unsigned numObjs = _instance->getNumObjs();
	unsigned numKnapsacks = _instance->getNumKnapsacks();

	/**
	 * Calcular el número de intentos como el porcentaje _alpha por el número de posibilidades, que es el número de objetos por el número de mochilas.
	 *
	 * En este paso no se considerará que ya haya objetos asignados a alguna mochila, la mochila 0 que representa objetos sin asignar a ninguna mochila, ni que haya mochilas ya completamente llenas
	 */
	unsigned numTries = ((unsigned)(numObjs * numKnapsacks * _alpha));

	for (unsigned i = 0; i < numTries; i++) {
		int indexObj = rand()%numObjs;
		int indexKnapsack = (rand()%numKnapsacks)+1;

		double deltaFitness = MQKPEvaluator::computeDeltaFitness(*_instance, *_sol, indexObj, indexKnapsack); 
		double density = deltaFitness/_instance->getWeight(indexObj);

		if (density > bestDensity || initialisedBestDensity == false) {
			initialisedBestDensity = true;
			bestDensity = density;
			bestObj = indexObj;
			bestKnapsack = indexKnapsack;
			bestDeltaFitness = deltaFitness;
		}
	}
	
	operation.setValues(bestObj, bestKnapsack,
			bestDeltaFitness);
}

void MQKPGrasp::buildInitialSolution() {

	unsigned numObjs = _instance->getNumObjs();

	_sol->setFitness(0);
	for (unsigned i = 0; i < numObjs; i++) {
		_sol->putObjectIn(i, 0);
	}

	/** Seleccionar la primera operación */
	MQKPObjectAssignmentOperation operation;
	chooseOperation(operation);

	while (operation.getDeltaFitness() > 0) {
		operation.apply(*_sol);
		_results.push_back(_sol->getFitness());
		chooseOperation(operation);
	}
}

void MQKPGrasp::initialise(double alpha, MQKPInstance& instance) {

	_sol = new MQKPSolution(instance);
	_bestSolution = new MQKPSolution(instance);
	_bestSolution->copy(*_sol);
	_instance = &instance;
	_alpha = alpha;
}

void MQKPGrasp::run(MQKPStopCondition& stopCondition) {

	if (_sol == NULL) {
		cerr << "GRASP was not initialised" << endl;
		exit(-1);
	}
	
	while (!stopCondition.reached()) {
		buildInitialSolution();	
		_results.push_back(_sol->getFitness());
		_ls.optimise(*_instance,_no,*_sol);

		vector<double> &auxResults = _ls.getResults();

		for (auto result : auxResults){
			_results.push_back(result);
		}

		if (MQKPEvaluator::compare(_sol->getFitness(), _bestSolution->getFitness()) > 0)
			_bestSolution->copy(*_sol);

		stopCondition.notifyIteration();
	}
}
