/*
 * CNPNodeAssignmentOperation.cpp
 *
 * Fichero que define las funciones de la clase CNPNodeAssignmentOperation. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */
#include <CNPNodeAssignmentOperation.h>

CNPNodeAssignmentOperation::CNPNodeAssignmentOperation()
{
  _indexNode = 0;
  _node = 0;
  _deltaFitness = 0;
}

CNPNodeAssignmentOperation::~CNPNodeAssignmentOperation()
{
}

void CNPNodeAssignmentOperation::apply(CNPSolution &solution)
{
  solution.changeNode(_indexNode, _node);
  solution.setFitness(solution.getFitness() + this->_deltaFitness); //Jose luis no esta seguro pot la suma
}

void CNPNodeAssignmentOperation::setValues(int indexNode,
                                           int node, double deltaFitness)
{

  _indexNode = indexNode;
  _node = node;
  _deltaFitness = deltaFitness;
}