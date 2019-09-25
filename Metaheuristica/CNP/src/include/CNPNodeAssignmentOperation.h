/* CNPObjectAssignmentOperation.h
 *
 * Fichero que declara la clase CNPObjectAssignmentOperation. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef __CNPOBJECTASSIGNMENTOPERATION_H__
#define __CNPOBJECTASSIGNMENTOPERATION_H__

#include <CNPChangeOperation.h>
#include <CNPSolution.h>

/**
 * Clase que codifica una operación de asignación de un objeto a una mochila, pudiendo ser ésta la mochila 0, es decir, sacarlo de la mochila en la que se encuentre
 */
class CNPNodeAssignmentOperation : public CNPChangeOperation
{

protected:
	/*
	 * TODO
	 * Crea las variables miembro de la clase según lo indicado en el guión de prácticas
	 */
	int _indexNode;
	int _node;
	double _deltaFitness;

public:
	/**
	 * Constructor
	 */
	CNPNodeAssignmentOperation();

	/**
	 * Destructor
	 */
	virtual ~CNPNodeAssignmentOperation();

	/**
	 * Función que aplica el cambio que define el propio objeto sobre la solución que recibe como argumento.
	 * @param[in, out] solution Objeto solución sobre el que se aplicará el cambio
	 */
	virtual void apply(CNPSolution &solution);

	/**
	 * Función que asigna los valores la operación
	 * @param[in] indexObject El índice del objeto que se va a cambiar de mochila
	 * @param[in] indexKnapsack El índice de la mochila donde se insertará el objeto
	 * @param[in] deltaFitness La diferencia en fitness de aplicar dicha operación de asignación de un objeto a una mochila (siempre que la solución actual no se hubiese cambiado cuando se calculo dicha diferencia)
	 */
	void setValues(int indexNode, int node, double deltaFitness);
	unsigned getNode(){
		return _node;
	}
};

#endif