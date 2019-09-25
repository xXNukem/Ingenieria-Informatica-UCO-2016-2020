/*
 * MQKPEvaluator.cpp
 *
 * Fichero que define los métodos de la clase MQKPEvaluator. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <MQKPEvaluator.h>
#include <MQKPInstance.h>
#include <MQKPSolution.h>

unsigned MQKPEvaluator::_numEvaluations = 0;

double MQKPEvaluator::computeFitness(MQKPInstance &instance, MQKPSolution &solution) {

    double fitness = 0;

    /*
     *  Calcular el fitness de la solución de la siguiente forma
     *   1. Obtener la máxima violación de las capacidades de las mochilas invocando la función de arriba
     *   2. Si es mayor a 0, entonces devolvemos dicha mayor violación multiplicada por -1.
     *   3. Si no, devolvemos la suma de los beneficios individuales y cuadráticos invocando a la función de arriba
     */
    if (instance.getMaxCapacityViolation(solution) > 0) {
        fitness = instance.getMaxCapacityViolation(solution) * (-1);
    } else {
        fitness = instance.getSumProfits(solution);
    }

    _numEvaluations++;
    return fitness;
}

double
MQKPEvaluator::computeDeltaFitness(MQKPInstance &instance, MQKPSolution &solution, int indexObject, int indexKnapsack) {

    _numEvaluations++;

    double actualMaxViolation = instance.getMaxCapacityViolation(solution);
    double deltaMaxCapacityViolation = instance.getDeltaMaxCapacityViolation(solution, indexObject, indexKnapsack);
    double newMaxViolation = actualMaxViolation + deltaMaxCapacityViolation;
    double actualSumProfits = instance.getSumProfits(solution);
    double deltaSumProfits = instance.getDeltaSumProfits(solution, indexObject, indexKnapsack);
    double newSumProfits = actualSumProfits + deltaSumProfits;

    if (actualMaxViolation > 0 && newMaxViolation > 0) {
        return deltaMaxCapacityViolation * (-1);
    } else if (actualMaxViolation == 0 && newMaxViolation == 0) {
        return deltaSumProfits;
    } else if (actualMaxViolation > 0 && newMaxViolation == 0) {
        return newSumProfits + deltaMaxCapacityViolation * (-1);
    } else if (newMaxViolation > 0 && actualMaxViolation == 0) {
        return (newMaxViolation + actualSumProfits) * (-1);
    } else {
        return 0.0;
    }
}

void MQKPEvaluator::resetNumEvaluations() {
    _numEvaluations = 0;
}
