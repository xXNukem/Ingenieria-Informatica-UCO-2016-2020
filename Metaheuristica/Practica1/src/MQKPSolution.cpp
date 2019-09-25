/*
 * MQKPSolution.cpp
 *
 * Fichero que define los métodos de la clase MQKPSolution. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include "MQKPSolution.h"
#include "MQKPInstance.h"

MQKPSolution::MQKPSolution(MQKPInstance &instance) {
	_numObjs=instance.getNumObjs();
	_fitness=0;
	_sol.resize(instance.getNumObjs());
	fill(_sol.begin()+1,_sol.end(),0);
}

MQKPSolution::~MQKPSolution() {
	_sol.clear();
	_numObjs=0;
	_fitness=0;
}

void MQKPSolution::putObjectIn(int object, int knapsack){
	_sol[object]=knapsack;
}

int MQKPSolution::whereIsObject(int object){
	return _sol[object];
}

