//
// Created by Gabriele Santi on 25/09/16.
//

#include "Crt_MstW.hpp"

class MSTWUtilities {
public:
    MSTWUtilities(void);
    MSTWUtilities(UndirectedGraph g);
    void setGraph(UndirectedGraph g);
    double CRTAlgorithm(double eps);
    ~MSTWUtilities();

private:
    UndirectedGraph graph;

    double approxNumConnectedComps(double eps, int avgDeg);
    double approxGraphAvgDegree();
};


//Default Constructor
MSTWUtilities::MSTWUtilities(void) {
    this->graph = nullptr;
}

//Constructor with given graph
MSTWUtilities::MSTWUtilities(UndirectedGraph g) : graph(g) {}

//Destructor
MSTWUtilities::~MSTWUtilities() {
    ~(this->graph);
}

/**
 * Set the graph the utilities will work on
 *
 * @param g undirected graph
 */
void MSTWUtilities::setGraph(UndirectedGraph g)  {
    ~(this->graph);
    this->graph = g;
}

/**
 * The base algorithm developed by Chazelle, Rubinfeld and Trevisan
 * for the approximation of the MST weitght in sublinear time.
 *
 * @param eps the maximum tolerated relative error
 * @return the approximation of the weight of the MST of the given graph
 */
double MSTWUtilities::CRTAlgorithm(double eps) {
    //TODO corpo base dell'algoritmo
    return 0.0;
}

/**
 * Private
 */

double MSTWUtilities::approxNumConnectedComps(double eps, int avgDeg) {
    //TODO
}

double MSTWUtilities::approxGraphAvgDegree() {
    //TODO con lemma 4
}