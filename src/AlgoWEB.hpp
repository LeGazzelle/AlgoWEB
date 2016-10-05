//
// Created by gabriel on 05/10/16.
//

#ifndef ALGOWEB_ALGOWEB_HPP
#define ALGOWEB_ALGOWEB_HPP

#include <iostream>

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

using namespace boost;


typedef property<edge_weight_t, int, no_property> Weight;
typedef adjacency_list<vecS, vecS, undirectedS,
        no_property, Weight> UndirectedGraph;
typedef graph_traits<UndirectedGraph>::vertices_size_type NumVertices;
typedef UndirectedGraph::edge_descriptor Edge;
typedef UndirectedGraph::vertex_descriptor Vertex;
typedef graph_traits<UndirectedGraph>::vertex_iterator VertexIterator;
typedef graph_traits<UndirectedGraph>::edge_iterator EdgeIterator;
typedef graph_traits<UndirectedGraph>::adjacency_iterator NeighboursIterator;

#endif //ALGOWEB_ALGOWEB_HPP
