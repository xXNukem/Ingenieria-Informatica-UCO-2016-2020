/*
 * CNPInstance.cpp
 *
 * Final Practice CNP Problem
 *
 * @author José Luis Gordillo Relaño
 * @author Alberto Luque Rivas
 * @author Carlos de la Barrera Perez
 */
#include "CNPObjectAssignmentOperation.h"

CNPObjectAssignmentOperation::CNPObjectAssignmentOperation()
{
    _node = 0;
    _indexNodeChanged = 0;
    _deltaFitness = 0;
}

CNPObjectAssignmentOperation::~CNPObjectAssignmentOperation()
{
}

void CNPObjectAssignmentOperation::apply(CNPSolution &solution)
{
    /*
	 * 1. Asigna el objeto de índice _indexObj a la mochila _indexKnapsack en solution
	 * 2. Actualiza el fitness de solution sumándole _deltaFitness
	 */
    
    solution.changeNode(_indexNodeChanged, _node);
    //Obtenemos el fitness antes del cambio
    double actualFitness = solution.getFitness();    
    //Al sumar el deltaFitness implica que el cambio de nodo se ha efectuado
    double newFitness = actualFitness + _deltaFitness;
    //if(abs(_deltaFitness) == abs(actualFitness)) newFitness=0;
    solution.setFitness(newFitness);
}

void CNPObjectAssignmentOperation::setValues(int node, int indexNodeChanged, double deltaFitness)
{
    /*
	 * Guarda los valores pasados como argumentos en las variables miembro
	 */
    _node = node;
    _indexNodeChanged = indexNodeChanged;
    _deltaFitness = deltaFitness;
}
