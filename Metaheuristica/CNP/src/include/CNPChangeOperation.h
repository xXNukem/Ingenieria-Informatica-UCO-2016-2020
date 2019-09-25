/*
 * CNPChangeOperation.h
 *
 * Fichero que declara la clase CNPChangeOperation. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author José Luis Gordillo Relaño <i62gorej@uco.es>
 */

#ifndef __CNPCHANGEOPERATION_H__
#define __CNPCHANGEOPERATION_H__

#include "CNPSolution.h"

/**
 * Clase abstracta para representar cualquier operación de modificación sobre una solución.
 */
class CNPChangeOperation{
public:

	/**
	 * Destructor
	 */
	virtual ~CNPChangeOperation(){
	}

	/**
	 * Función que aplica el cambio que define el objeto sobre la solución que recibe como argumento
	 * @param[in,out] solution Objeto solución sobre el que se aplicará el cambio
	 */
	virtual void apply(CNPSolution &solution) = 0;
};

#endif
