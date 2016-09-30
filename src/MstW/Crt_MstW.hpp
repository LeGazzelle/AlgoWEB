//
// Created by Gabriele Santi on 25/09/16.
//
#ifndef ALGOWEB_CRT_MSTW_HPP
#define ALGOWEB_CRT_MSTW_HPP

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;


typedef property<edge_weight_t, int, no_property> Weight;
typedef adjacency_list < vecS, vecS, undirectedS,
no_property, Weight > UndirectedGraph;
typedef graph_traits<UndirectedGraph>::vertices_size_type NumVertices;
typedef UndirectedGraph::edge_descriptor Edge;
typedef UndirectedGraph::vertex_descriptor Vertex;

class MSTWUtilities {
public:
    MSTWUtilities(void);

    MSTWUtilities(UndirectedGraph g, int maxWeight);

    void setGraph(UndirectedGraph g, int maxWeight);

    double CRTAlgorithm(double eps);

    ~MSTWUtilities();

private:
    UndirectedGraph graph;
    int maxWeight;

    double approxNumConnectedComps(double eps, int avgDeg);

    double approxGraphAvgDegree();
};

#endif //ALGOWEB_CRT_MSTW_HPP
