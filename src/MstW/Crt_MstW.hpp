//
// Created by Gabriele Santi on 25/09/16.
//
#ifndef ALGOWEB_CRT_MSTW_HPP
#define ALGOWEB_CRT_MSTW_HPP

#include "../AlgoWEB.hpp"
#include "../BFS/BFS.hpp"
#include "boost/graph/random.hpp"

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
    //management
    boost::random::mt19937 generator;

    double approxNumConnectedComps(double eps, unsigned long avgDeg);

    unsigned long approxGraphAvgDegree(double eps);

    unsigned long computeNumVertices(unsigned long n, double eps);

    unsigned long computeNumVerticesLemma4(unsigned long n, double eps);
};

#endif //ALGOWEB_CRT_MSTW_HPP
