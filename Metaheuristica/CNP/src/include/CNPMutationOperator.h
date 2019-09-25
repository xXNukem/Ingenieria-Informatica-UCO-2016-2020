/*
 * CNPMutationOperator.h
 *
 * Fichero que define la clase CNPMutationOperator. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_CNPMUTATIONOPERATOR_H_
#define INCLUDE_CNPMUTATIONOPERATOR_H_

#include <CNPSolution.h>
#include <vector>
#include <cstdlib>

using namespace std;

/**
 * Clase que define un operador de mutación para el CNP. Se basa en recorrer todos los genes de la solución y cambiarlos por un valor aleatorio según una probabilidad
 */
class CNPMutationOperator{

protected:
	/**
	 * Variables miembro de la clase
	 * _mutProb Probabilidad de mutación
	 * _numObjs Número de objetos. Se utiliza para reducir el número de consultas a la instancia
	 * _numKnapsacks Número de mochilas del problema. Se utiliza para reducir el número de consultas a la instancia
	 */
	double _mutProb;
	unsigned _numNodes;
	unsigned _numNodesSol;

	/**
	 * Función que muta una solución
	 * @param[in,out] sol Solución a mutar
	 */
	void mutate(Solution* sol){
		CNPSolution *s = (CNPSolution*) sol;

		//Recorrer los objetos y, según la probabilidad de mutación,
		//asignarlos a una posición aleatoria (podrían modificarse 0, 1, o más de 1 gen)
		for(int i = 0; i < _numNodes; i++){
			if((double) rand()/(RAND_MAX) <= _mutProb){
				if(!s->checkDuplicity(i))
					s->changeNode(rand()%_numNodesSol, i);
			}
		}
	}

public:
	/**
	 * Constructor
	 * @param[in] mutProb Probabilidad de mutación
	 * @param[in] instance Instancia del problema a abordar
	 */
	CNPMutationOperator(double mutProb, CNPInstance &instance){
		_mutProb = mutProb;
		_numNodes = instance.getNumNodes();
		_numNodesSol = instance.getNumNodesSol();
	}

	/**
	 * Función que muta un conjunto de soluciones
	 * @param[in,out] sols Soluciones a mutar
	 */
	void mutate(vector<Solution*> &sols){

		for (Solution* sol : sols){
			mutate(sol);
		}
	}
};



#endif /* INCLUDE_CNPMUTATIONOPERATOR_H_ */
