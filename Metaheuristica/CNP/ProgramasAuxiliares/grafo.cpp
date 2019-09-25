#include <boost/graph/betweenness_centrality.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <boost/graph/connected_components.hpp>
using namespace std;
using namespace boost;
typedef boost::property<boost::edge_weight_t, float> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, EdgeWeightProperty> Graph;


int main(int argc, char** argv){
    if(argc < 2) return 0;
    int _numNodes;
    double _densityGraph;
    ifstream file(argv[1]);
    vector<Graph::vertex_descriptor> _vecVertex;
    if (!file.good())
    {
        std::cout << "Error: File " << argv[1] << " not found or with errors" << std::endl;
        exit(-1);
    }
    Graph g;
    EdgeWeightProperty weight = 1; //Edge Weight = 1
    file >> _numNodes;
    file >> _densityGraph;
    
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
                
            }
        }
    }
    file.close();
    int nodo = 0;
    while(nodo >= 0){
        cout<<"Inserta nodo para borrar, inserta un numero menor que cero para finalizar"<<endl;
        cin>>nodo;
        if(nodo >= 0) clear_vertex(nodo, g);
    }

    typedef boost::property_map<Graph, boost::vertex_index_t>::type VertexIndexMap;
    VertexIndexMap v_index = get(boost::vertex_index, g);
    std::vector<double> v_centrality_vec(boost::num_vertices(g), 0.0);
    boost::iterator_property_map<std::vector<double>::iterator, VertexIndexMap>
        v_centrality_map(v_centrality_vec.begin(), get(boost::vertex_index, g));
    brandes_betweenness_centrality(g, v_centrality_map);

    double sumBC = 0;
    for (int i=0;i<v_centrality_vec.size();i++)
    {
        sumBC += v_centrality_vec.at(i);
       // cout << v_centrality_vec.at(i)<<" - ";
    }
    cout << endl<<"SUMA BC: "<<sumBC<<endl;
    /*   Graph::vertex_iterator vertexIt, vertexEnd;
        Graph::adjacency_iterator neighbourIt, neighbourEnd;
        tie(vertexIt, vertexEnd) = vertices(g);
        for (; vertexIt != vertexEnd; ++vertexIt)
        {
            cout << *vertexIt << " esta conectado con ";
            tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, g);
            for (; neighbourIt != neighbourEnd; ++neighbourIt)
                cout << *neighbourIt << " ";
            cout << "\n";
        }
        */
}