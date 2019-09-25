/*
 * CNPInstance.cpp
 *
 * Final Practice CNP Problem
 *
 * @author José Luis Gordillo Relaño
 */

#include <fstream>
#include <iostream>
#include "CNPInstance.h"
#include <boost/graph/connected_components.hpp>
typedef boost::property<boost::edge_weight_t, float> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, EdgeWeightProperty> Graph;

CNPInstance::CNPInstance()
{
    _numNodes = 0;
    _densityGraph = 0.0;
}

CNPInstance::~CNPInstance()
{
    _numNodes = 0;
    _densityGraph = 0.0;
    _BCentralityVec.clear();
    _AdjMatrix.clear();
}
int CNPInstance::getBCNumNodes(){return _BCentralityVec.size();}
int CNPInstance::getNumNodes() const { return num_vertices(_graph); }
double CNPInstance::getDensity() const { return _densityGraph; }
int CNPInstance::getMatrix(int row, int col) const { return _AdjMatrix[row][col]; }
double CNPInstance::getBCElement(int index) const { return _BCentralityVec[index]; }
void CNPInstance::setNumNodes(int n) { _numNodes = n; }
void CNPInstance::setDensity(double density) { _densityGraph = density; }
void CNPInstance::setNumNodesSol(int numNodes) { 
    assert(numNodes > 0);
    _numNodesSol = numNodes;
};
int CNPInstance::getNumNodesSol() const { return _numNodesSol; };

void CNPInstance::readInstance(char *filename)
{
    ifstream file(filename);
    if (!file.good())
    {
        std::cout << "Error: File " << filename << " not found or with errors" << std::endl;
        exit(-1);
    }
    Graph g;
    EdgeWeightProperty weight = 1; //Edge Weight = 1
    file >> _numNodes;
    file >> _densityGraph;
    _AdjMatrix.resize(_numNodes, std::vector<int>(_numNodes));
    // Generated vertex and added to auxiliar graph

    for (int i = 0; i < _numNodes; i++)
    {
        Graph::vertex_descriptor vertex = boost::add_vertex(g);
        _vecVertex.push_back(vertex);
    }
    // Looping Upper triangular matrix, generate vertex and adjMatrix
    for (int i = 0; i < _numNodes; i++)
    {
        for (int j = i; j < _numNodes; j++)
        {
            int flag = 0;
            file >> flag;
            if (flag && i != j)
            {
                boost::add_edge(_vecVertex.at(i), _vecVertex.at(j), weight, g);
                _AdjMatrix[i][j] = 1;
            }
        }
    }
    file.close();

    _graph = g;
}
double CNPInstance::getBetweennessCentrality()
{
    typedef boost::property_map<Graph, boost::vertex_index_t>::type VertexIndexMap;
    VertexIndexMap v_index = get(boost::vertex_index, _graph);
    std::vector<double> v_centrality_vec(boost::num_vertices(_graph), 0.0);
    boost::iterator_property_map<std::vector<double>::iterator, VertexIndexMap>
        v_centrality_map(v_centrality_vec.begin(), get(boost::vertex_index, _graph));
    brandes_betweenness_centrality(_graph, v_centrality_map);

    _BCentralityVec = v_centrality_vec;
    
    double sumBC = 0;
    for (int i = 0; i < _BCentralityVec.size(); i++)
    {
        sumBC += _BCentralityVec.at(i);
    }
    return sumBC;
}

void CNPInstance::deleteEdge(int node)
{
    clear_vertex(_vecVertex[node], _graph);
    //remove_vertex(node, _graph);
}

void CNPInstance::printAdjMatrix()
{
    for (int i = 0; i < getNumNodes(); i++)
    {
        for (int j = 0; j < getNumNodes(); j++)
        {
            cout << this->getMatrix(i, j) << " - ";
        }
        cout << endl;
    }
}

void CNPInstance::PrintConnections()
{
    Graph::vertex_iterator vertexIt, vertexEnd;
    Graph::adjacency_iterator neighbourIt, neighbourEnd;
    tie(vertexIt, vertexEnd) = vertices(_graph);
    for (; vertexIt != vertexEnd; ++vertexIt)
    {
        cout << *vertexIt << " esta conectado con ";
        tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, _graph);
        for (; neighbourIt != neighbourEnd; ++neighbourIt)
            cout << *neighbourIt << " ";
        cout << "\n";
    }
}

int CNPInstance::getNumEdgesFromNode(int node){
    Graph::vertex_iterator vertexIt, vertexEnd;
    Graph::adjacency_iterator neighbourIt, neighbourEnd;
    tie(vertexIt, vertexEnd) = vertices(_graph);
    int numEdges = 0;
    for (; vertexIt != vertexEnd; ++vertexIt)
    {
        if(node == *vertexIt){
            tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, _graph);
            for (; neighbourIt != neighbourEnd; ++neighbourIt)
                numEdges++;
        }
    } 
    return numEdges;
}
void CNPInstance::copyBCArray(CNPInstance &instance){
    this->_BCentralityVec = instance._BCentralityVec;
}
int CNPInstance::getBcElementIndex(double bc){
    std::vector<double>::iterator it = std::find(_BCentralityVec.begin(), _BCentralityVec.end(), bc);
    int index = std::distance(_BCentralityVec.begin(), it);
    return index;
}