#include <CNPEvaluator.h>
#include <CNPInstance.h>
#include <CNPSolGenerator.h>
#include <CNPSolution.h>
#include <CNPSimulatedAnnealing.h>
#include <CNPTabuSearch.h>
#include <CNPStopCondition.h>
#include <CNPLocalSearch.h>
#include <CNPSimpleFirstImprovementNO.h>
#include <CNPSimpleBestImprovementNO.h>
#include <Timer.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <funcionesAuxiliares.h>
extern unsigned int seeds[];
int main(int argc, char **argv)
{
	if (argc < 3)
	{
		cout << argv[0] << " <problem instance files> NumberNodeToDelete" << endl;
		return 0;
	}

	//////////////////////////
	//Ejecución de experimentos
	//////////////////////////
	unsigned int numInstances = (argc - 1) / 2;
	vector<vector<vector<double> *> *> allTheResults;
	srand(seeds[0]);
	//En la matriz allTheResults se almacenarán todos los valores de fitness generados
	//Es tridimensional
	//El primer índice recorre las instancias de los problemas que se han abordado
	//El segundo índice recorre las ejecuciones que se han hecho sobre la misma instancia
	//El tercer índice recorre las soluciones que se han generado en la misma ejecución
	runExperiments(allTheResults, argv, argc);

	//////////////////////
	// Impresión de resultados
	//////////////////////
	vector<double> lastResults;

	bool allResultsPrinted = false;
	unsigned int iIteration = 0;
	unsigned int indexColumn = 0;

	vector<unsigned> printColumns = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	vector<string> titles = { "currentFirstHC", "bestFirstHC", "currentBestHC", "bestBestHC", "currentSA", "bestSA", "currentTS", "bestTs", "currentIG", "bestIG", "currentGA", "bestGA", "bestGAPerIt", "popMeanGA", "offMeanGA"};

	for (unsigned int iInstance = 0; iInstance < numInstances; iInstance++) {

		for (auto indexColumnPerInstance : printColumns) {
			cout << argv[iInstance * 2 + 1] << "_" << argv[iInstance * 2 + 2]
					<< "_" << titles[indexColumnPerInstance] << "\t";
			lastResults.push_back(
					allTheResults.at(iInstance)->at(indexColumnPerInstance)->at(
							0));			
		}
	}
	cout << endl;
	allResultsPrinted = false;
	
	while (allResultsPrinted == false) {
		allResultsPrinted = true;
		for (unsigned int iInstance = 0; iInstance < numInstances;
				iInstance++) {

			for (auto indexColumnPerInstance : printColumns) {

				if (allTheResults.at(iInstance)->at(indexColumnPerInstance)->size()
						> iIteration) {
					allResultsPrinted = false;
					cout
							<< allTheResults.at(iInstance)->at(
									indexColumnPerInstance)->at(iIteration)
							<< "\t";
					lastResults[indexColumn] = allTheResults.at(iInstance)->at(
							indexColumnPerInstance)->at(iIteration);
				} else {
					cout << lastResults[indexColumn] << "\t";
				}
				indexColumn++;
			}
		}
		cout << endl;
		iIteration++;
		indexColumn = 0;
	}


	//////////////////////
	// Liberar memoria
	//////////////////////
	//free3Darray(allTheResults);
	return 0;
}