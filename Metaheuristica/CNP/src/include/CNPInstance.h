#ifndef _CNPINSTANCE_
#define _CNPINSTANCE_

#include <boost/graph/betweenness_centrality.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;
using namespace boost;
typedef boost::property<boost::edge_weight_t, float> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, EdgeWeightProperty> Graph;

/**
 * @brief Class that stores the information related to an instance of the CNP problem
 * 
 */
class CNPInstance
{
protected:
    /**
         *  _graph: Graph which will be studied
         *  _numNodes: Number of nodes that the graph will have
         *  _DensityGraph: Percentage of edge density of the graph
         *  _BCentralityVec: Vector where the BC of each node of the graph will be stored
         *  _AdjMatrix: Adjacency matrix of the nodes of the graph
         *  _vecVertex: Vector de vertices insertados en el grafo
         */
    Graph _graph;
    int _numNodes;
    int _numNodesSol;
    double _densityGraph;
    std::vector<double> _BCentralityVec;
    std::vector<vector<int>> _AdjMatrix;
    std::vector<Graph::vertex_descriptor> _vecVertex;

public:
    /**
         * @brief Construct a new CNPInstance object
         * 
         */
    CNPInstance();
    /**
         * @brief Destroy the CNPInstance object
         * 
         */
    ~CNPInstance();

    /**
         * Read function of an input file
         * @param[in] filename Name of the file where instance data are stored
         */
    void readInstance(char *filename);
    /**
         * @brief Get the Num Nodes of graph
         * 
         * @return int 
         */
    int getNumNodes() const;

    /**
     * @brief Get the Num Nodes Sol object
     * 
     * @return int 
     */
    int getNumNodesSol() const;

    /**
         * @brief Get the Density
         * 
         * @return double 
         */
    double getDensity() const;
    /**
         * @brief Get the Matrix element
         * 
         * @param row 
         * @param col 
         * @return int 
         */
    int getMatrix(int row, int col) const;
    /**
         * @brief Get the BCVector element
         * 
         * @param index 
         * @return double 
         */
    double getBCElement(int index) const;
    /**
         * @brief Set the Num Nodes
         * 
         * @param n 
         */
    void setNumNodes(int n);
    /**
     * @brief Set the Num Nodes Sol object
     * 
     * @param numNodes 
     */
    void setNumNodesSol(int numNodes);

    /**
         * @brief Set the Density 
         * 
         * @param density 
         */
    void setDensity(double density);
    /**
      * @brief Get the Betweenness Centrality object
      * 
      * @return double 
      */
    double getBetweennessCentrality();
    /**
      * @brief Get the Size B C object
      * 
      * @return int 
      */
    int getSizeBC() { return _BCentralityVec.size(); }
    /**
      * @brief Delete a node from graph
      * 
      * @param node 
      */
    void deleteEdge(int node);
    /**
      * @brief print Adyacence Matrix
      * 
      */
     void printAdjMatrix();  
     /**
      * @brief Print vertex conections
      * 
      */
     void PrintConnections();
     /**
     * @brief Get the Num Edges From Node object
     * 
     * @param node 
     * @return int 
     */
     int getNumEdgesFromNode(int node);
    /**
     * @brief Return number of size BC
     * 
     * @return int 
     */
     int getBCNumNodes();
    /**
     * @brief Copy array of BCs
     * 
     * @param instance 
     */
     void copyBCArray(CNPInstance &instance);
    /**
     * @brief Get the Bc Element Index object
     * 
     * @param bc 
     * @return int 
     */
     int getBcElementIndex(double bc);
};

#endif