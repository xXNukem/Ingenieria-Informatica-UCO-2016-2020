/*
 * CNPTabuSearch.cpp
 *
 * Fichero que define las funciones de la clase CNPTabuSearch. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <CNPEvaluator.h>
#include <CNPNodeAssignmentOperation.h>
#include <CNPTabuSearch.h>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>

using namespace std;

void CNPTabuSearch::initialise(CNPInstance *instance, unsigned tabuTennure)
{
    _instance = instance;
    _tabuTennure = tabuTennure;
}

void CNPTabuSearch::setSolution(CNPSolution *solution)
{

    if (_solution != NULL)
    {
        cerr << "No se debe invocar más de una vez el método CNPTabuSearch::setSolution" << endl;
        exit(1);
    }

    this->_solution = solution;

    if (_bestSolution == NULL)
    {
        _bestSolution = new CNPSolution(*_instance);
    }

    _bestSolution->copy(*solution);
}

void CNPTabuSearch::run(CNPStopCondition &stopCondition)
{
    if (_solution == NULL)
    {
        cerr << "Tabu search has not been given an initial solution" << endl;
        exit(-1);
    }

    _results.clear();
    unsigned numNodes = _instance->getNumNodes();
    unsigned numNodesSol = _instance->getNumNodesSol();
    unsigned numIterations = 0;

    while (!stopCondition.reached())
    {

        vector<int> perm;
        randomPermutation(numNodes, perm);
        double bestDeltaFitness = 0;
        bool initialisedDeltaFitness = false;
        CNPNodeAssignmentOperation bestOperation;

        //Buscar la mejor operación no tabú
        for (unsigned i = 0; i < numNodes; i++)
        {

            unsigned node = perm[i];
            //Si el nodo no es tabú y no se encuentra en la solución (utilizar _shortTermMem_aux.find)

            if (_shortTermMem_aux.find(node) == _shortTermMem_aux.end() && _solution->checkDuplicity(node) == false)
            {

                //Probar todas los nodos de la solcuión y elegir la mejor opción
                for (unsigned j = 0; j < numNodesSol; j++)
                {

                    //Obtener la diferencia de fitness de aplicar dicha operación
                    double deltaFitness = CNPEvaluator::computeDeltaFitness(*_instance, *_solution, j, perm.at(i));

                    //Si la diferencia de fitness es la mejor hasta el momento, apuntarla para aplicarla después
                    if (deltaFitness < bestDeltaFitness || initialisedDeltaFitness == false)
                    {
                        initialisedDeltaFitness = true;
                        bestDeltaFitness = deltaFitness;
                        bestOperation.setValues(j, node, bestDeltaFitness);
                    }
                }
            }
        }

        bestOperation.apply(*_solution);
        _shortTermMem.push(bestOperation.getNode());
        _shortTermMem_aux.insert(bestOperation.getNode());

        if (_shortTermMem.size() > _tabuTennure)
        {
            unsigned value = _shortTermMem.front();
            _shortTermMem.pop();
            _shortTermMem_aux.erase(value);
        }

        //Actualizar la mejor solución
        if (CNPEvaluator::compare(_solution->getFitness(),
                                  _bestSolution->getFitness()) < 0)
        {
            _bestSolution->copy(*_solution);
        }

        numIterations++;
        _results.push_back(_solution->getFitness());
        stopCondition.notifyIteration();
    }
}