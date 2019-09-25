/*
 * CNPSimpleFirstImprovementNO.h
 *
 * Fichero que define la clase CNPSimpleFirstImprovementNO. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_CNPSIMPLEFIRSTIMPROVEMENTNO_H_
#define INCLUDE_CNPSIMPLEFIRSTIMPROVEMENTNO_H_

#include <CNPNeighExplorer.h>
#include <CNPSolution.h>
#include <CNPChangeOperation.h>
/**
 * Clase que se encarga de explorar el vecindario de una solución dada, devolviendo la primera operación de asignación de un objeto a una mochila que encuentre que mejore la calidad de la solución recibida. En caso de que no exista ninguna operación que mejore la calidad de la solución recibida, entonces devolverá FALSE
 */
class CNPSimpleFirstImprovementNO : public CNPNeighExplorer{

public:

	/**
	 * Destructor
	 */
	virtual ~CNPSimpleFirstImprovementNO(){

	}

	/**
	 * Función que explora el vecindario de una solución dada, devolviendo la primera operación de asignación de un objeto a una mochila que encuentre que mejora la solución actual, devolverá FALSE si la operación devuelta no mejora a la solución actual
	 * @param[in] instance Instancia del problema
	 * @param[in] solution Solución cuya vecindad se va a explorar
	 * @param[out] operation Operación tal que aplicada a la solución, devuelve una vecina.
	 *
	 * @return true si la operación devuelta mejora a solution; false, si no hay ninguna operación en la vecindad que pueda mejorar a solution
	 */
	virtual bool findOperation(CNPInstance &instance, CNPSolution &solution, CNPChangeOperation &operation);
};


#endif /* INCLUDE_CNPSIMPLEFIRSTIMPROVEMENTNO_H_ */
