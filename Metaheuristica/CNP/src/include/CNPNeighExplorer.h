/*
 * CNPNeighExplorer.h
 *
 * Fichero que define la clase CNPNeighExplorer. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_CNPNEIGHEXPLORER_H_
#define INCLUDE_CNPNEIGHEXPLORER_H_

#include <CNPSolution.h>
#include <CNPInstance.h>
#include <CNPChangeOperation.h>

/**
 * clase abstracta que define las operaciones de cualquier operador que explora la vecindad de una solución dada.
 */
class CNPNeighExplorer
{
public:
    /**
	 * Destructor
	 */
    virtual ~CNPNeighExplorer() {}

    /**
	 * Función que busca una operación que aplicada a la solución devuelva otra solución vecina. Se utilizará para buscar una solución vecina que la mejore, o la mejor de las soluciones vecinas.
	 *
	 * @param[in] instance Instancia del problema de la múltiples mochilas cuadráticas
	 * @param[in] solution Solución cuya vecindad va a ser explorada
	 * @param[out] operation Operación que se devuelve al explorar la vecindad.
	 *
	 * @return Devuelve verdadero si ha encontrado una operación válida, que mejora la solution y que se ha almacenado en operation. Falso en otro caso
	 */
    virtual bool findOperation(CNPInstance &instance, CNPSolution &solution, CNPChangeOperation &operation) = 0;

    void randomPermutation(int size, vector<int> &perm)
    {

        /** TODO
     * 1. Vacía el vector perm
     * 2. Llénalo con la permutación identidad
     * 3. Recórrelo intercambiando cada elemento con otro escogido de forma aleatoria.
     */
        perm.clear();
        for (int i = 0; i < size; i++)
            perm.push_back(i);

        for (int i = 0; i < size; i++)
        {
            //generando posicion aleatoria
            int randomPos = rand() % size;

            //intercambiando posiciones
            int aux;
            aux = perm.at(i);
            perm.at(i) = perm.at(randomPos);
            perm.at(randomPos) = aux;
        }
        ///
    }
};

#endif /* INCLUDE_CNPNEIGHEXPLORER_H_ */
