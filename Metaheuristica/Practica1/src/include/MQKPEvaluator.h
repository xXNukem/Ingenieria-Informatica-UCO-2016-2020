/**
 * MQKPEvaluator.h
 * 
 * Fichero que define la clase MQKPEvaluator. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
*/

#ifndef __MQKPEvaluator_H__
#define __MQKPEvaluator_H__

#include "MQKPInstance.h"
#include "MQKPSolution.h"
#include <time.h>
#include <stdlib.h>

/**
 * Clase que calcula el fitness de una solución al problema MQKP
 */
class MQKPEvaluator {

public:
	/**
	 * Función que calcula el fitness de una solución
	 * @param[in] instance Referencia a un objeto con la información de la instancia del problema MQKP
	 * @param[in] solution Referencia a un objeto que representa una solución al problema.
	 * 
	 * @return Fitness de la solución. Será negativa si se viola la capacidad de alguna mochila y positiva si la solución es factible. En ese caso, el valor es igual a la suma de los beneficios individuales y cuadráticos
	 */
	static double computeFitness(MQKPInstance &instance, MQKPSolution &solution);
};

#endif