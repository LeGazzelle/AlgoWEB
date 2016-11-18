//
// Created by Gabriele Santi on 05/10/16.
//

#include <randomsequence.hpp>
#include "GraphGen.hpp"

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
    //int seed;
    static std::mt19937 generator;
    std::uniform_int_distribution<vertex_index_t> dist;
};

std::mt19937 RandomGenerator::generator;
RandomGenerator *rg = new RandomGenerator();

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
 * @return a random, connected, weighted undirected graph
 */
FastGraph GraphGen::generate(vertex_index_t v, vertex_index_t e, weight_t maxWeight, unsigned int seed) {
    vertex_index_t tree[v], i, j, count;
    EdgeMap *edgeMap = new EdgeMap();
    std::pair<vertex_index_t, bool> vertexFinder;
    FastGraph *g = new FastGraph(v);

    //Initialize random generator
    if (seed)
        rg->init(maxWeight, seed);
    else
        rg->init(maxWeight);

    /*  Generate a random permutation in the array tree. */
    GraphGen::initArray(tree, v);
    GraphGen::permute(tree, v);

    /*  Next generate a random spanning tree.
       The algorithm is:

         Assume that vertices tree[ 0 ],...,tree[ i - 1 ] are in
         the tree.  Add an edge incident on tree[ i ]
         and a random vertex in the set {tree[ 0 ],...,tree[ i - 1 ]}.
    */
    g->addUndirectedEdge(tree[1], tree[0], rg->rand());
    updateEdgesMap(edgeMap, tree[1], tree[0]);


    for (i = 2; i < v; i++) {
        j = rg->rand(i - 1);
        g->addUndirectedEdge(tree[i], tree[j], rg->rand());
        updateEdgesMap(edgeMap, tree[i], tree[j]);
    }

    /* Add additional random edges until achieving at least desired number */

    count = v - 1;

    while (count < e) {
        i = rg->rand(v - 1);
        j = rg->rand(v - 1);

        if (i == j)
            continue;

        /**
         * res is a pair <Edge, bool> where bool is true iff no edge existed
         * between i and j, hence a correct insertion has been performed; false otherwise
         */
        vertexFinder = GraphGen::findTarget(edgeMap, i, j, v);

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
};


/* set a[ i ] = i, for i = 0,...,end - 1 */
void GraphGen::initArray(vertex_index_t *a, vertex_index_t end) {
    vertex_index_t i;

    for (i = 0; i < end; i++)
        *a++ = i;
}


/* randomly permute a[ 0 ],...,a[ n - 1 ] */
void GraphGen::permute(vertex_index_t *a, vertex_index_t n) {
    vertex_index_t i;

    for (i = 0; i < n - 1; i++)
        swap(a + i + rg->rand((n - i - 1)), a + i);
}

void GraphGen::swap(vertex_index_t *a, vertex_index_t *b) {
    vertex_index_t temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

//BfsMatrix GraphGen::edgesMatrixInit(const vertex_index_t n) {
//    BfsMatrix em = *new BfsMatrix(n);
//    vertex_index_t i, j;
//
//    for (i = 0; i < n; i++) { //O(n)
//        em[i].resize(n);
//        //em[i] = {}; seem not to work
//    }
//
//    for (i = 0; i < n; i++) { //O(n^2)
//        for (j = 0; j < n; j++)
//            em[i][j] = false;
//    }
//
//    return em;
//}

EMapIter GraphGen::updateEdgesMap(EdgeMap *em, vertex_index_t u, vertex_index_t v) {
    if (u < v)
        return em->emplace(Edge(u, v), 0);
    else
        return em->emplace(Edge(v, u), 0);
}

std::pair<vertex_index_t, bool>
GraphGen::findTarget(EdgeMap *pMap, vertex_index_t i, vertex_index_t j, vertex_index_t max) {
    if (updateEdgesMap(pMap, i, j).second)
        return std::pair<vertex_index_t, bool>(j, true);
    else {
        vertex_index_t up, down;

        down = i ? i - 1 : max - 1;

        up = (i + 1) % max;

        while (true) {
            if (updateEdgesMap(pMap, i, up).second)
                return std::pair<vertex_index_t, bool>(up, true);
            else if (updateEdgesMap(pMap, i, down).second)
                return std::pair<vertex_index_t, bool>(down, true);
            else {
                up = (up + 1) % max;
                if (up == down)
                    return std::pair<vertex_index_t, bool>(0, false);

                if (down)
                    --down;
                else
                    down = max - 1;

                if (up == down)
                    return std::pair<vertex_index_t, bool>(0, false);
            }
        }
    }
}
