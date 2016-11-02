//
// Created by Gabriele Santi on 25/09/16.
//

#include <queue>
#include "MSTWCompare.hpp"

class Coin {
private:
    static boost::random::mt19937 generator;
    static boost::random::uniform_int_distribution<> coin;

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
    this->vertices = new long long[dim];

    for (long long i = 0LL; i < dim; i++)
        this->vertices[i] = NULL_VERTEX;
}

long long VertexConverter::getVertexIndex(long long globalIndex) {
    if (this->vertices[globalIndex] < 0LL)
        this->vertices[globalIndex] = this->next++;

    return vertices[globalIndex];
}
//TODO EFFICENTARE IL RANDOM VERTEX EXTRACTOR CON GLI ARTICOLI TROVATI IN RETE SU GENERAZIONE O(1)

RandomVertexExtractor::RandomVertexExtractor(unsigned long dim) {
    this->vindexes = new Vertex[dim];
    this->size = dim;

    for (long long i = 0; i < dim; i++)
        this->vindexes[i] = (Vertex) i;
}

Vertex RandomVertexExtractor::extractRandomVertex() {
    return *std::rotate(this->vindexes, this->vindexes + 1, this->vindexes + this->size);
}

void RandomVertexExtractor::prepare() {
    this->scramble();
}

void RandomVertexExtractor::scramble() {
    std::random_shuffle(this->vindexes, this->vindexes + this->size);
}

//Constructor with given graph
MSTWCompare::MSTWCompare(UndirectedGraph g, int maxWeight) : graph(g), maxWeight(maxWeight) {
    this->generator.seed((const uint32_t &) std::time(0));
    this->g_i = *new UndirectedGraph();
    this->num_vert_G = num_vertices(g);
    this->vc.init(num_vert_G);
    WeightMap weights = get(edge_weight, this->graph);
    //light runs
    this->subgraphs = *new std::vector<UndirectedGraph>;
    this->fys = *new std::vector<FisherYatesSequence>;

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
 * This method is to be called compulsory prior to a MSTWCompare::LightCRTAlgorithm
 * call. It prepares the data structures needed for a light run. Only for test purposes.
 *
 * @return the time elapsed for the operation
 */
double MSTWCompare::prepareLightRun() {
    clock_t start, end;
    long long k;

    start = clock();
    this->copyOfOrderedEdges = std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, WeightedEdgeComparator>(
            this->orderedEdges);

    this->subgraphs.push_back(UndirectedGraph()); //we discard position '0'
    for (k = 1; k <= this->maxWeight; k++) {
        this->subgraphs.push_back(*new UndirectedGraph(this->lightExtractGraph((int) k)));
    }
    //end = clock();

    //restore internal data structure for subsequent calls
    this->g_i.clear();

    this->fys.push_back(FisherYatesSequence(1)); //again discard position '0'
    for (k = 1; k <= this->num_vert_G; k++) {
        this->fys.push_back(*new FisherYatesSequence(k));
    }
    end = clock(); //TODO we could differentiate the two phases

    return double(end - start);
}

/**
 * The base algorithm developed by Chazelle, Rubinfeld and Trevisan
 * for the approximation of the MST weitght in sublinear time.
 * This version uses pre-computed data structures, for test purposes.
 *
 * @param eps the maximum tolerated relative error
 * @return the approximation of the weight of the MST of the given graph
 */
double MSTWCompare::LightCRTAlgorithm(double eps) {
    if (this->maxWeight == 0)
        return -1.0;

    double c = 0.0;
    unsigned long d = lightApproxGraphAvgDegree(eps);

    for (int i = 1; i < this->maxWeight; i++) {
        c += lightApproxNumConnectedComps(eps, d, i);
    }

    return this->num_vert_G - this->maxWeight + c;
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

    double c = 0.0;
    unsigned long d = approxGraphAvgDegree(eps);

    for (int i = 1; i < this->maxWeight; i++) {
        c += approxNumConnectedComps(eps, d, i);
    }

    return this->num_vert_G - this->maxWeight + c;
}

long double MSTWCompare::getAverageDegree() {
    if (this->num_vert_G == 1)
        return 0.0;

    VertexIterator vi, vi_end;
    boost::tie(vi, vi_end) = vertices(this->graph);
    long double degreeAvg = degree(*vi, this->graph);
    vi++;

    while (vi != vi_end) {
        degreeAvg = (degreeAvg + degree(*vi, this->graph)) / 2.0;
        vi++;
    }

    return degreeAvg;
}

/**
 * Private
 */

double MSTWCompare::approxNumConnectedComps(double eps, unsigned long avgDeg, int i) {
    this->extractGraph(i);
    unsigned long n_i = num_vertices(this->g_i);

    if (!n_i)
        return 0.0;

    RandomVertexExtractor *rve = new RandomVertexExtractor(n_i);
    rve->prepare();
    unsigned long j, r = computeNumVertices(n_i, eps);
    Vertex u;
    double Beta = 0.0;
    BFS *bfs;
    bool flipAgain;
    int flips;
    double threshold = 4 * this->maxWeight;
    threshold /= eps;

    for (j = 0; j < r; j++) {
        u = rve->extractRandomVertex();
        flips = 0;

        bfs = new BFS(this->g_i, u, avgDeg);
        bfs->firstStep();
        flipAgain = true;

        while (flipAgain) {
            flips++;
            flipAgain = Coin::flip() && bfs->getVisitedVertices() < threshold && !bfs->isGreaterThanDstar();
            if (flipAgain) {
                bfs->nextStep(0);

                if (bfs->isCompleted()) {
                    flipAgain = false;
                    if (bfs->getVisitedEdges())
                        Beta += (bfs->getUDeg() * std::pow(2, flips-1)) / bfs->getVisitedEdges();
                    else
                        Beta += 2;
                }
            }
        }

        delete bfs;
    }


    return (this->num_vert_G * Beta) / r;
}

unsigned long MSTWCompare::approxGraphAvgDegree(double eps) {
    unsigned long maxDegree = 0;
    unsigned long c = computeNumVerticesLemma4(this->num_vert_G, eps);
    RandomVertexExtractor *rve = new RandomVertexExtractor(this->num_vert_G); //mischia tutti i nodi per darne solo una parte... inefficiente
    rve->prepare();
    unsigned int i;
    Vertex v;

    for (i = 0; i < c; i++) {
        v = rve->extractRandomVertex();

        if (boost::degree(v, this->graph) > maxDegree)
            maxDegree = boost::degree(v, this->graph);
    }

    return maxDegree;
}

double MSTWCompare::lightApproxNumConnectedComps(double eps, unsigned long avgDeg, int i) {
    //this->extractGraph(i);
    unsigned long n_i = num_vertices(this->subgraphs[i]);

    if (!n_i)
        return 0.0;

    //RandomVertexExtractor *rve = new RandomVertexExtractor(n_i);
    //rve->prepare();
    unsigned long j, r = computeNumVertices(n_i, eps);
    Vertex u;
    double Beta = 0.0;
    BFS *bfs;
    bool flipAgain;
    int flips;
    double threshold = 4 * this->maxWeight;
    threshold /= eps;

    for (j = 0; j < r; j++) {
        u = this->fys[n_i].next();
        flips = 0;

        bfs = new BFS(this->subgraphs[i], u, avgDeg);
        bfs->firstStep();
        flipAgain = true;

        while (flipAgain) {
            flips++;
            flipAgain = Coin::flip() && bfs->getVisitedVertices() < threshold && !bfs->isGreaterThanDstar();
            if (flipAgain) {
                bfs->nextStep(0);

                if (bfs->isCompleted()) {
                    flipAgain = false;
                    if (bfs->getVisitedEdges())
                        Beta += (bfs->getUDeg() * std::pow(2, flips - 1)) / bfs->getVisitedEdges();
                    else
                        Beta += 2;
                }
            }
        }

        delete bfs;
    }


    return (this->num_vert_G * Beta) / r;
}

unsigned long MSTWCompare::lightApproxGraphAvgDegree(double eps) {
    unsigned long maxDegree = 0;
    unsigned long c = computeNumVerticesLemma4(this->num_vert_G, eps);
    //RandomVertexExtractor *rve = new RandomVertexExtractor(this->num_vert_G); //mischia tutti i nodi per darne solo una parte... inefficiente
    //rve->prepare();
    unsigned int i;
    Vertex v;

    for (i = 0; i < c; i++) {
        v = this->fys[this->num_vert_G].next();

        if (boost::degree(v, this->graph) > maxDegree)
            maxDegree = boost::degree(v, this->graph);
    }

    return maxDegree;
}

unsigned long MSTWCompare::computeNumVertices(unsigned long n, double eps) {
    unsigned long y;
    double den = eps * eps;
    den = 1 + n*den;
    y = (unsigned long) std::floor(n / den);

    return y == 0 ? 1 : y;
}

unsigned long MSTWCompare::computeNumVerticesLemma4(unsigned long n, double eps) {
    unsigned long y;

    double sqrtn = std::sqrt(n);
    double den = eps + 1 / sqrtn;
    y = (unsigned long) std::floor(sqrtn / den);

    return y == 0 ? 1 : y;
}

/**
 * Extract the subgraph of G containing edges of weight
 * AT MOST i
 *
 * @param i
 */
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

/**
 * Extract the subgraph of G containing edges of weight
 * AT MOST i, light version
 *
 * @param i
 * @return the subgraph
 */
UndirectedGraph MSTWCompare::lightExtractGraph(int i) {
    WeightedEdge minimum = this->copyOfOrderedEdges.top();

    if (minimum.weight <= i) {
        do {
            add_edge(vertex(this->vc.getVertexIndex(minimum.source), this->g_i),
                     vertex(this->vc.getVertexIndex(minimum.target), this->g_i), this->g_i);
            this->copyOfOrderedEdges.pop();
            minimum = this->copyOfOrderedEdges.top();
        } while (minimum.weight <= i && !this->copyOfOrderedEdges.empty());
    }

    return this->g_i;
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
    std::vector<Vertex> spanning_tree(this->num_vert_G);
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