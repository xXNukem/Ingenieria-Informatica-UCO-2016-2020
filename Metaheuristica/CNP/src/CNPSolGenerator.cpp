/*
 * CNPSolGenerator.cpp
 *
 * Final Practice CNP Problem
 *
 * @author Alberto Luque Rivas
 */
#include "CNPSolGenerator.h"

void CNPSolGenerator::genRandomSol(CNPInstance &instance, CNPSolution &solution)
{
    int nodo;
    CNPSolution *aux = new CNPSolution(instance);
    while (aux->getSolSize() < instance.getNumNodesSol())
    {
        nodo = rand() % (instance.getNumNodes());
        if (!aux->checkDuplicity(nodo))
        {
            aux->addNodeToSol(nodo);
        }
    }
    solution.copy(*aux);
}
