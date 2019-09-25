/*
 * main.cpp
 *
 * File which defines the main fucntion for running experiments over the Multiple Quadratic Knapsack Problem.
 * Specifically, these experiments generate random solutions over the four instances and store the best solution
 * found up to the moment.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

//Definition of some parameters of the experimentation
#define MAX_SECONS_PER_RUN 5
#define MAX_SOLUTIONS_PER_RUN 100000
#define NUM_RUNS 5


#include "MQKPEvaluator.h"
#include "MQKPInstance.h"
#include "MQKPSolGenerator.h"
#include "MQKPSolution.h"
#include "Timer.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cfloat>

using namespace std;


//External definition of the seeds for the random number generator (in seeds.cpp)
extern unsigned int numSeeds;
extern unsigned int seeds[];

/**
 * Function for the generation of random solutions, during MAX_SECONS_PER_RUN seconds and with a maximum of MAX_SOLUTIONS_PER_RUN,
 * for the instance passed as a parameter
 * @param[out] results array where we store the fitness values of the randomly generated solutions
 * @param[in] instance Instance of the MQKP
 */
void runARandomSearchExperiment(vector<double> &results, MQKPInstance &instance){

	MQKPSolution currentSolution(instance);
	Timer t;
	unsigned int numSolutions = 0;

	//While there is time and not too many solutions have been generated, generate a random solution and store the result
	while (t.elapsed_time(Timer::VIRTUAL) <= MAX_SECONS_PER_RUN && numSolutions < MAX_SOLUTIONS_PER_RUN){
		MQKPSolGenerator::genRandomSol(instance, currentSolution);
		double currentFitness = MQKPEvaluator::computeFitness(instance, currentSolution);
		results.push_back(currentFitness);
		numSolutions++;
	}
}

/**
 * Function which runs all the experiments for arguments passed in the command line to the main program.
 * Specifically, NUM_RUNS experiments for each instance.
 * @param[out] results 3D matrix where the results will be saved. The first index will be the instance considered,
 *                     the second index will be the experiment and the third index will be the solution generated
 *                     in this experiment.
 * @param[in] mainArgs Arguments of the main function (argv). These arguments are organized, from the first index, as:
 *                     <filename of instance 1> <number of knapsacks> <filename of instance 2> <number of knapsacks>...
 * @param[in] numMainArgs Number of arguments of the main function (argc)
 */
void runExperiments(vector< vector< vector< double>* >* > &results, char **mainArgs, unsigned int numMainArgs){

	//For each instance of the problem
	for (unsigned int iInstance = 1; iInstance < numMainArgs; iInstance += 2){

		//Read the instance and create the data structures needed to store the results
		MQKPInstance instance;
		vector< vector < double >* >* resultsOnThisInstance = new vector< vector< double >* >;
		results.push_back(resultsOnThisInstance);
		char *instanceName = mainArgs[iInstance];
		unsigned int numKnapsacks = atoi(mainArgs[iInstance + 1]);
		instance.readInstance(instanceName, numKnapsacks);

		//Run NUM_RUNS executions over this instance
		for (unsigned int r = 1; r <= NUM_RUNS && r < numSeeds; r++){
			srand(seeds[r]); //Initialization of the random number generator before each execution
			vector<double> *theseResults = new vector<double>;
			resultsOnThisInstance->push_back(theseResults);
			runARandomSearchExperiment(*theseResults, instance);
		}
	}
}

/**
 * Function returning the number of solutions in the run resulting in more solutions.
 * @param[in] results 2D matrix with the results of the different runs. The first index is for the runs, the second is for the solutions in a given run.
 * @return Longest number of solutions.
 */
unsigned int getLongestRunLength(vector< vector< double >* > &results){

	unsigned int maxLength = 0;
	unsigned int numRuns = results.size();

	for (unsigned int iRun = 0; iRun < numRuns; iRun++){

		unsigned int length = results.at(iRun)->size();
		if (length > maxLength){
			maxLength = length;
		}
	}

	return maxLength;
}

/**
 * Structure to calculate and store the outputs of the program, average of the solutions of the current iteration and average of the best solutions from the beginning to the current iteration.
 */
struct currentBestPair{
	double current;
	double best;
};

/**
 * Function for obtaining the averages for the results of several runs.
 * @param[in] results 2D matrix with the results of the different runs. The first index is for the runs. The second index is for the solutions of a run.
 * @param[out] means Vector where the average results are stored, in currentBestPair structures, that is, with the average of the solutions in current
 *                   iteration and the average of the best solutions from the beginning to the current iteration.
 */
void computeMeans(vector< vector<double>* > &results, vector<currentBestPair> &means, unsigned int overallLongestRun){
	//Obtain the number of elements of the longest run
	unsigned int numRuns = results.size();
	currentBestPair previousMean;
	previousMean.best = -DBL_MAX;

	//Calculate the average
	for (unsigned int iSolutions = 0; iSolutions < overallLongestRun; iSolutions++){
		currentBestPair currentMean;
		currentMean.current = 0;
		currentMean.best = 0;
		double value;

		if (iSolutions == 0){

			for (unsigned int iRun = 0; iRun < numRuns; iRun++){

				unsigned int length = results.at(iRun)->size();
				if (length <= iSolutions){
					value = results.at(iRun)->back();
					currentMean.current += value;
				}else{
					value = results.at(iRun)->at(iSolutions);
					currentMean.current += value;
				}

				currentMean.best += value;
			}
		}
		else {
			for (unsigned int iRun = 0; iRun < numRuns; iRun++){

				unsigned int length = results.at(iRun)->size();
				if (length <= iSolutions){
					value = results.at(iRun)->back();
					currentMean.current += value;
				}else{
					value = results.at(iRun)->at(iSolutions);
					currentMean.current += value;
				}

				currentMean.best += max(value, previousMean.best);
			}
		}

		currentMean.current /= numRuns;
		currentMean.best /= numRuns;
		means.push_back(currentMean);
		previousMean.best = currentMean.best;
	}

}

/**
 * Function to free the memory of a 2D vector
 * @param[in] array 2D vector whose memory is going to be freed
 */
template <typename T>
void free2Darray(vector< vector<T>* > &array){

	int numVectors = array.size();

	for (int i = 0; i < numVectors; i++){
		array.at(i)->clear();
		delete (array.at(i));
	}

	array.clear();
}

/**
 * Function to free the memory of a 3D vector
 * @param[in] array 3D vector whose memory is going to be freed
 */
template <typename T>
void free3Darray(vector< vector <vector<T>*>*> &array){

	int numArrays = array.size();

	for (int i = 0; i < numArrays; i++){
		free2Darray(*(array.at(i)));
		delete (array.at(i));
	}

	array.clear();
}

/**
 * Main function running the experimentation. Generation of random solutions for the instances.
 *
 * Finally, the results generated in matrix form are written to the standard output. For each instance, two columns are generated,
 * one with the average results of the solutions generated in each iteration and other with average results
 * of the best solution found from the beginning to one given iteration.
 */
int main(int argc, char **argv) {

	if (argc < 3 || (argc % 2) != 1){
		cout << argv[0] << " (<problem instance files> <numKnapsacks>)+" << endl;
		return 0;
	}



	//////////////////////////
	//Experiment execution
	//////////////////////////
	unsigned int numInstances = (argc - 1) / 2;
	vector< vector< vector< double >* >* > allTheResults;
	//All the fitness values generated will be saved in the matrix allTheResults
	//It is a 3D matrix
	//-> First index for the instance
	//-> Second index for the runs performed over the same instance
	//-> Third index for the solutions generated during the run

	runExperiments(allTheResults, argv, argc);




	////////////////////////////
	//Average value calculation
	////////////////////////////
	unsigned int overallMaxNumResults = 0;
	vector< vector< currentBestPair>* > meanResults;
	//The results will be stored in the meanResults matrix, but averaging each iteration of the search process
	// (average of the first solutions of the different runs, the same for the second solutions...)
	//It is a 2D matrix
	//-> First index for the instance
	//-> Second index for the average value obtained for each iteration of the algorithm

	// Obtain the length of the overall longest run
	overallMaxNumResults = 0;
	for (unsigned int iInstance = 0; iInstance < numInstances; iInstance++){
		unsigned int longestRunLength = getLongestRunLength(*allTheResults.at(iInstance));

		if (longestRunLength > overallMaxNumResults){
			overallMaxNumResults = longestRunLength;
		}
	}

	//For each instance of the problem, obtain the average values
	for (unsigned int iInstance = 0; iInstance < numInstances; iInstance++){
		vector< vector< double >* > *resultsThisInstance = allTheResults.at(iInstance);
		vector< currentBestPair > *theseMeans = new vector<currentBestPair>;
		meanResults.push_back(theseMeans);
		computeMeans(*resultsThisInstance, *theseMeans, overallMaxNumResults);
	}


	//////////////////////
	// Printing the results
	//////////////////////
	for (int iInstance = 1; iInstance < argc; iInstance += 2){
		cout << argv[iInstance] << "_" << argv[iInstance + 1] << "_best\t";
		cout << argv[iInstance] << "_" << argv[iInstance + 1] << "_current\t";
	}
	cout << endl;

	for (unsigned int iIteration = 0; iIteration < overallMaxNumResults; iIteration++){
		for (unsigned int iInstance = 0; iInstance < numInstances; iInstance++){
			cout << meanResults.at(iInstance)->at(iIteration).best << "\t";
			cout << meanResults.at(iInstance)->at(iIteration).current << "\t";
		}
		cout << endl;
	}




	//////////////////////
	// Freeing memory
	//////////////////////
	free3Darray(allTheResults);
	free2Darray(meanResults);

	return 0;
}
