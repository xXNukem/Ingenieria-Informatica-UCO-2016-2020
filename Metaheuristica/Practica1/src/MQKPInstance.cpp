/*
 * MQKPInstance.cpp
 *
 * Fichero que define los métodos de la clase MQKPInstance. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <fstream>
#include <iostream>
#include "MQKPInstance.h"
#include "MQKPSolution.h"

MQKPInstance::MQKPInstance() {
	_numObjs=0;
	_numKnapsacks=0;
}

MQKPInstance::~MQKPInstance() {
	_weights.clear();
	_capacities.clear();
	_profits.clear();
}

int MQKPInstance::getNumObjs() const {
	return _numObjs;
}

int MQKPInstance::getNumKnapsacks() const {
    return _numKnapsacks;
}
int MQKPInstance::getWeight(int index)const {
	return _weights[index];
}

double MQKPInstance::getCapacity(int index)const {
	return _capacities[index];
}

void MQKPInstance::setNumObjs(int NumObjs) {
	_numObjs=NumObjs;
}

void MQKPInstance::setNumKnapsacks(int numKnapsacks) {
	_numKnapsacks=numKnapsacks;
}

double MQKPInstance::getMaxCapacityViolation(MQKPSolution &solution) {

	double *sumWeights = new double[this->_numKnapsacks + 1];

	for (int j = 1; j <= this->_numKnapsacks; j++) {
		sumWeights[j] = 0;
	}

	for (int i = 0; i < this->_numObjs; i++) {
		int value = solution.whereIsObject(i);
		if(value > 0) sumWeights[value] = sumWeights[value] + this->getWeight(i);
	}

	double maxCapacityViolation = 0; //Inicializamos la máxima violación de alguna mochila a 0, que significa que no hay ninguna violación

	for (int j = 1; j <= this->_numKnapsacks; j++) {
		double violation = sumWeights[j] - this->getCapacity(j);
		if (violation > maxCapacityViolation) maxCapacityViolation = violation;
	}
	delete[] sumWeights;
	return maxCapacityViolation;
}

double MQKPInstance::getSumProfits(MQKPSolution &solution) {

	double sumProfits = 0.;
	int _numObjs = this->_numObjs, indexX = 0, indexY = 0;
	for(int i = 0; i < _numObjs; i++){
		indexX = solution.whereIsObject(i);
		if(indexX > 0){
			sumProfits += this->_profits[i][i];
			for(int j = (i+1); j < _numObjs; j++){
				indexY = solution.whereIsObject(j);
				if (indexX == indexY) sumProfits += this->_profits[i][j];
			}
		}

	}
	return sumProfits;
}

void MQKPInstance::readInstance(char *filename, int numKnapsacks) {

	std::ifstream file( filename );

	if(!file.good())
		exit(-1);
	else {
		std::string nameInstance, discard;
		int numObject=0;
		double sumWeights=0;

		file >> nameInstance;
		file >> numObject;
		setNumObjs(numObject);
		setNumKnapsacks(numKnapsacks);

		_profits.resize(numObject, vector<int >(numObject));
		for(int i = 0; i < numObject - 1; i++)
			file >> _profits[i][i];


		for(int i = 0; i < numObject - 1; i++) {
			for(int j = (i + 1); j < numObject; j++) {
				file >> _profits[i][j];
				_profits[j][i]=_profits[i][j];
			}
		}

		file >> discard;
		file >> discard;
		file >> discard;

		_weights.resize(numObject);
		_capacities.resize(numKnapsacks + 1);

		for(int i = 0; i < numObject; i++){
			file >> this->_weights[i];
			sumWeights+=_weights[i];
		}

		sumWeights*=0.8;
		sumWeights/=numKnapsacks;
		fill(_capacities.begin(), _capacities.end(), sumWeights);
		file.close();
	}
}
