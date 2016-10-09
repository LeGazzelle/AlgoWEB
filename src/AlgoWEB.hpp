//
// Created by gabriel on 05/10/16.
//

#ifndef ALGOWEB_ALGOWEB_HPP
#define ALGOWEB_ALGOWEB_HPP

#include <iostream>

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

using namespace boost;

static bool __VERB;


typedef property<edge_weight_t, int, no_property> Weight;
typedef property<disallow_parallel_edge_tag, no_property> noMultigraph;
typedef adjacency_list<setS, vecS, undirectedS,
        no_property, Weight, noMultigraph> UndirectedGraph;

typedef graph_traits<UndirectedGraph>::vertices_size_type NumVertices;
typedef UndirectedGraph::edge_descriptor Edge;
typedef UndirectedGraph::vertex_descriptor Vertex;
typedef graph_traits<UndirectedGraph>::vertex_iterator VertexIterator;
typedef graph_traits<UndirectedGraph>::edge_iterator EdgeIterator;
typedef graph_traits<UndirectedGraph>::adjacency_iterator NeighboursIterator;
typedef property_map<UndirectedGraph, edge_weight_t>::type WeightMap;
typedef property_map<UndirectedGraph, vertex_index_t>::type VertexMap;
typedef std::vector<std::vector<bool>> EdgesMatrix;

#endif //ALGOWEB_ALGOWEB_HPP
