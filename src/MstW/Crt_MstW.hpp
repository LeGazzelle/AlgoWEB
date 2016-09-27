//
// Created by Gabriele Santi on 25/09/16.
//
#ifndef ALGOWEB_CRT_MSTW_HPP
#define ALGOWEB_CRT_MSTW_HPP

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

typedef property< edge_weight_t, double > Weight;
typedef adjacency_list < vecS, vecS, undirectedS,
no_property, Weight > UndirectedGraph;

#endif //ALGOWEB_CRT_MSTW_HPP
