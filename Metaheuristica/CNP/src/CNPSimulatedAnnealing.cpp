/*
 * CNPSimulatedAnnealing.cpp
 *
 * Fichero que define las funciones de la clase CNPSimulatedAnnealing. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <CNPSimulatedAnnealing.h>
#include "CNPSolution.h"
#include "CNPSolGenerator.h"
#include <CNPEvaluator.h>
#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace std;

void CNPSimulatedAnnealing::setSolution(CNPSolution *solution)
{
    if (_T <= 0 || _annealingFactor <= 0)
    {
        cerr << "No se pudo iniciar el enfriamiento simulado" << endl;
        exit(-1);
    }

    if (_solution != NULL)
    {
        cerr << "_solution != NUL" << endl;
        exit(1);
    }

    this->_solution = solution;

    if (_bestSolution == NULL)
    {
        _bestSolution = new CNPSolution(*_instance);
    }

    _bestSolution->copy(*solution);
}

void CNPSimulatedAnnealing::run(CNPStopCondition &stopCondition)
{

    if (_T <= 0 || _annealingFactor <= 0)
    {
        cerr << "No se pudo iniciar el enfriamiento simulado" << endl;
        exit(-1);
    }

    if (_solution == NULL)
    {
        cerr << "Simulated annealing has not been given an initial solution" << endl;
        exit(-1);
    }

    _results.clear();
    int numNodesToSol = _instance->getNumNodesSol();
    int numNodesProblem = _instance->getNumNodes();

    //HASTA AQUI CORRECTO

    unsigned numIterations = 0;
    while (!stopCondition.reached())
    {
        int indice = rand() % (numNodesToSol);
        int nodo;

        //Comprobar duplicidad
        bool flag = true;
        while (flag == true)
        {
            nodo = rand() % (numNodesProblem);
            if (!_solution->checkDuplicity(nodo))
            {
                flag = false;
            }
        }

        double deltaFitness = CNPEvaluator::computeDeltaFitness(*_instance, *_solution, indice, nodo);

        if (CNPEvaluator::compare(_solution->getFitness(), _bestSolution->getFitness()) < 0)
        {
            _solution->changeNode(indice, nodo);
            _solution->setFitness(_solution->getFitness() + deltaFitness);
            _bestSolution->copy(*_solution);
        }
        else
        {
            if (this->accept(deltaFitness))
            {
                _solution->changeNode(indice, nodo);
                _solution->setFitness(_solution->getFitness() + deltaFitness); //REVISAR
                _bestSolution->copy(*_solution);
            }
        }

        numIterations++;
        _results.push_back(_solution->getFitness());

        if (numIterations % _itsPerAnnealing == 0)
        {
            _T *= _annealingFactor;
        }

        stopCondition.notifyIteration();
    }
}

bool CNPSimulatedAnnealing::accept(double deltaFitness)
{

    double auxDeltaFitness = deltaFitness;
    if (!CNPEvaluator::isToBeMinimised())
    {
        auxDeltaFitness = -auxDeltaFitness;
    }
    /*
		A mayor temperatura, mayor probabilidad de aceptación de soluciones peores
		A menor diferencia de fitness, mayor probabilidad de aceptación de soluciones peores
	*/
    double prob = exp(auxDeltaFitness / _T);
    double randSample = (((double)rand()) / RAND_MAX);
    //cout << " (" << randSample << "----" << prob << ")\n";
    return (randSample < prob);
}

void CNPSimulatedAnnealing::initialise(double initialProb, int numInitialEstimates, double annealingFactor, unsigned itsPerAnnealing, CNPInstance &instance)
{
    _initialProb = initialProb;
    _annealingFactor = annealingFactor;
    _instance = &instance;
    _itsPerAnnealing = itsPerAnnealing;
    int numNodesToSol = instance.getNumNodesSol();
    int numNodesProblem = instance.getNumNodes();
    double averageFDiffs = 0.;

    /**
	 * Inicialización de la temperatura.
	 * Para ello, se generan una serie de soluciones iniciales y de vecinos. Se calcula la diferencia media de fitness hacia peores soluciones y se despeja la temperatura de la función de aceptación
	 */

    for (int i = 0; i < numInitialEstimates; i++)
    {
        CNPSolution sol(instance);
        CNPSolGenerator::genRandomSol(instance, sol);
        sol.setFitness(CNPEvaluator::computeFitness(instance, sol));
        int indice = rand() % (numNodesToSol);
        int nodo = rand() % (numNodesProblem);

        double deltaFitness = CNPEvaluator::computeDeltaFitness(instance, sol, indice, nodo);
        averageFDiffs += min(fabs(deltaFitness), 0.1); //He puesto una diferencia mínima de 10 para evitar cambios en el fitness demasiado pequeños (por ejemplo, cuando se modifica una mochila que no es la de la máxima violación (este método se podría mejorar)
    }

    averageFDiffs /= numInitialEstimates;

    _T = -1. * averageFDiffs / log(initialProb);
    //cout << "VALOR DE T: " << _T << endl;
}