/*
 * MQKPObjectAssignmentOperation.cpp
 *
 * Fichero que define las funciones de la clase MQKPObjectAssignmentOperation. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <MQKPObjectAssignmentOperation.h>

MQKPObjectAssignmentOperation::MQKPObjectAssignmentOperation() {
    _indexKnapsack = 0;
    _indexObj = 0;
    _deltaFitness = 0;
}

MQKPObjectAssignmentOperation::~MQKPObjectAssignmentOperation() {
}

void MQKPObjectAssignmentOperation::apply(MQKPSolution &solution) {

    solution.putObjectIn(_indexObj, _indexKnapsack);
    solution.setFitness(solution.getFitness() + this->_deltaFitness);
}

void MQKPObjectAssignmentOperation::setValues(int indexObject,
                                              int indexKnapsack, double deltaFitness) {

    _indexObj = indexObject;
    _indexKnapsack = indexKnapsack;
    _deltaFitness = deltaFitness;
}
