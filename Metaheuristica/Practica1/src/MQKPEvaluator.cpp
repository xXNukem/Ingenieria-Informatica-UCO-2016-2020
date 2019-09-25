/*
 * MQKPEvaluator.cpp
 *
 * Fichero que define los métodos de la clase MQKPEvaluator. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include "MQKPEvaluator.h"
#include "MQKPSolution.h"
#include "MQKPInstance.h"

double MQKPEvaluator::computeFitness(MQKPInstance &instance, MQKPSolution &solution){
	double violated = instance.getMaxCapacityViolation(solution);
	return (violated > 0.0) ? violated*-1 : instance.getSumProfits(solution);
}



