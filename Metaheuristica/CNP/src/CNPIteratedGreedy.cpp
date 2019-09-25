/*
 * CNPIteratedGreedy.cpp
 *
 * Fichero que define las funciones de la clase CNPIteratedGreedy. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author José Luis Gordillo Relaño <i62gorej@uco.es>
 */

#include "CNPIteratedGreedy.h"
#include "CNPObjectAssignmentOperation.h"
#include "CNPSolution.h"
#include <iostream>

using namespace std;

void CNPIteratedGreedy::destroy()
{
	//Obtenemos el tamaño del array de solucion
	unsigned numNodes = _instance->getNumNodes();
	//Lo recorremos y segun una prob, será eliminado del array
	for (unsigned i = 0; i < numNodes; i++)
	{
		if (_sol->checkDuplicity(i))
		{
			double randSample = ((double)(rand())) / RAND_MAX;
			if (randSample <= _alpha)
				_sol->deleteNode(i);
		}
	}

	double fitness = CNPEvaluator::computeFitness(*_instance, *_sol);
	_sol->setFitness(fitness);
	_results.push_back(_sol->getFitness());
}

void CNPIteratedGreedy::initialise(double alpha, CNPInstance &instance, CNPSolution &solution, bool flag)
{
	_sol = new CNPSolution(instance);
	_bestSolution = new CNPSolution(instance);
	_sol->copy(solution);
	_bestSolution->copy(*_sol);
	_instance = &instance;
	_alpha = alpha;
	_flag = flag;
}

void CNPIteratedGreedy::run(CNPStopCondition &stopCondition)
{

	if (_sol == NULL)
	{
		cerr << "IG was not initialised" << endl;
		exit(-1);
	}

	while (stopCondition.reached() == false)
	{
		destroy();

		buildInitialSol(*_instance, *_sol);

		_results.push_back(_sol->getFitness());

		if (CNPEvaluator::compare(_sol->getFitness(), _bestSolution->getFitness()) < 0)
			_bestSolution->copy(*_sol);
		else
			_sol->copy(*_bestSolution);

		(_alpha > 0.25 && _flag) ? _alpha -= 0.1 : _alpha = 0.25;
		stopCondition.notifyIteration();
	}
	CNPEvaluator::computeFitness(*_instance, *_bestSolution);
}
void CNPIteratedGreedy::buildInitialSol(CNPInstance &instance, CNPSolution &solution)
{
	//Declaramos dos objetos auxiliares donde se haran las operaciones
	CNPInstance inst = instance;
	int numNodesSolution = inst.getNumNodesSol();

	while (solution.getSolSize() < numNodesSolution)
	{
		//Creamos un array para la lista de candidatos a insertar en la solución
		vector<double> _candidateList;
		//Obtenemos el fitness para posterior inserción de los BCs en la lista
		double fitness = CNPEvaluator::computeFitness(inst, solution);
		//Creamos un array donde almacenar los candidatos a insertar
		for (int i = 0; i < inst.getBCNumNodes(); i++)
			_candidateList.push_back(inst.getBCElement(i));

		//Ordenamos los Bcs individuales por nodo de mayor a menor
		sort(_candidateList.begin(), _candidateList.end(), greater<double>());
		//Seleccionamos siempre al que mayor debilidad aporta
		int node = _candidateList.at(rand()%5);
		//Obtenemos el indice del nodo en el grafo y comprobamos que no exista en Sol
		int index = inst.getBcElementIndex(_candidateList.at(node));
		//Añado a la solución un nodo aleatorio entre los N primeros mejores nodos
		if (!solution.checkDuplicity(index))			
			solution.addNodeToSol(index);
		//Renuevo la instancia para dejarla original y obtengo el fitness nuevo
		inst = instance;
		fitness = CNPEvaluator::computeFitness(inst, solution);
	}
}