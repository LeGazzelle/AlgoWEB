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


VertexConverter::VertexConverter() {}

void VertexConverter::init(unsigned long dim) {
    //this->next = 0;
    this->vertices = new long long[dim];

    for (long long i = 0LL; i < dim; i++)
        this->vertices[i] = NULL_VERTEX;
}

long long VertexConverter::getVertexIndex(long long globalIndex) {
    if (this->vertices[globalIndex] < 0LL)
        this->vertices[globalIndex] = this->next++;

    return vertices[globalIndex];
}


RandomVertexExtractor::RandomVertexExtractor() {}

void RandomVertexExtractor::init(unsigned long dim) {
    this->vindexes = new Vertex[dim];
    this->size = dim;

    for (long long i = 0; i < dim; i++)
        this->vindexes[i] = (Vertex) i;
}

Vertex RandomVertexExtractor::extractRandomVertex() {
    return *std::rotate(this->vindexes, this->vindexes+1, this->vindexes+this->size);
}

void RandomVertexExtractor::prepare() {
    this->scramble();
}

void RandomVertexExtractor::scramble() {
    std::random_shuffle(this->vindexes, this->vindexes+this->size);
}

//Default Constructor
//MSTWCompare::MSTWCompare(void) {
//    this->maxWeight = 0;
//    this->generator.seed((const uint32_t &) std::time(0));
//}

//Constructor with given graph
MSTWCompare::MSTWCompare(UndirectedGraph g, int maxWeight) : graph(g), maxWeight(maxWeight) {
    this->generator.seed((const uint32_t &) std::time(0));
    this->g_i = *new UndirectedGraph();
    this->vc.init(num_vertices(g));
    this->rve.init(num_vertices(g));
    WeightMap weights = get(edge_weight, this->graph);

    EdgeIterator ei, eiend;
    for (boost::tie(ei, eiend) = edges(this->graph); ei != eiend; ++ei)
        this->orderedEdges.push(WeightedEdge(source(*ei, this->graph), target(*ei, this->graph), weights[*ei]));
}

//Destructor
MSTWCompare::~MSTWCompare() {}

/**
 * Set the graph the utilities will work on
 *
 * @param g undirected graph
 */
//void MSTWCompare::setGraph(UndirectedGraph g, int maxWeight) {
//    this->graph = g;
//    this->maxWeight = maxWeight;
//}

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
    this->extractGraph(i);
    this->rve.prepare();

    if (!num_vertices(this->g_i))
        return 0.0;

    unsigned long j, r = computeNumVertices(num_vertices(this->g_i), eps);
    Vertex u;
    double Beta = 0.0;
    //std::queue<Vertex> candidates;
    //Vertex candidate;
    BFS *bfs;
    bool flipAgain;
    int flips = 0;
    double threshold = 4 * this->maxWeight;
    threshold /= eps;

//    for (j = 0; j < r; j++) {
//        candidates.push(random_vertex(this->g_i, this->generator));
//    }


//    while (!candidates.empty()) {
    for (j = 0; j < r; j++) {
//        u = candidates.front();
//        candidates.pop();
        u = this->rve.extractRandomVertex();

        bfs = new BFS(this->g_i, u, avgDeg);
        bfs->firstStep();
        flipAgain = true;

        while (flipAgain) {
            flips++;
            flipAgain = Coin::flip() && bfs->getVisitedVertices() < threshold && !bfs->isGreaterThanDstar();
            if (flipAgain) {
                bfs->nextStep();

                if (bfs->isCompleted()) {
                    flipAgain = false;
                    if (bfs->getVisitedEdges())
                        Beta += (bfs->getUDeg() * std::pow(2, flips)) / bfs->getVisitedEdges();
                    else
                        Beta += 2;
                }
            }
        }

        delete bfs;
    }

//    for (j = 0; j < r; j++) {
//        Beta += beta[j];
//    }

    return (num_vertices(this->graph) * Beta) / (2 * r);
}

//std::queue<Vertex> MSTWCompare::getRandomCandidates() {
//
//}

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
    unsigned long y;
    double den = eps * eps;
    den += 1 / n;
    y = (unsigned long) std::floor(1 / den);

    return y == 0 ? 1 : y;
}

unsigned long MSTWCompare::computeNumVerticesLemma4(unsigned long n, double eps) {
    unsigned long y;

    double sqrtn = std::sqrt(n);
    double den = eps + 1 / sqrtn;
    y = (unsigned long) std::floor(sqrtn / den);

    return y == 0 ? 1 : y;
}

//bool MSTWCompare::compareEdge(Edge a, Edge b) {
//    return boost::get(edge_weight_t(), this->graph, a) < boost::get(edge_weight_t(), this->graph, b);
//}

void MSTWCompare::extractGraph(int i) {
    WeightedEdge minimum = this->orderedEdges.top();

    if (minimum.weight <= i) {
        do {
            add_edge(vertex(this->vc.getVertexIndex(minimum.source), this->g_i),
                     vertex(this->vc.getVertexIndex(minimum.target), this->g_i), this->g_i);
            this->orderedEdges.pop();
            minimum = this->orderedEdges.top();
        } while (minimum.weight <= i && !this->orderedEdges.empty());
    }
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

//DEBUG
//UndirectedGraph MSTWCompare::computeG_i(int i) {
//    this->extractGraph(i);
//
//    return this->g_i;
//}