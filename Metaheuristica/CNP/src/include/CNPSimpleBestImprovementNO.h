/*
 * MKPSimpleBestImprovementNO.h
 *
 *  Created on: Jan 29, 2017
 *      Author: carlos
 */

#ifndef INCLUDE_CNPSIMPLEBESTIMPROVEMENTNO_H_
#define INCLUDE_CNPSIMPLEBESTIMPROVEMENTNO_H_

#include <CNPNeighExplorer.h>
#include <CNPSolution.h>
#include <CNPChangeOperation.h>
/**
 * Clase que se encarga de explorar el vecindario de una solución dada, devolviendo la mejor operación de asignación de un objeto a una mochila entre las operaciones posibles, devolverá FALSE si la operación devuelta no mejora a la solución actual
 */
class CNPSimpleBestImprovementNO : public CNPNeighExplorer{

public:

	/**
	 * Destructor
	 */
	virtual ~CNPSimpleBestImprovementNO(){

	}

	/**
	 * Función que explora el vecindario de una solución dada, devolviendo la mejor operación de asignación de un objeto a una mochila entre las operaciones posibles, devolverá FALSE si la operación devuelta no mejora a la solución actual
	 * @param[in] instance Instancia del problema
	 * @param[in] solution Solución cuya vecindad se va a explorar
	 * @param[out] operation Operación tal que aplicada a la solución, devuelve una vecina.
	 *
	 * @return true si la operación devuelta mejora a solution; false, si no hay ninguna operación en la vecindad que pueda mejorar a solution
	 */
	virtual bool findOperation(CNPInstance &instance, CNPSolution &solution, CNPChangeOperation &operation);

};


#endif /* INCLUDE_CNPSIMPLEBESTIMPROVEMENTNO_H_ */
