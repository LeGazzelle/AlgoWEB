//
// Created by Gabriele Santi on 25/09/16.
//
#ifndef ALGOWEB_CRT_MSTW_HPP
#define ALGOWEB_CRT_MSTW_HPP

#include <algorithm>

#include "../AlgoWEB.hpp"
#include "../utilities/randomsequence.hpp"
#include "../BFS/BFS.hpp"
#include "WeightedEdge.hpp"
#include <boost/graph/random.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

class VertexConverter {
private:
    long long next;
    long long *vertices;

public:
    VertexConverter();

    void init(unsigned long dim);

    long long getVertexIndex(long long globalIndex);
};

class RandomVertexExtractor {
private:
    Vertex *vindexes;
    unsigned long size;

    void scramble();

public:
    RandomVertexExtractor(unsigned long dim);

    Vertex extractRandomVertex();

    void prepare();
};

class MSTWCompare {
public:
    MSTWCompare(UndirectedGraph g, int maxWeight);

    double CRTAlgorithm(double eps);

    double prepareLightRun();

    double LightCRTAlgorithm(double eps);

    double KruskalAlgorithm();

    double PrimAlgorithm();

    long double getAverageDegree();

    ~MSTWCompare();

private:
    UndirectedGraph graph;
    int maxWeight;
    //management
    boost::random::mt19937 generator;
    UndirectedGraph g_i;
    NumVertices num_vert_G;
    std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, WeightedEdgeComparator> orderedEdges;
    VertexConverter vc;
    //management for light runs
    std::vector<UndirectedGraph> subgraphs;
    std::vector<FisherYatesSequence> fys;
    std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, WeightedEdgeComparator> copyOfOrderedEdges;

    double approxNumConnectedComps(double eps, unsigned long avgDeg, int i);

    unsigned long approxGraphAvgDegree(double eps);

    double lightApproxNumConnectedComps(double eps, unsigned long avgDeg, int i);

    unsigned long lightApproxGraphAvgDegree(double eps);

    unsigned long computeNumVertices(unsigned long n, double eps);

    unsigned long computeNumVerticesLemma4(unsigned long n, double eps);

    void extractGraph(int i);

    UndirectedGraph lightExtractGraph(int i);
};

#endif //ALGOWEB_CRT_MSTW_HPP
