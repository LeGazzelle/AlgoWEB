//
// Created by Gabriele Santi on 25/09/16.
//
#ifndef ALGOWEB_CRT_MSTW_HPP
#define ALGOWEB_CRT_MSTW_HPP

#include "../AlgoWEB.hpp"

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

    double approxNumConnectedComps(double eps, double avgDeg);

    double approxGraphAvgDegree();

    unsigned long computeNumVertices(unsigned long n, double eps);
};

#endif //ALGOWEB_CRT_MSTW_HPP
