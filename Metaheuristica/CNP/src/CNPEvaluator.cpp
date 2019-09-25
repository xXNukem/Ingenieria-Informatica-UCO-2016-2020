/*
 * CNPEvaluator.cpp
 *
 * Final Practice CNP Problem
 *
 * @author José Luis Gordillo Relaño
 * @author Alberto Luque Rivas
 * @author Carlos de la Barrera Perez
 */
#include "CNPEvaluator.h"
#include "CNPSolution.h"
#include "CNPInstance.h"
double CNPEvaluator::_numEvaluations = 0.;
double CNPEvaluator::computeFitness(CNPInstance &instance, CNPSolution &solution)
{
    //Hacemos copia de la istancia que almacena el grafo completo
    _numEvaluations++;
    CNPInstance inst = instance;
    double fitness = 0.0;
    //Borramos las aristas del grafo de la istancia auxiliar
    for (int i = 0; i < solution.getSolSize(); i++)
        inst.deleteEdge(solution.getNodeFromSol(i));
    //Obtenemos le fitness como la suma de los bcs de los nodos del grafo
    fitness = inst.getBetweennessCentrality();
    instance.copyBCArray(inst);
    //Establecemos el fitness a la solución actual
    solution.setFitness(fitness);
    return fitness;
}

double CNPEvaluator::computeDeltaFitness(CNPInstance &instance, CNPSolution &solution, int index, int node)
{
    double actualFitness = solution.getFitness();
    CNPSolution sol = solution;
    //Actualizamos el nodo cambiando el nodo del indice "index" por node
    int node_aux = solution.getNodeFromSol(index);
    sol.changeNode(index, node);

    //Calculamos Fitness del cambio de nodo
    double newFitness = CNPEvaluator::computeFitness(instance, sol);
    //retornamos la diferencia de fitness
    sol.changeNode(index, node_aux);
    return newFitness - actualFitness;
}
void CNPEvaluator::resetNumEvaluations()
{
    _numEvaluations = 0;
}