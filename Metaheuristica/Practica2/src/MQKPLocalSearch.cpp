/*
 * MQKPLocalSearch.cpp
 *
 * Fichero que define las funciones de la clase MQKPLocalSearch. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <MQKPLocalSearch.h>
#include <MQKPInstance.h>
#include <MQKPSolution.h>
#include <MQKPNeighExplorer.h>
#include <MQKPObjectAssignmentOperation.h>

MQKPLocalSearch::MQKPLocalSearch() {
}

MQKPLocalSearch::~MQKPLocalSearch() {
}

void MQKPLocalSearch::optimise(MQKPInstance &instance, MQKPNeighExplorer &explorer, MQKPSolution &solution) {

    _results.clear();
    _results.push_back(solution.getFitness());
    MQKPObjectAssignmentOperation operation;

    while (explorer.findOperation(instance, solution, operation)) {
        operation.apply(solution);
        this->_results.push_back(solution.getFitness());
    }
}
