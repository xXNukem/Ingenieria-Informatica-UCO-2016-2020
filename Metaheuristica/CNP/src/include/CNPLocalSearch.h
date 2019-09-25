/**
 * CNPLocalSearch.h
 *
 * Fichero que define la clase CNPLocalSearch. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_CNPLOCALSEARCH_H_
#define INCLUDE_CNPLOCALSEARCH_H_

#include <CNPInstance.h>
#include <CNPSolution.h>
#include <CNPNeighExplorer.h>

/**
 * Clase que implementa la optimización local repetitiva de una solución dada.
 */
class CNPLocalSearch
{

	/**
	 * vector de doubles donde almacena la calidad de la última solución aceptada
	 */
	vector<double> _results;

public:
	/**
	 * Constructor
	 */
	CNPLocalSearch();

	/**
	 * Destructor
	 */
	~CNPLocalSearch();

	/**
	 * Función que optimiza una solución aplicado repetidamente la exploración de su vecindario hasta alcanzar un óptimo local.
	 * @param[in] instance Instancia del problema
	 * @param[in] explorer Operador de exploración del vecindario. La idea es que reciba un operador que bien explore el vecindario devolviendo la primera solución que mejora a la actual, o devolviendo el mejor cambio posible sobre la solución actual
	 * @param[in,out] solution Solución inicial que se optimiza localmente. El resultado final se devuelve en ella.
	 */
	void optimise(CNPInstance &instance, CNPNeighExplorer &explorer, CNPSolution &solution);

	/**
	 * Función que devuelve el vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 *
	 * @return vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 */
	vector<double> &getResults()
	{
		return _results;
	}
};

#endif /* INCLUDE_CNPLOCALSEARCH_H_ */
