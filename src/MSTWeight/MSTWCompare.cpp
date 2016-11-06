//
// Created by Gabriele Santi on 25/09/16.
//

#include <queue>
#include "MSTWCompare.hpp"

class Coin {
private:
    static std::mt19937 generator;
    static std::uniform_int_distribution<> coin;

public:
    static int flip() {
        static bool init = false;

        if (!init) {
            coin = std::uniform_int_distribution<>(0, 1);
            generator.seed((const uint32_t &) std::time(0));
            init = true;
        }

        return coin(generator);
    }
};

std::mt19937 Coin::generator;
std::uniform_int_distribution<> Coin::coin;

//Constructor with given graph
MSTWCompare::MSTWCompare(FastGraph g, weight_t maxWeight) : graph(g), maxWeight(maxWeight), g_i(g.numVertices()) {
    this->generator.seed((const uint32_t &) std::time(0));
    //this->g_i = *new FastSubGraph(10); //FIXME c'è da risolvere il fatto che il costruttore vorrebbe il numero di vertici a priori (vedi sopra)
    this->num_vert_G = g.numVertices();
    //this->vc.init(num_vert_G);
    //WeightMap weights = get(edge_weight, this->graph);
    //light runs
    this->subgraphs = *new std::vector<FastSubGraph>;
    this->fys = *new std::vector<FisherYatesSequence>;

    EdgeList edgeList = this->graph.edges();
    EdgeIterator ei;
    for (ei = edgeList.begin(); ei != edgeList.end(); ++ei)
        this->orderedEdges.push(*ei);
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
long double MSTWCompare::prepareLightRun() {
    clock_t start, end;
    weight_t k;
    vertex_index_t h;

    start = clock();
    this->copyOfOrderedEdges = std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, WeightedEdgeComparator>(
            this->orderedEdges);

    this->subgraphs.push_back(FastSubGraph(vertex_index_t(0))); //we discard position '0'
    for (k = 1; k <= this->maxWeight; k++) {
        this->subgraphs.push_back(*new FastSubGraph(this->lightExtractGraph((k))));
    }
    //end = clock();

    //restore internal data structure for subsequent calls
    //this->g_i;

    this->fys.push_back(FisherYatesSequence(1)); //again discard position '0'
    for (h = 1; h <= this->num_vert_G; h++) {
        this->fys.push_back(*new FisherYatesSequence(h));
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
    unsigned long d = lightApproxGraphAvgDegree(eps); //O(1/eps)

    for (weight_t i = 1; i < this->maxWeight; i++) { //O(w)
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

    for (weight_t i = 1; i < this->maxWeight; i++) {
        c += approxNumConnectedComps(eps, d, i);
    }

    return this->num_vert_G - this->maxWeight + c;
}

long double MSTWCompare::getAverageDegree() {
    if (this->num_vert_G == 1)
        return 0.0;

    vertex_index_t vi = 0ULL;
    long double degreeAvg = this->graph.degree(vi);
    vi++;

    while (vi != this->num_vert_G) {
        degreeAvg = (degreeAvg + this->graph.degree(vi)) / 2.0;
        vi++;
    }

    return degreeAvg;
}

/**
 * Private
 */

long double MSTWCompare::approxNumConnectedComps(double eps, vertex_index_t avgDeg, weight_t i) {
    this->extractGraph(i);
    unsigned long n_i = this->g_i.numVertices();

    if (!n_i)
        return 0.0;

    FisherYatesSequence *fys = new FisherYatesSequence((long long int) n_i);
    vertex_index_t j, r = computeNumVertices(n_i, eps);
    Vertex u;
    double Beta = 0.0;
    BFS *bfs;
    bool flipAgain;
    int flips;
    double threshold = 4 * this->maxWeight;
    threshold /= eps;

    for (j = 0; j < r; j++) {
        u = fys->next();
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

//TODO check that hypothesis for theorem 6 are met
vertex_index_t MSTWCompare::approxGraphAvgDegree(double eps) {
    vertex_index_t i, deg, maxDegree = 0;
    vertex_index_t c = computeNumVerticesLemma4(this->num_vert_G, eps);
    FisherYatesSequence *fys = new FisherYatesSequence(this->num_vert_G);
    Vertex v;

    for (i = 0; i < c; i++) {
        v = fys->next();

        if ((deg = this->graph.degree(v)) > maxDegree)
            maxDegree = deg;
    }

    delete fys;
    return maxDegree;
}

double MSTWCompare::lightApproxNumConnectedComps(double eps, vertex_index_t avgDeg, weight_t i) {
    //this->extractGraph(i);
    unsigned long n_i = this->subgraphs[i].numVertices();

    if (!n_i)
        return 0.0;

    //RandomVertexExtractor *rve = new RandomVertexExtractor(n_i);
    //rve->prepare();
    unsigned long j, r = computeNumVertices(n_i, eps); //O(1/eps^2)
    Vertex u;
    double Beta = 0.0;
    BFS *bfs;
    bool flipAgain;
    int flips;
    double threshold = 4 * this->maxWeight;
    threshold /= eps;

    for (j = 0; j < r; j++) {
        u = this->fys[n_i].next(); //O(1)
        flips = 0;

        bfs = new BFS(this->subgraphs[i], u, avgDeg); //O(n^2) ???
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

vertex_index_t MSTWCompare::lightApproxGraphAvgDegree(double eps) {
    vertex_index_t i, deg, maxDegree = 0;
    unsigned long c = computeNumVerticesLemma4(this->num_vert_G, eps);
    Vertex v;

    for (i = 0; i < c; i++) {
        v = this->fys[this->num_vert_G].next(); // O(1)
        deg = this->graph.degree(v);

        if (deg > maxDegree)
            maxDegree = deg;
    }

    return maxDegree;
}

vertex_index_t MSTWCompare::computeNumVertices(vertex_index_t n, double eps) {
    unsigned long y;
    double den = eps * eps;
    den = 1 + n * den;
    y = (unsigned long) std::floor(n / den);

    return y == 0 ? 1 : y;
}

vertex_index_t MSTWCompare::computeNumVerticesLemma4(vertex_index_t n, double eps) {
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
void MSTWCompare::extractGraph(weight_t i) {
    WeightedEdge minimum = this->orderedEdges.top();

    if (minimum.weight <= i) {
        do {
            this->g_i.addEdge(minimum.source, minimum.target, minimum.weight);
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
FastSubGraph MSTWCompare::lightExtractGraph(weight_t i) {
    WeightedEdge minimum = this->copyOfOrderedEdges.top();

    if (minimum.weight <= i) {
        do {
            this->g_i.addEdge(minimum.source, minimum.target, minimum.weight);
            this->copyOfOrderedEdges.pop();
            minimum = this->copyOfOrderedEdges.top();
        } while (minimum.weight <= i && !this->copyOfOrderedEdges.empty());
    }

    //DEBUG
    std::cout << "g_" << i << ":" << std::endl;
    this->g_i.printByAdjList();
    std::cout << "-------------------------------------------------------------------------------------\n";

    return this->g_i;
}

double MSTWCompare::KruskalAlgorithm() {
    //TODO

    return -1.0;
}

double MSTWCompare::PrimAlgorithm() {
    //TODO

    return -1.0;
}