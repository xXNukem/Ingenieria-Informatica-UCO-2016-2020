/*
 * CNPCrossoverOperator.h
 *
 * Fichero que define la clase CNPCrossoverOperator. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author José Luis Gordillo Relaño <i62gorej@uco.es>
 */

#ifndef INCLUDE_CNPCROSSOVEROPERATOR_H_
#define INCLUDE_CNPCROSSOVEROPERATOR_H_

#include <CNPSolution.h>
#include <Solution.h>
#include <CNPInstance.h>
#include <vector>


using namespace std;

/**
 * Clase que implementa un operador de cruce uniforme para el problema CNP. Su idea es la misma que la de un cruce uniforme para codificación entera
 */
class CNPCrossoverOperator
{

protected:
	/**
	 * Variables miembro de la clase:
	 *  - _instance Instancia de problema abordada. Se utiliza únicamente para crear nuevos objetos CNPSolution
	 *  - _numNodes almacena el número de nodos total del grafo
	 *  - _crossProb probabilidad de cruce
	 */
	CNPInstance *_instance;
	unsigned _numNodes;
	double _crossProb;

	/**
	 * Función que cruza dos soluciones según su probabilidad de cruce. En caso de que no haya crucce, la solución devuelta será igual al mejor padre
	 * @param[in] s1 primer padre
	 * @param[in] s2 segundo padre
	 * @return Nuevo objeto solución descendiente de haber cruzado s1 y s2. La solución se reserva dinámicamente en memoria. Es responsabilidad del invocador de gestionarla correctamente.
	 */
	CNPSolution *cross(Solution *s1, Solution *s2)
	{
		CNPSolution *sol = new CNPSolution(*_instance);
		CNPSolution *sol1 = (CNPSolution *)s1;
		CNPSolution *sol2 = (CNPSolution *)s2;

		double randSample = (((double)rand()) / RAND_MAX);
		int i = 0;
		int numTries = 0;
		if (randSample < _crossProb)
		{
			//Cruce uniforme de los dos padres,
			//que va eligiendo el valor de uno de los padres aleatoriamente,
			//con la misma probabilidad, para cada gen
			while (sol->getSolSize() < _instance->getNumNodesSol() && i < _instance->getNumNodesSol() && numTries < 500)
			{
				if ((((double)rand()) / RAND_MAX) < 0.5)
				{
					if (!sol->checkDuplicity(sol1->getNodeFromSol(i)))
					{
						sol->addNodeToSol(sol1->getNodeFromSol(i));
						i++;
					}
				}
				else
				{
					if (!sol->checkDuplicity(sol2->getNodeFromSol(i)))
					{
						sol->addNodeToSol(sol2->getNodeFromSol(i));
						i++;
					}
				}
				numTries++;
			}
			if (CNPEvaluator::compare(sol1->getFitness(), sol2->getFitness()) < 0)
				sol->copy(*sol1);
			else
				sol->copy(*sol2);

		}
		else
		{
			//Si no hay cruce, copiar el mejor padre
			if (CNPEvaluator::compare(sol1->getFitness(), sol2->getFitness()) < 0)
				sol->copy(*sol1);
			else
				sol->copy(*sol2);
		}
		return sol;
	}

public:
	/**
	 * Constructor
	 * @param[in] crossProb Probabilidad de cruce
	 * @param[in] instance Instancia del problema abordada
	 */
	CNPCrossoverOperator(double crossProb, CNPInstance &instance)
	{
		_instance = &instance;
		_numNodes = instance.getNumNodes();
		_crossProb = crossProb;
	}

	/**
	 * Función que aplica el cruce a una población de padres.
	 * @param[in] parents Vector de padres. El cruce se aplica entre cada dos padres consecutivos (1,2), (3,4)...
	 * @param[out] offspring Vector donde se almacenan los descendientes generados. IMPORTANTE: Esta función reserva memoria dinámicamente para las nuevas soluciones en offspring, por lo que es responsabilidad de quien la invoque de gestionar la memoria adecuadamente.
	 */
	void cross(vector<Solution *> &parents, vector<Solution *> &offspring)
	{

		unsigned numParents = (unsigned)parents.size();

		//Se aplica cruce entre cada dos padres consecutivos (1,2), (3,4), ...
		offspring.clear();

		for (int i = 0; i < parents.size(); i = i + 2)
		{
			CNPSolution *sol = cross(parents[i], parents[i + 1]);
			offspring.push_back(sol);
		}
	}
};

#endif /* INCLUDE_CNPCROSSOVEROPERATOR_H_ */
