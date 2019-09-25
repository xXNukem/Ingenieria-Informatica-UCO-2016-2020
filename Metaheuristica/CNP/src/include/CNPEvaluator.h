#ifndef _CNPEVALUATOR_H_
#define _CNPEVALUATOR_H_
#include "CNPInstance.h"
#include "CNPSolution.h"

class CNPEvaluator
{
protected:
    static double _numEvaluations;

public:
    static double computeFitness(CNPInstance &instance, CNPSolution &solution);
	/**
	 * @brief Compute difference between actual fitness and new fitnes changing node index
	 * 
	 * @param instance 
	 * @param solution 
	 * @param index 
	 * @param node 
	 * @return double 
	 */
    static double computeDeltaFitness(CNPInstance &instance, CNPSolution &solution, int index, int node);
    /**
     * @brief Reset num evaluations
     * 
     */
    static void resetNumEvaluations();

	/**
	 * @brief Get the Num Evaluations object
	 * 
	 * @return unsigned 
	 */
    static unsigned getNumEvaluations(){
        return _numEvaluations;
    }
	/**
	 * @brief Compare numbers
	 * 
	 * @param f1 
	 * @param f2 
	 * @return 1 if f1 > f2, -1 if f1 < f2 and 0 if are equals
	 */
	static double compare(double f1, double f2){
		return (f1 > f2) ? 1.0 : (f1 < f2) ? -1.0 : 0.0;
	}

	/**
	 * @brief Function that told if problem is to minimised or maximised
	 * 
	 * @return true 
	 * @return false 
	 */
	static bool isToBeMinimised(){
		return (compare(0,1) > 0);
	}    
};

#endif