//
// Created by Gabriele Santi on 25/09/16.
//
#ifndef ALGOWEB_CRT_MSTW_HPP
#define ALGOWEB_CRT_MSTW_HPP

#include <algorithm>
#include <ctime>

#include "../utilities/randomsequence.hpp"
#include "../BFS/BFS.hpp"
#include "../Graphs/FastGraphs.hpp"
#include "../Graphs/VertexConverter.hpp"

class MSTWCompare {
public:
    MSTWCompare(FastGraph g, weight_t maxWeight);

    double CRTAlgorithm(double eps);

    long double prepareLightRun();

    double LightCRTAlgorithm(double eps);

    double KruskalAlgorithm();

    double PrimAlgorithm();

    long double getAverageDegree();

    ~MSTWCompare();

private:
    FastGraph graph;
    weight_t maxWeight;
    //management
    std::mt19937 generator;
    FastSubGraph g_i;
    vertex_index_t num_vert_G;
    std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, WeightedEdgeComparator> orderedEdges;
    //VertexConverter vc;
    //management for light runs
    std::vector<FastSubGraph> subgraphs;
    std::vector<FisherYatesSequence> fys;
    std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, WeightedEdgeComparator> copyOfOrderedEdges;

    long double approxNumConnectedComps(double eps, vertex_index_t avgDeg, weight_t i);

    vertex_index_t approxGraphAvgDegree(double eps);

    double lightApproxNumConnectedComps(double eps, vertex_index_t avgDeg, weight_t i);

    vertex_index_t lightApproxGraphAvgDegree(double eps);

    vertex_index_t computeNumVertices(vertex_index_t n, double eps);

    vertex_index_t computeNumVerticesLemma4(vertex_index_t n, double eps);

    void extractGraph(weight_t i);

    FastSubGraph lightExtractGraph(weight_t i);
};

#endif //ALGOWEB_CRT_MSTW_HPP
