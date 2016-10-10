//
// Created by Gabriele Santi on 25/09/16.
//

#include <queue>
#include "MSTWCompare.hpp"

class Coin {
private:
    static boost::random::mt19937 generator;
    static boost::random::uniform_int_distribution<> coin;// = boost::random::uniform_int_distribution<>(0, 1);
    //static bool init = false;

public:
    static int flip() {
        static bool init = false;

        if (!init) {
            coin = boost::random::uniform_int_distribution<>(0, 1);
            generator.seed((const uint32_t &) std::time(0));
            init = true;
        }

        return coin(generator);
    }
};

boost::random::mt19937 Coin::generator;
boost::random::uniform_int_distribution<> Coin::coin;

//Default Constructor
MSTWCompare::MSTWCompare(void) {
    this->maxWeight = 0;
    this->generator.seed((const uint32_t &) std::time(0));
}

//Constructor with given graph
MSTWCompare::MSTWCompare(UndirectedGraph g, int maxWeight) : graph(g), maxWeight(maxWeight) {
    this->generator.seed((const uint32_t &) std::time(0));
}

//Destructor
MSTWCompare::~MSTWCompare() {}

/**
 * Set the graph the utilities will work on
 *
 * @param g undirected graph
 */
void MSTWCompare::setGraph(UndirectedGraph g, int maxWeight) {
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
double MSTWCompare::CRTAlgorithm(double eps) {
    if (this->maxWeight == 0)
        return -1.0;

    NumVertices n = num_vertices(this->graph);
    double c = 0.0;
    unsigned long d = approxGraphAvgDegree(eps);

    for (int i = 1; i < this->maxWeight; i++) {
        c += approxNumConnectedComps(eps, d, i);
    }

    return n - this->maxWeight + c;
}

/**
 * Private
 */

double MSTWCompare::approxNumConnectedComps(double eps, unsigned long avgDeg, int i) {
    unsigned long j, r = computeNumVertices(num_vertices(this->graph), eps);
    Vertex u;
    double Beta, beta[r];
    std::queue<Vertex> candidates;
    BFS *bfs;
    bool flipAgain;
    int flips = 0;
    double threshold = 4 * this->maxWeight;
    threshold /= eps;

    for (j = 0; j < r; j++) {
        candidates.push(random_vertex(this->graph, this->generator));
    }

    j = 0;

    while (!candidates.empty()) {
        u = candidates.front();
        candidates.pop();

        beta[j] = 0.0;
        bfs = new BFS(this->graph, u, avgDeg);
        bfs->setI(i);
        bfs->firstStep();
        flipAgain = true;

        while (flipAgain) {
            flips++;
            if (Coin::flip() && bfs->getVisitedVertices() < threshold && bfs->isGreaterThanDstar()) {
                bfs->nextStep();

                if (bfs->isCompleted()) {
                    flipAgain = false;
                    if (bfs->getVisitedEdges())
                        beta[j] = (bfs->getUDeg() * std::pow(2, flips)) / bfs->getVisitedEdges();
                    else
                        beta[j] = 2;
                }
            }
        }
    }

    Beta = 0;
    for (j = 0; j < r; j++) {
        Beta += beta[j];
    }

    return (num_vertices(this->graph) * Beta) / (2 * r);
}

unsigned long MSTWCompare::approxGraphAvgDegree(double eps) {
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

unsigned long MSTWCompare::computeNumVertices(unsigned long n, double eps) {
    double den = eps * eps;
    den += 1 / n;

    return (unsigned long) std::floor(1 / den);
}

unsigned long MSTWCompare::computeNumVerticesLemma4(unsigned long n, double eps) {
    double sqrtn = std::sqrt(n);
    double den = eps + 1 / sqrtn;


    return (unsigned long) std::floor(sqrtn / den);
}

double MSTWCompare::KruskalAlgorithm() {
    std::vector<Edge> spanning_tree;
    WeightMap weight = get(edge_weight, this->graph);
    double MSTWeight = 0.0;

    kruskal_minimum_spanning_tree(this->graph, std::back_inserter(spanning_tree));

    for (std::vector<Edge>::iterator ei = spanning_tree.begin(); ei != spanning_tree.end(); ++ei) {
        MSTWeight += weight[*ei];
    }

    return MSTWeight;
}

double MSTWCompare::PrimAlgorithm() {
    std::vector<Vertex> spanning_tree(num_vertices(this->graph));
    WeightMap weight = get(edge_weight, this->graph);
    double MSTWeight = 0.0;

    prim_minimum_spanning_tree(this->graph, &spanning_tree[0]);

    for (Vertex vi = 0; vi != spanning_tree.size(); ++vi) {
        if (spanning_tree[vi] != vi) {
            MSTWeight += weight[edge(vi, spanning_tree[vi], this->graph).first];
        }
    }

    return MSTWeight;
}