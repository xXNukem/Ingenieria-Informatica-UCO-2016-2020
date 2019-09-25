/*
 * CNPLocalSearch.cpp
 *
 * Fichero que define las funciones de la clase CNPLocalSearch. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <CNPLocalSearch.h>
#include <CNPInstance.h>
#include <CNPSolution.h>
#include <CNPNeighExplorer.h>
#include <CNPObjectAssignmentOperation.h>

CNPLocalSearch::CNPLocalSearch()
{
}

CNPLocalSearch::~CNPLocalSearch()
{
}

void CNPLocalSearch::optimise(CNPInstance &instance, CNPNeighExplorer &explorer, CNPSolution &solution)
{
    _results.clear();
    _results.push_back(solution.getFitness());
    CNPObjectAssignmentOperation operation;
    while (explorer.findOperation(instance, solution, operation))
    {
        operation.apply(solution);
        this->_results.push_back(solution.getFitness());
    }
}
