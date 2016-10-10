//
// Created by Gabriele Santi on 25/09/16.
//
#ifndef ALGOWEB_CRT_MSTW_HPP
#define ALGOWEB_CRT_MSTW_HPP

#include <ctime>
#include "../AlgoWEB.hpp"
#include "../BFS/BFS.hpp"
#include <boost/graph/random.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>


class MSTWCompare {
public:
    MSTWCompare(void);

    MSTWCompare(UndirectedGraph g, int maxWeight);

    void setGraph(UndirectedGraph g, int maxWeight);

    double CRTAlgorithm(double eps);

    double KruskalAlgorithm();

    double PrimAlgorithm();

    ~MSTWCompare();

private:
    UndirectedGraph graph;
    int maxWeight;
    //management
    boost::random::mt19937 generator;

    double approxNumConnectedComps(double eps, unsigned long avgDeg, int i);

    unsigned long approxGraphAvgDegree(double eps);

    unsigned long computeNumVertices(unsigned long n, double eps);

    unsigned long computeNumVerticesLemma4(unsigned long n, double eps);
};

#endif //ALGOWEB_CRT_MSTW_HPP
