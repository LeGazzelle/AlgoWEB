//
// Created by Gabriele Santi on 25/09/16.
//
#ifndef ALGOWEB_CRT_MSTW_HPP
#define ALGOWEB_CRT_MSTW_HPP

#include <ctime>
#include <algorithm>

#include "../AlgoWEB.hpp"
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
    RandomVertexExtractor ();
    void init (unsigned long dim);
    Vertex extractRandomVertex();
    void prepare();
};

class MSTWCompare {
public:
    MSTWCompare(UndirectedGraph g, int maxWeight);

    double CRTAlgorithm(double eps);

    double KruskalAlgorithm();

    double PrimAlgorithm();

    ~MSTWCompare();

    //DEBUG
    //UndirectedGraph computeG_i(int i);

private:
    UndirectedGraph graph;
    int maxWeight;
    //management
    boost::random::mt19937 generator;
    UndirectedGraph g_i;
    std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, WeightedEdgeComparator> orderedEdges;
    VertexConverter vc;
    RandomVertexExtractor rve;

    double approxNumConnectedComps(double eps, unsigned long avgDeg, int i);

    unsigned long approxGraphAvgDegree(double eps);

    unsigned long computeNumVertices(unsigned long n, double eps);

    unsigned long computeNumVerticesLemma4(unsigned long n, double eps);

    void extractGraph(int i);

    //std::queue<Vertex> getRandomCandidates();
};

#endif //ALGOWEB_CRT_MSTW_HPP
