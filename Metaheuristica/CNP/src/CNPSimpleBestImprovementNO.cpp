/**
 * CNPSimpleBestImprovementNO.cpp
 *
 * Fichero que define las funciones de la clase CNPSimpleBestImprovementNO. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <CNPSimpleBestImprovementNO.h>
#include <CNPInstance.h>
#include <CNPSolution.h>
#include <CNPObjectAssignmentOperation.h>
#include <CNPEvaluator.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

bool CNPSimpleBestImprovementNO::findOperation(CNPInstance &instance,
                                               CNPSolution &solution, CNPChangeOperation &operation)
{

    CNPObjectAssignmentOperation *oaOperation = dynamic_cast<CNPObjectAssignmentOperation *>(&operation);
    if (oaOperation == NULL)
    {
        cerr << "CNPSimpleBestImprovementNO::findOperation recibió un objeto operation que no es de la clase CNPObjectAssignmentOperation" << endl;
        exit(1);
    }

    //Crear una permutación de los índices de los objetos e inicializar algunas variables
    vector<int> perm;
    int numNodesSol = instance.getNumNodesSol();
    int numNodesTotal = instance.getNumNodes();
    randomPermutation(numNodesTotal, perm);
    bool initialised = false;
    double bestDeltaFitness = 0;
    double deltaFitness = 0.0;
    for (int i = 0; i < numNodesTotal; i++)
    {

        if (!solution.checkDuplicity(perm.at(i)))
        {
            for (int j = 0; j < numNodesSol; j++)
            {

                deltaFitness = CNPEvaluator::computeDeltaFitness(instance, solution, j, perm.at(i)); //J es el indice y perm.at(i) el nodo permutado que no esta en la solución

                if (CNPEvaluator::compare(deltaFitness, bestDeltaFitness) < 0 || !initialised)
                {
                    initialised = true;
                    bestDeltaFitness = deltaFitness;
                    oaOperation->setValues(j, perm.at(i), bestDeltaFitness);
                }
            }
        }
    }
    return (bestDeltaFitness < 0.0) ? true : false;
}
