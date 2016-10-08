//
// Created by Gabriele Santi on 25/09/16.
//

#include <queue>
#include "Crt_MstW.hpp"

//Default Constructor
MSTWUtilities::MSTWUtilities(void) {
    this->maxWeight = 0;
}

//Constructor with given graph
MSTWUtilities::MSTWUtilities(UndirectedGraph g, int maxWeight) : graph(g), maxWeight(maxWeight) {}

//Destructor
MSTWUtilities::~MSTWUtilities() {}

/**
 * Set the graph the utilities will work on
 *
 * @param g undirected graph
 */
void MSTWUtilities::setGraph(UndirectedGraph g, int maxWeight) {
    this->graph = g;
    this->maxWeight = maxWeight;
}

/**
 * The base algorithm developed by Chazelle, Rubinfeld and Trevisan
 * for the approximation of the MST weitght in sublinear time.
 *
 * @param eps the maximum tolerated relative error
 * @return the approximation of the weight of the MST of the given graph
 */
double MSTWUtilities::CRTAlgorithm(double eps) {
    if (this->maxWeight == 0)
        return -1.0;

    NumVertices n = num_vertices(this->graph);
    double c = 0.0;
    double d = approxGraphAvgDegree();

    for (int i = 1; i < this->maxWeight; i++) {
        c += approxNumConnectedComps(eps, d);
    }

    return n - this->maxWeight + c;
}

/**
 * Private
 */

double MSTWUtilities::approxNumConnectedComps(double eps, double avgDeg) {
    unsigned long i, r = computeNumVertices(num_vertices(this->graph), eps);
    std::queue<Vertex> candidates;

    for (i = 0; i < r; i++) {
        //candidates.push();
    }

    return 1.0;
}

double MSTWUtilities::approxGraphAvgDegree() {
    //TODO con lemma 4
    return 2.0;
}

unsigned long MSTWUtilities::computeNumVertices(unsigned long n, double eps) {
    double den = eps * eps;
    den += 1 / n;

    return (unsigned long) floor(1 / den);
}
