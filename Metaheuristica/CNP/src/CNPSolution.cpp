/*
 * CNPSolution.cpp
 *
 * Final Practice CNP Problem
 *
 * @author José Luis Gordillo Relaño
 * @author Alberto Luque Rivas
 * @author Carlos de la Barrera Perez
 */
#include "CNPSolution.h"

//--Constructor y destructor
CNPSolution::CNPSolution()
{
    _fitness = 0;
}
CNPSolution::CNPSolution(CNPInstance &instance)
{
    _fitness = 0;
    _fitnessAssigned = false;
    _nodesSolSize = instance.getNumNodesSol();
}

CNPSolution::~CNPSolution()
{
    _sol.clear();
    _fitnessAssigned = false;
    _fitness = 0;
}

//--Funciones de la clase
void CNPSolution::addNodeToSol(int node)
{
    _sol.push_back(node);
}

int CNPSolution::getNodeFromSol(int index)
{
    return _sol.at(index);
}

void CNPSolution::copy(Solution &solution)
{
	CNPSolution &auxSol = (CNPSolution&) solution;
    for (int i = 0; i < auxSol._nodesSolSize; i++)
		_sol.push_back(auxSol._sol[i]);

	_fitness = auxSol._fitness;
	_fitnessAssigned = auxSol._fitnessAssigned;
    _nodesSolSize = auxSol._nodesSolSize;
    assert(_fitness == auxSol._fitness);   
}

int CNPSolution::getSolSize()
{
    return _sol.size();
}

bool CNPSolution::checkDuplicity(int node)
{
    return (std::find(_sol.begin(), _sol.end(), node) != _sol.end()) ? true : false;
}

//--Métodos de acceso

void CNPSolution::setFitness(double fitness)
{
    _fitness = fitness;
    _fitnessAssigned = true;
}

double CNPSolution::getFitness() const
{
    return _fitness;
}

void CNPSolution::changeNode(int index, int node){
        //Intercambiamos un nodo y ordenamos el array solución
        this->_sol.at(index) = node;
}
void CNPSolution::deleteNode(int node){
    this->_sol.erase(std::remove(_sol.begin(), _sol.end(), node), _sol.end());
}