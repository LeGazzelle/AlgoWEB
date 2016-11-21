//
// Created by Gabriele Santi on 25/09/16.
//

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
    //this->g_i = *new FastSubGraph(10); //FIXME c'è da risolvere il fatto che il costruttore vorrebbe il numero di vertici a priori (vedi sopra)
    std::cout << "Preparing the data structures for the run..." << std::endl;
    std::cout.flush();
    ProgressAnimations progressAnimations = ProgressAnimations();
    vertex_index_t total = this->graph.numEdges(), i = 0;

    this->num_vert_G = g.numVertices();
    //prepare needed structure
    //this->subgraphs = CRTsubgraphs(this->num_vert_G);
    //this->fys = std::vector<FisherYatesSequence>(this->num_vert_G + 1);
    //prim
    this->primOrderedEdges = std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, WeightedEdgeComparator>();

    EdgeList *edgeList = this->graph.edges();
    EdgeIterator ei, ei_end;
    ei_end = edgeList->end();
    std::cout << "Ordering edges...\n" << std::flush;
    for (ei = edgeList->begin(); ei != ei_end; ++ei) {
        this->crtOrderedEdges.push(*ei);
        ++i;
        if (!(i % 150)) //avoids to process too much output to std cout
            progressAnimations.printProgBar((unsigned) std::ceil(100.0 * i / total));
    }
    std::cout << std::endl;
    std::cout.flush();
    //extractSubGraphs();

    std::cout << "Creating Fisher-Yates sequences..." << std::flush;
    this->fys = new FisherYatesSequence(this->num_vert_G);
    std::cout << "DONE" << std::flush;
//    for (vertex_index_t h = 1; h <= this->num_vert_G; ++h) {
//        if (!(h % 100))
//            progressAnimations.printProgBar((unsigned) std::ceil(100.0 * h / this->num_vert_G));
//        this->fys[h] = FisherYatesSequence(h);
//    }

    std::cout << "\n\n";
}

//Destructor
MSTWCompare::~MSTWCompare() {}

/**
 * This method is to be called compulsory prior to a MSTWCompare::LightCRTAlgorithm
 * call. It prepares the data structures needed for a light run. Only for test purposes.
 *
 * @return the time elapsed for the operation
 */
//long double MSTWCompare::prepareLightRun() {
//    clock_t start, end;
//    weight_t k;
//    vertex_index_t h;
//
//    start = clock();
//    this->copyOfOrderedEdges = std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, WeightedEdgeComparator>(
//            this->crtOrderedEdges);
//
//    this->subgraphs.push_back(FastSubGraph(vertex_index_t(0))); //we discard position '0'
//    for (k = 1; k <= this->maxWeight; ++k) {
//        this->subgraphs.push_back(*new FastSubGraph(this->lightExtractGraph((k))));
//    }
//    //end = clock();
//
//    //restore internal data structure for subsequent calls
//    //this->g_i;
//
//    this->fys.push_back(FisherYatesSequence(1)); //again discard position '0'
//    for (h = 1; h <= this->num_vert_G; ++h) {
//        this->fys.push_back(*new FisherYatesSequence(h));
//    }
//    end = clock();
//
//    return double(end - start);
//}

/**
 * The base algorithm developed by Chazelle, Rubinfeld and Trevisan
 * for the approximation of the MST weitght in sublinear time.
 * This version uses pre-computed data structures, for test purposes.
 *
 * @param eps the maximum tolerated relative error
 * @return the approximation of the weight of the MST of the given graph
 */
//double MSTWCompare::LightCRTAlgorithm(double eps) {
//    if (this->maxWeight == 0)
//        return -1.0;
//
//    double c = 0.0;
//    unsigned long d = lightApproxGraphAvgDegree(eps); //O(1/eps)
//
//    for (weight_t i = 1; i < this->maxWeight; ++i) { //O(w)
//        c += lightApproxNumConnectedComps(eps, d, i);
//    }
//
//    return this->num_vert_G - this->maxWeight + c;
//}

/**
 * The base algorithm developed by Chazelle, Rubinfeld and Trevisan
 * for the approximation of the MST weitght in sublinear time.
 *
 * @param eps the maximum tolerated relative error
 * @return the approximation of the weight of the MST of the given graph
 */
CRTresult MSTWCompare::CRTAlgorithm(double eps) {
    CRTresult res;
    clock_t start, end;
    double c = 0.0;

    start = clock();
    vertex_index_t d = approxGraphAvgDegree(eps);
    end = clock();

    res.time = end - start;

    for (weight_t i = 1; i < this->maxWeight; ++i) {
        this->extractSubGraph(i);
        this->fys = new FisherYatesSequence(this->g_i.numVertices());
        start = clock();
        c += approxNumConnectedComps(eps, d, i);
        end = clock();
        delete this->fys;
        res.time += (end - start);
    }

    res.res = this->num_vert_G - this->maxWeight + c;
    res.time /= CLOCKS_PER_SEC;

    return res;
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
    //this->extractGraph(i);
    vertex_index_t n_i = this->g_i.numVertices();

    if (!n_i)
        return 0.0;

    //FisherYatesSequence *fys = new FisherYatesSequence(n_i);
    vertex_index_t j, r = (vertex_index_t) std::floor(
            (std::sqrt(n_i / i) * eps - 1) / std::pow(eps, 2)); //computeNumVertices(n_i, eps);
    Vertex u;
    double Beta = 0.0;
    BFS *bfs;
    bool flipAgain;
    int flips;
    double threshold = 4 * this->maxWeight;
    threshold /= eps;

    for (j = 0; j < r; ++j) {
        u = this->fys->next();
        flips = 0;

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
                        Beta += (bfs->getUDeg() * std::pow(2, flips - 1)) /
                                bfs->getVisitedEdges(); //there's an implicit division by 2
                    else
                        Beta += 1; //remember we pre-divide by 2
                }
            }
        }

        delete bfs;
    }

    //delete fys;

    return (n_i * Beta) / r;
}

//TODO check that hypothesis for theorem 6 are met
vertex_index_t MSTWCompare::approxGraphAvgDegree(double eps) {
    vertex_index_t i, deg, maxDegree = 0;
    vertex_index_t c = (vertex_index_t) std::floor(
            (std::sqrt(this->num_vert_G) * eps - 1) / eps); //computeNumVerticesLemma4(this->num_vert_G, eps);
    //FisherYatesSequence *fys = new FisherYatesSequence(this->num_vert_G);
    Vertex v;

    for (i = 0; i < c; ++i) {
        v = this->fys->next();

        if ((deg = this->graph.degree(v)) > maxDegree)
            maxDegree = deg;
    }

    //delete fys;
    return maxDegree;
}

//double MSTWCompare::lightApproxNumConnectedComps(double eps, vertex_index_t avgDeg, weight_t i) {
//    //this->extractGraph(i);
//    unsigned long n_i = this->subgraphs[i].numVertices();
//
//    if (!n_i)
//        return 0.0;
//
//    //RandomVertexExtractor *rve = new RandomVertexExtractor(n_i);
//    //rve->prepare();
//    unsigned long j, r = computeNumVertices(n_i, eps); //O(1/eps^2)
//    Vertex u;
//    double Beta = 0.0;
//    BFS *bfs;
//    bool flipAgain;
//    int flips;
//    double threshold = 4 * this->maxWeight;
//    threshold /= eps;
//
//    for (j = 0; j < r; ++j) {
//        u = this->fys[n_i].next(); //O(1)
//        flips = 0;
//
//        bfs = new BFS(this->subgraphs[i], u, avgDeg); //O(n^2) ???
//        bfs->firstStep();
//        flipAgain = true;
//
//        while (flipAgain) {
//            flips++;
//            flipAgain = Coin::flip() && bfs->getVisitedVertices() < threshold && !bfs->isGreaterThanDstar();
//            if (flipAgain) {
//                bfs->nextStep();
//
//                if (bfs->isCompleted()) {
//                    flipAgain = false;
//                    if (bfs->getVisitedEdges())
//                        Beta += (bfs->getUDeg() * std::pow(2, flips - 1)) / bfs->getVisitedEdges();
//                    else
//                        Beta += 2;
//                }
//            }
//        }
//
//        delete bfs;
//    }
//
//
//    return (this->num_vert_G * Beta) / r;
//}
//
//vertex_index_t MSTWCompare::lightApproxGraphAvgDegree(double eps) {
//    vertex_index_t i, deg, maxDegree = 0;
//    unsigned long c = computeNumVerticesLemma4(this->num_vert_G, eps);
//    Vertex v;
//
//    for (i = 0; i < c; ++i) {
//        v = this->fys[this->num_vert_G].next(); // O(1)
//        deg = this->graph.degree(v);
//
//        if (deg > maxDegree)
//            maxDegree = deg;
//    }
//
//    return maxDegree;
//}

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
void MSTWCompare::extractSubGraph(weight_t i) {
    WeightedEdge minimum = this->crtOrderedEdges.top();

    if (minimum.weight <= i) {
        do {
            this->g_i.addUndirectedEdge(minimum.source, minimum.target, minimum.weight);
            this->crtOrderedEdges.pop();
            minimum = this->crtOrderedEdges.top();
        } while (minimum.weight <= i && !this->crtOrderedEdges.empty());
    }
}

/**
 * Extract the subgraph of G containing edges of weight
 * AT MOST i, light version
 *
 * @param i
 * @return the subgraph
 */
//FastSubGraph MSTWCompare::lightExtractGraph(weight_t i) {
//    WeightedEdge minimum = this->copyOfOrderedEdges.top();
//
//    if (minimum.weight <= i) {
//        do {
//            this->g_i.addUndirectedEdge(minimum.source, minimum.target, minimum.weight);
//            this->copyOfOrderedEdges.pop();
//            minimum = this->copyOfOrderedEdges.top();
//        } while (minimum.weight <= i && !this->copyOfOrderedEdges.empty());
//    }
//
//    return this->g_i;
//}

double MSTWCompare::KruskalAlgorithm() {
    EdgeList edges = EdgeList(*this->graph.edges());
    double mst_wt = 0.0; // Initialize result

    // Sort edges in increasing order on basis of cost
    edges.sort([](const WeightedEdge &lhs, const WeightedEdge &rhs) { return lhs.weight > rhs.weight; });

    // Create disjoint sets
    DisjointSets ds(this->graph.numVertices());

    // Iterate through all sorted edges
    EdgeIterator ei, ei_end = edges.end();

    for (ei = edges.begin(); ei != ei_end; ei++) {
        Vertex u = ei->source;
        Vertex v = ei->target;

        vertex_index_t set_u = ds.find(u);
        vertex_index_t set_v = ds.find(v);

        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v) {
            // Current edge will be in the MST
            // Update MST weight
            mst_wt += ei->weight;

            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }

    return mst_wt;

}

double MSTWCompare::PrimAlgorithm() {
    vertex_index_t newVertex, current = getRandomVertex(this->num_vert_G - 1);
    this->visited = StatefulVertices(this->num_vert_G);
    WeightedEdge minimum;
    vertex_index_t i = 0;
    FastGraph mst = FastGraph(this->num_vert_G);
    AdjacencyList *al;
    AdjacencyIterator ai, ai_end;
    EdgeList *el;
    EdgeIterator ei, ei_end;
    double ans = 0.0;

    while (i < this->num_vert_G) {
        if (!visited[current]) {            // If current node is not visited
            visited[current] = true;        // Mark it visited

            al = this->graph.adjacentVertices(current);
            ai_end = al->end();

            for (ai = al->begin(); ai != ai_end; ++ai) {
                if (!visited[ai->second]) {
                    // If the edge leads to an un-visited
                    // vertex only then enqueue it
                    this->primOrderedEdges.push(WeightedEdge(current, ai->second, ai->first));
                }
            }

            minimum = this->primOrderedEdges.top();     // The greedy choice
            this->primOrderedEdges.pop();

            newVertex = minimum.target;
            current = minimum.source;

            if (!visited[newVertex]) {
                mst.addUndirectedEdge(current, newVertex, minimum.weight);
            }

            current = newVertex;
            ++i;
        } else {

            minimum = this->primOrderedEdges.top();
            this->primOrderedEdges.pop();

            newVertex = minimum.target;
            current = minimum.source;

            if (!visited[newVertex]) {
                mst.addUndirectedEdge(current, newVertex, minimum.weight);
            }

            current = newVertex;
        }
    }

    el = mst.edges();
    ei_end = el->end();

    for (ei = el->begin(); ei != ei_end; ++ei)
        ans += ei->weight;

    return ans;
}

vertex_index_t MSTWCompare::getRandomVertex(vertex_index_t max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<vertex_index_t> dis(0, max);

    return dis(gen);
}

//void MSTWCompare::extractSubGraphs() {
//    WeightedEdge minimum;
//    ProgressAnimations progressAnimations = ProgressAnimations();
//
//    std::cout << "Extracting graphs...\n" << std::flush;
//
//    //initialization
//    this->subgraphs[1] = FastSubGraph(this->num_vert_G);
//    minimum = this->crtOrderedEdges.top();
//
//    if (minimum.weight <= 1) {
//        do {
//            this->subgraphs[1].addUndirectedEdge(minimum.source, minimum.target, minimum.weight);
//            this->crtOrderedEdges.pop();
//            minimum = this->crtOrderedEdges.top();
//        } while (minimum.weight <= 1 && !this->crtOrderedEdges.empty());
//    }
//
//
//    //population
//    for (weight_t i = 2; i <= this->maxWeight; i++) {
//        progressAnimations.printProgBar((unsigned int) std::ceil(100.0 * i / this->maxWeight));
//
//        minimum = this->crtOrderedEdges.top();
//        this->subgraphs[i] = FastSubGraph(this->subgraphs[i-1]);
//
//        if (minimum.weight <= i) {
//            do {
//                this->subgraphs[i].addUndirectedEdge(minimum.source, minimum.target, minimum.weight);
//                this->crtOrderedEdges.pop();
//                minimum = this->crtOrderedEdges.top();
//            } while (minimum.weight <= i && !this->crtOrderedEdges.empty());
//        }
//    }
//
//    std::cout << std::endl;
//
//    //conclusion
//    //this->subgraphs[this->maxWeight] = (FastSubGraph) this->graph;
//
//}

DisjointSets::DisjointSets(vertex_index_t n) {
    // Allocate memory
    this->n = n;
    parent = new vertex_index_t[n + 1];
    rnk = new vertex_index_t[n + 1];

    // Initially, all vertices are in
    // different sets and have rank 0.
    for (vertex_index_t i = 0; i <= n; i++) {
        rnk[i] = 0;

        //every element is parent of itself
        parent[i] = i;
    }
}

vertex_index_t DisjointSets::find(vertex_index_t u) {
    /* Make the parent of the nodes in the path
       from u--> parent[u] point to parent[u] */
    if (u != parent[u])
        parent[u] = find(parent[u]);
    return parent[u];
}

void DisjointSets::merge(vertex_index_t x, vertex_index_t y) {
    x = find(x), y = find(y);

    /* Make tree with smaller height
       a subtree of the other tree  */
    if (rnk[x] > rnk[y])
        parent[y] = x;
    else // If rnk[x] <= rnk[y]
        parent[x] = y;

    if (rnk[x] == rnk[y])
        rnk[y]++;
}
