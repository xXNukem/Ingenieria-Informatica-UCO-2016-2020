#ifndef _CNPSOLUTION_H_
#define _CNPSOLUTION_H_

#ifndef __MQKPINSTANCE_H__
#include "CNPInstance.h"
#else
class MQKPInstance;
#endif

#include <vector>
#include <algorithm>
#include "Solution.h"

using namespace std;

class CNPSolution : public Solution
{
protected:
    vector<int> _sol; //vector de solucion
    double _fitness;  //valor de la calidad de la solución
    bool _fitnessAssigned;
    int _nodesSolSize;
public:
    /**
     * @brief Construct a new CNPSolution object
     * 
     * @param instance 
     */
    CNPSolution();
    CNPSolution(CNPInstance &instance);

    /**
     * @brief Destroy the CNPSolution object
     * 
     */
    virtual ~CNPSolution();

    /**
     * @brief Add a node to solution vector
     * 
     * @param node 
     */
    void addNodeToSol(int node);
    /**
     * @brief Get the Node From Sol object
     * 
     * @param index 
     * @return int 
     */
    int getNodeFromSol(int index);
    /**
     * @brief Copy actual solution object from solution object argument
     * 
     * @param solution 
     */
    virtual void copy(Solution &solution);

    /**
     * @brief Get the Fitness object
     * 
     * @return double 
     */
    virtual double getFitness() const;

    /**
     * @brief Set the Fitness object
     * 
     * @param fitness 
     */
    void setFitness(double fitness);
    /**
     * @brief Check node duplicity in array
     * 
     * @param node to search
     * @return true if exists
     * @return false if not exits
     */
    bool checkDuplicity(int node);
    /**
     * @brief Get the Sol Size object
     * 
     * @return int 
     */
    int getSolSize();
    /**
     * @brief Change node into sol array
     * 
     * @param index 
     * @param node 
     */
    void changeNode(int index, int node);
    /**
     * @brief Delete node from sol array
     * 
     * @param Node to be erased
     */
    void deleteNode(int node);

	/**
	 * Función que indica si el fitness de la solución es válido (deja de serlo si se cambia un objeto de mochila; y se convierte en válido cuando se le asigna)
	 *
	 */
	bool hasValidFitness(){
		return _fitnessAssigned;
	}
};

#endif
