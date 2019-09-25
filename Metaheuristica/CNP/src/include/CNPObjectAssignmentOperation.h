/* CNPObjectAssignmentOperation.h
 *
 * Fichero que declara la clase CNPObjectAssignmentOperation. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author José Luis Gordillo Relaño
 * @author Alberto Luque Rivas
 * @author Carlos de la barrera Perez
 */

#ifndef __CNPOBJECTASSIGNMENTOPERATION_H__
#define __CNPOBJECTASSIGNMENTOPERATION_H__

#include "CNPChangeOperation.h"
#include "CNPSolution.h"

/**
 * Clase que codifica una operación de asignación de un objeto a una mochila, pudiendo ser ésta la mochila 0, es decir, sacarlo de la mochila en la que se encuentre
 */
class CNPObjectAssignmentOperation : public CNPChangeOperation
{

protected:
	//las variables miembro de la clase según lo indicado en el guión de prácticas (_indexObj, _indexKnapsack, _deltaFitness)
	int _node;
	int _indexNodeChanged;
	double _deltaFitness;

public:
	/**
	 * Constructor
	 */
	CNPObjectAssignmentOperation();

	/**
	 * Destructor
	 */
	virtual ~CNPObjectAssignmentOperation();

	/**
	 * Función que aplica el cambio que define el propio objeto sobre la solución que recibe como argumento.
	 * @param[in, out] solution Objeto solución sobre el que se aplicará el cambio
	 */
	virtual void apply(CNPSolution &solution);

	/**
	 * Función que asigna los valores la operación
	 * @param[in] Node Nodo que se va a aplicar a la solución
	 * @param[in] indexSol El índice del objeto a sustituir en el vector solución
	 * @param[in] deltaFitness La diferencia en fitness de aplicar dicha operación de asignación de un nodo al grafo
	 */
	void setValues(int node, int indexNodeChanged, double deltaFitness);

	/**
	 * Función que devuelve el objeto sujeto de la operación
	 * @return índice del objeto sujeto de la operación
	 */
	unsigned getNode()
	{
		return _node;
	}

	/**
	 * Función que devuelve la diferencia en fitness de la operación,
	 * @return Diferencia en fitness de la operación (siempre que la solución actual no se hubiese cambiado cuando se calculo dicha diferencia)
	 */
	double getDeltaFitness()
	{
		return _deltaFitness;
	}

	/**
	 * Función que devuelve la mochila objeto de la operación
	 * @return mochila objeto de la operación
	 */
	unsigned getIndexNode()
	{
		return _indexNodeChanged;
	}
};

#endif

