/*
 * CNPSimpleFirstImprovementNO.cpp
 *
 * Fichero que define las funciones de la clase CNPSimpleFirstImprovementNO.Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <CNPSimpleFirstImprovementNO.h>
#include <CNPInstance.h>
#include <CNPEvaluator.h>
#include <CNPObjectAssignmentOperation.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

bool CNPSimpleFirstImprovementNO::findOperation(CNPInstance &instance, CNPSolution &solution,
                                                CNPChangeOperation &operation)
{

    CNPObjectAssignmentOperation *oaOperation = dynamic_cast<CNPObjectAssignmentOperation *>(&operation);
    if (oaOperation == NULL)
    {
        cerr << "CNPSimpleFirstImprovementNO::findOperation recibió un objeto operation que no es de la clase CNPObjectAssignmentOperation" << endl;
        exit(1);
    }

    //Crear una permutación de los índices de los nodos e inicializar algunas variables
    vector<int> perm;
    int numNodesSol = instance.getNumNodesSol();
    int numNodesTotal = instance.getNumNodes();
    randomPermutation(numNodesTotal, perm);

    double deltaFitness = 0.0;

    for (int i = 0; i < numNodesTotal; i++)
    {
        if (!solution.checkDuplicity(perm.at(i)))
        {
            for (int j = 0; j < numNodesSol; j++)
            {
                deltaFitness = CNPEvaluator::computeDeltaFitness(instance, solution, j, perm.at(i));
                if (deltaFitness < 0.0)
                {
                    oaOperation->setValues(j, perm.at(i), deltaFitness);
                    return true;
                }
            }
        }
    }
    return false;
}
