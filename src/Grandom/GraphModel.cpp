//
// Created by Gabriele Santi on 24/11/16.
//

#include <randomsequence.hpp>
#include <algorithm>
#include "GraphModel.hpp"

class RandomGenerator {
public:
    RandomGenerator() {}

    void init(vertex_index_t max) {
        generator.seed((const uint32_t &) std::time(0));
        this->dist = std::uniform_int_distribution<vertex_index_t>(1, max);
    }

    void init(vertex_index_t max, unsigned int seed) {
        generator.seed(seed);
        this->dist = std::uniform_int_distribution<vertex_index_t>(1, max);
    }

    weight_t rand() {
        return (weight_t) this->dist(generator);
    }

    vertex_index_t rand(vertex_index_t max) {
        std::uniform_int_distribution<vertex_index_t> tmpDist(0, max);
        return tmpDist(generator);
    }

private:
    static std::mt19937 generator;
    std::uniform_int_distribution<vertex_index_t> dist;
};

std::mt19937 RandomGenerator::generator;
RandomGenerator *rg = new RandomGenerator();

GraphModel::GraphModel(vertex_index_t v, vertex_index_t e , weight_t maxWeight) : v(v), e(e), maxWeight(maxWeight) {}

UniformModel::UniformModel(vertex_index_t v, vertex_index_t e, weight_t maxWeight, unsigned int seed) : GraphModel(v, e, maxWeight) {
    this->seed = seed;
}

/**
 * This function generates a random connected simple graph with
 * v vertices and max(v-1,e) edges.  The graph can be weighted
 * (weight_flag == 1) or unweighted (weight_flag != 1). If
 * it is weighted, the weights are in the range 1 to max_wgt.
 * It is assumed that e <= v(v-1)/2.
 *
 * To  generate  a  random  connected  graph,  we begin by
 * generating  a  random  spanning  tree.  To generate a random
 * spanning  tree,  we  first  generate  a  random  permutation
 * tree[0],...,tree[v-1]. (v = number of vertices.)
 * We  then  iteratively  add edges  to form a
 * tree.  We  begin with the tree consisting of vertex tree[0] and
 * no   edges.   At   the   iterative   step,  we  assume  that
 * tree[0],tree[1],...,tree[i-1]  are  in  the  tree.  We  then add vertex
 * tree[i]  to     the    tree    by    adding    the    edge
 * (tree[i],tree[rand(i)]).  (This  construction  is similar to
 * that  of  Prim's algorithm.) Finally, we add random edges to
 * produce the desired number of edges.
 *
 * @param v number of nodes
 * @param e number of edges
 * @param maxWeight max positive integer weight for the edges
 * @param seed an optional argument to set the seed, wich is meant random if not provided
 * @return a random, connected, weighted undirected graph
 */
FastGraph UniformModel::generate() {
    vertex_index_t tree[this->v], i, j, count;
    EdgeMap *edgeMap = new EdgeMap();
    std::pair<vertex_index_t, bool> vertexFinder;
    FastGraph *g = new FastGraph(this->v);

    //Initialize random generator
    if (this->seed)
        rg->init(this->maxWeight, this->seed);
    else
        rg->init(this->maxWeight);

    /*  Generate a random permutation in the array tree. */
    initArray(tree);
    permute(tree);

    /*  Next generate a random spanning tree.
       The algorithm is:

         Assume that vertices tree[ 0 ],...,tree[ i - 1 ] are in
         the tree.  Add an edge incident on tree[ i ]
         and a random vertex in the set {tree[ 0 ],...,tree[ i - 1 ]}.
    */
    g->addUndirectedEdge(tree[1], tree[0], rg->rand());
    updateEdgesMap(edgeMap, tree[1], tree[0]);


    for (i = 2; i < this->v; i++) {
        j = rg->rand(i - 1);
        g->addUndirectedEdge(tree[i], tree[j], rg->rand());
        updateEdgesMap(edgeMap, tree[i], tree[j]);
    }

    /* Add additional random edges until achieving at least desired number */

    count = this->v - 1;

    while (count < this->e) {

        i = rg->rand(this->v - 1);
        j = rg->rand(this->v - 1);


        if (i == j)
            continue;

        /**
         * res is a pair <Edge, bool> where bool is true iff no edge existed
         * between i and j, hence a correct insertion has been performed; false otherwise
         */
        vertexFinder = findTarget(edgeMap, i, j);

        /**
         * since no edge exists between i and j, insert it
         */

        if (vertexFinder.second) {
            g->addUndirectedEdge(i, vertexFinder.first, rg->rand());
            count++;
        }

    }

    delete edgeMap;

    return *g;
}

/* set a[ i ] = i, for i = 0,...,end - 1 */
void UniformModel::initArray(vertex_index_t *tree) {
    vertex_index_t i;

    for (i = 0; i < this->v; i++)
        *tree++ = i;
}

/* randomly permute a[ 0 ],...,a[ n - 1 ] */
void UniformModel::permute(vertex_index_t *tree) {
    vertex_index_t i;

    for (i = 0; i < this->v - 1; i++)
        swap(tree + i + rg->rand((this->v - i - 1)), tree + i);
}

EMapIter UniformModel::updateEdgesMap(EdgeMap *eMap, vertex_index_t u, vertex_index_t v) {
    if (u < v)
        return eMap->emplace(Edge(u, v), 0);
    else
        return eMap->emplace(Edge(v, u), 0);
}

void UniformModel::swap(vertex_index_t *a, vertex_index_t *b) {
    vertex_index_t temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

std::pair<vertex_index_t, bool>
UniformModel::findTarget(EdgeMap *pMap, vertex_index_t i, vertex_index_t j) {
    if (updateEdgesMap(pMap, i, j).second)
        return std::pair<vertex_index_t, bool>(j, true);
    else {
        vertex_index_t up, down;

        down = i ? i - 1 : this->v - 1;

        up = (i + 1) % this->v;

        while (true) {
            if (updateEdgesMap(pMap, i, up).second)
                return std::pair<vertex_index_t, bool>(up, true);
            else if (updateEdgesMap(pMap, i, down).second)
                return std::pair<vertex_index_t, bool>(down, true);
            else {
                up = (up + 1) % this->v;
                if (up == down)
                    return std::pair<vertex_index_t, bool>(0, false);

                if (down)
                    --down;
                else
                    down = this->v - 1;

                if (up == down)
                    return std::pair<vertex_index_t, bool>(0, false);
            }
        }
    }
}

GaussianModel::GaussianModel(vertex_index_t v, vertex_index_t e, weight_t maxWeight, unsigned int seed) : UniformModel(v, e, maxWeight, seed) {}

FastGraph GaussianModel::generate() {
    vertex_index_t tree[this->v], i, j, count, roll;
    EdgeMap *edgeMap = new EdgeMap();
    std::pair<vertex_index_t, bool> vertexFinder;
    FastGraph *g = new FastGraph(this->v);

    //Initialize random generator
    if (this->seed)
        rg->init(this->maxWeight, this->seed);
    else
        rg->init(this->maxWeight);

    /*  Generate a random permutation in the array tree. */
    initArray(tree);
    permute(tree);

    /*  Next generate a random spanning tree.
       The algorithm is:

         Assume that vertices tree[ 0 ],...,tree[ i - 1 ] are in
         the tree.  Add an edge incident on tree[ i ]
         and a random vertex in the set {tree[ 0 ],...,tree[ i - 1 ]}.
    */
    g->addUndirectedEdge(tree[1], tree[0], rg->rand());
    updateEdgesMap(edgeMap, tree[1], tree[0]);


    for (i = 2; i < this->v; i++) {
        j = rg->rand(i - 1);
        g->addUndirectedEdge(tree[i], tree[j], rg->rand());
        updateEdgesMap(edgeMap, tree[i], tree[j]);
    }

    /* Add additional random edges until achieving at least desired number */

    count = this->v - 1;

    while (count < this->e) {
        roll = rg->rand(100);

        if(roll < 60)
            //in the 60% of cases the source will be a node of the first
            //10% of the graph, thus forming a cluster over there
            i = rg->rand(v/10);
        else
            i = rg->rand(this->v - 1);

        j = rg->rand(this->v - 1);


        if (i == j)
            continue;

        /**
         * res is a pair <Edge, bool> where bool is true iff no edge existed
         * between i and j, hence a correct insertion has been performed; false otherwise
         */
        vertexFinder = findTarget(edgeMap, i, j);

        /**
         * since no edge exists between i and j, insert it
         */

        if (vertexFinder.second) {
            g->addUndirectedEdge(i, vertexFinder.first, rg->rand());
            count++;
        }

    }

    delete edgeMap;

    return *g;
}

WattsStrogatzModel::WattsStrogatzModel(vertex_index_t v, vertex_index_t e , weight_t maxWeight, int beta) : GraphModel(v, e, maxWeight) {
    if (beta < 0 || beta > 100) {
        std::cerr << "Beta must be a percentage value (between 0 and 100 included); assuming default value 50."
                  << std::endl;
        this->beta = 50;
    } else
        this->beta = beta;
}

FastGraph WattsStrogatzModel::generate() {
    FastGraph *g = new FastGraph(this->v);
    rg->init(this->maxWeight);
    vertex_index_t i, j, halfAvgDeg = this->e / this->v;
    AdjacencyList *al;

    //create regular ring lattice
    for (i = 0; i < this->v; i++) {
        for (j = 1; j <= halfAvgDeg; j++) {
            g->addUndirectedEdge(i, ((i+j) % this->v), rg->rand());
        }
    }

    //rewire every edge (i,j) with probability beta
    for (i = 0; i < this->v; i++) {
        al = g->adjacentVertices(i);

        for (AdjacencyIterator ai = al->begin(); ai != al->end(); ++ai) {
            if (rg->rand(100) < this->beta) {
                if (!g->rewire(i, ai, rg->rand(this->v - 1)))
                    break;
            }
        }
    }

    return *g;
}

BarabasiAlbertModel::BarabasiAlbertModel(vertex_index_t v, vertex_index_t e, weight_t maxWeight) : GraphModel(v, e, maxWeight) {}

FastGraph BarabasiAlbertModel::generate() {
    FastGraph *g = new FastGraph(this->v);
    rg->init(this->maxWeight);
    vertex_index_t m = this->e / this->v;
    vertex_index_t u, p, v, d;
    vertex_index_t m0 = 2*m;
    std::vector<vertex_index_t> roll = std::vector<vertex_index_t>(m);
    std::vector<vertex_index_t> degreeList = std::vector<vertex_index_t>(this->v);

    //create a complete graph with m0 vertices
    for (u = 0; u < m0; ++u) {
        p = u + 1;

        while (p < m0) {
            g->addUndirectedEdge(u, p, rg->rand());
            ++p;
        }

        degreeList[u] = m0 - 1;
    }

    //until we have reach the total number of nodes...
    for (u = m0; u < this->v; ++u) {

        for (p = 0; p < m; ++p)
            roll[p] = rg->rand((2 * g->numEdges()) - 1);
        std::sort(roll.begin(), roll.end());

        d = degreeList[0];
        p = 0;
        for (v = 0; v < u && p < m; ++v) {
            while (roll[p] < d) {
                g->addUndirectedEdge(u, v, rg->rand());
                degreeList[v]++;
                p++;
            }

            d += degreeList[v+1];

        }

        degreeList[u] = m;
    }

    return *g;
}
