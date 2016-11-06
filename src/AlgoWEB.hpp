//
// Created by Gabriele Santi on 05/10/16.
//

#ifndef ALGOWEB_ALGOWEB_HPP
#define ALGOWEB_ALGOWEB_HPP

#include <list>
#include <vector>
//#include <tuple>
#include <queue>

typedef unsigned long long Vertex;
typedef unsigned long long vertex_index_t;
typedef unsigned int Weight;
typedef unsigned int weight_t;
//typedef std::pair<unsigned long, unsigned long> Edge;
//using Edge = std::tuple<unsigned long, int, unsigned long>;
typedef std::pair<weight_t, vertex_index_t> AdjacentItem;
typedef std::list<AdjacentItem> AdjacencyList;
typedef std::list<AdjacentItem>::iterator AdjacencyIterator;
enum bfs_vertex_state_t {
    UNEXPLORED, QUEUED, EXPLORED
};
union bfs_matrix_t {
    bool edgeState;
    bfs_vertex_state_t vertexState;
};
typedef std::vector<std::vector<bfs_matrix_t>> BfsMatrix;

#endif //ALGOWEB_ALGOWEB_HPP


//
//#include <iostream>
//#include <ctime>
//
//#include <boost/config.hpp>
//#include <boost/graph/adjacency_list.hpp>
//#include <boost/graph/graph_traits.hpp>
//#include <boost/graph/subgraph.hpp>
//#include <boost/random/mersenne_twister.hpp>
//#include <boost/random/uniform_int_distribution.hpp>
//
//using namespace boost;
//
//static bool __VERB;
//
//
//
//typedef property<edge_weight_t, int, no_property> Weight;
////typedef property<edge_index_t, unsigned long, Weight> EdgeWeight;
//typedef property<disallow_parallel_edge_tag, no_property> noMultigraph;
////typedef subgraph<adjacency_list<setS, vecS, undirectedS,
////        property<vertex_index_t, unsigned long>, EdgeWeight, noMultigraph> > UndirectedGraph;
//typedef adjacency_list<setS, vecS, undirectedS,
//        property<vertex_index_t, long long>, Weight, noMultigraph> UndirectedGraph;
//
//typedef graph_traits<UndirectedGraph>::vertices_size_type NumVertices;
//typedef UndirectedGraph::vertex_descriptor Vertex;
//typedef UndirectedGraph::edge_descriptor Edge;
//typedef graph_traits<UndirectedGraph>::edge_iterator EdgeIterator;
//typedef graph_traits<UndirectedGraph>::vertex_iterator VertexIterator;
//typedef graph_traits<UndirectedGraph>::adjacency_iterator NeighboursIterator;
//typedef property_map<UndirectedGraph, edge_weight_t>::type WeightMap;
//typedef property_map<UndirectedGraph, edge_weight_t>::const_type ConstWeightMap;
//typedef property_map<UndirectedGraph, vertex_index_t>::type VertexMap;
//typedef std::vector<std::vector<bool>> BfsMatrix;
//
////DEBUG
//template<typename UndirectedGraph>
//void print_adjacent_vertex(const UndirectedGraph g) {
//    ConstWeightMap weight = get(edge_weight, g);
//    std::cout << "Graph Print: (between parentesis the weights on the edges)" << std::endl;
//    for (std::pair<VertexIterator, VertexIterator> vertices = boost::vertices(g);
//         vertices.first != vertices.second; ++vertices.first) {
//        std::cout << *vertices.first << " is connected with ";
//        for (std::pair<NeighboursIterator, NeighboursIterator> neighbour = adjacent_vertices(*vertices.first, g);
//             neighbour.first != neighbour.second; ++neighbour.first) {
//            std::pair<Edge, bool> res = edge(*vertices.first, *neighbour.first, g);
//            std::cout << *neighbour.first << "(" << get(weight, res.first) << ") ";
//        }
//        std::cout << std::endl;
//    }
//    std::cout << "#vertices: " << num_vertices(g) << ", #edges: " << num_edges(g) << std::endl;
//}
//

