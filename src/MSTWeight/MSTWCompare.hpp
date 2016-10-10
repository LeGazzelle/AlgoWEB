//
// Created by Gabriele Santi on 25/09/16.
//
#ifndef ALGOWEB_CRT_MSTW_HPP
#define ALGOWEB_CRT_MSTW_HPP

#include <ctime>
#include "../AlgoWEB.hpp"
#include "../BFS/BFS.hpp"
#include "WeightedEdge.hpp"
#include <boost/graph/random.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>




class MSTWCompare {
public:
    //MSTWCompare(void);

    MSTWCompare(UndirectedGraph g, int maxWeight);

    //void setGraph(UndirectedGraph g, int maxWeight);

    double CRTAlgorithm(double eps);

    double KruskalAlgorithm();

    double PrimAlgorithm();

    ~MSTWCompare();

private:
    UndirectedGraph graph;
    int maxWeight;
    //management
    boost::random::mt19937 generator;
    UndirectedGraph g_i;
    //bool compareEdge(Edge a, Edge b);
    std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, WeightedEdgeComparator> orderedEdges;
    //std::priority_queue<Edge, std::vector<Edge>, decltype(&MSTWCompare::compareEdge)> orderedEdges;

    double approxNumConnectedComps(double eps, unsigned long avgDeg, int i);

    unsigned long approxGraphAvgDegree(double eps);

    unsigned long computeNumVertices(unsigned long n, double eps);

    unsigned long computeNumVerticesLemma4(unsigned long n, double eps);

    void extractGraph(int i);
};

#endif //ALGOWEB_CRT_MSTW_HPP
