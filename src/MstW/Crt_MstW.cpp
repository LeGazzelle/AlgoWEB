//
// Created by Gabriele Santi on 25/09/16.
//

#include <queue>
#include "Crt_MstW.hpp"

class Coin {
private:
    static boost::random::mt19937 generator;
    const static boost::random::uniform_int_distribution<> coin = boost::random::uniform_int_distribution<>(0, 1);
    static bool init = false;

public:
    static int flip() {
        if (!init) {
            generator.seed((const uint32_t &) std::time(0));
            init = true;
        }

        return coin(generator);
    }
};

//Default Constructor
MSTWUtilities::MSTWUtilities(void) {
    this->maxWeight = 0;
    this->generator.seed((const uint32_t &) std::time(0));
}

//Constructor with given graph
MSTWUtilities::MSTWUtilities(UndirectedGraph g, int maxWeight) : graph(g), maxWeight(maxWeight) {
    this->generator.seed((const uint32_t &) std::time(0));
}

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
    unsigned long d = approxGraphAvgDegree(eps);

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
    Vertex u;
    double Beta, beta[r];
    std::queue<Vertex> candidates;
    BFS bfs;
    bool flipAgain;
    int flips = 0;
    double threshold = 4 * this->maxWeight;
    threshold /= eps;

    for (i = 0; i < r; i++) {
        candidates.push(random_vertex(this->graph, this->generator));
    }

    i = 0;

    while (!candidates.empty()) {
        u = candidates.front();
        candidates.pop();

        beta[i] = 0.0;
        bfs = new BFS(this->graph, u, avgDeg);
        flipAgain = true;

        while (flipAgain) {
            flips++;
            if (Coin::flip() && bfs.getVisitedVertices() < threshold && bfs.isGreaterThanDstar) {
                bfs.nextStep();

                if (bfs.isCompleted()) {
                    flipAgain = false;
                    if (bfs.getVisitedEdges())
                        beta[i] = (bfs.getUDeg() * pow(2, flips)) / bfs.getVisitedEdges();
                    else
                        beta[i] = 2;
                }
            }
        }
    }

    Beta = 0;
    for (i = 0; i < r; i++) {
        Beta += beta[i];
    }

    return (num_vertices(this->graph) * Beta) / (2 * r);
}

unsigned long MSTWUtilities::approxGraphAvgDegree(double eps) {
    unsigned long maxDegree = 0;
    unsigned long c = computeNumVerticesLemma4(num_vertices(this->graph), eps);
    unsigned int i;
    Vertex v;

    for (i = 0; i < c; i++) {
        v = random_vertex(this->graph, this->generator);

        if (boost::degree(v, this->graph) > maxDegree)
            maxDegree = boost::degree(v, this->graph);
    }

    return maxDegree;
}

unsigned long MSTWUtilities::computeNumVertices(unsigned long n, double eps) {
    double den = eps * eps;
    den += 1 / n;

    return (unsigned long) floor(1 / den);
}

unsigned long MSTWUtilities::computeNumVerticesLemma4(unsigned long n, double eps) {
    double sqrtn = sqrt(n);
    double den = eps + 1 / sqrtn;


    return (unsigned long) floor(sqrtn / den);
}
