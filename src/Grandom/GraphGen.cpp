//
// Created by Gabriele Santi on 05/10/16.
//

#include "GraphGen.hpp"

class RandomGenerator {
public:
    RandomGenerator() {}

    void init(int max) {
        generator.seed((const uint32_t &) std::time(0));
        this->dist = boost::random::uniform_int_distribution<>(1, max);
    }

    void init(int max, unsigned int seed) {
        generator.seed(seed);
        this->dist = boost::random::uniform_int_distribution<>(1, max);
    }

    int rand() {
        return this->dist(generator);
    }

    int rand(int max) {
        boost::random::uniform_int_distribution<> tmpDist(0, max);
        return tmpDist(generator);
    }

private:
    //int seed;
    static boost::random::mt19937 generator;
    boost::random::uniform_int_distribution<> dist;
};

boost::random::mt19937 RandomGenerator::generator;
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
 * @param maxWeight max integer weight for the edges
 * @return a random, connected, weighted undirected graph
 */
UndirectedGraph GraphGen::generate(unsigned long v, unsigned long e, unsigned int maxWeight, unsigned int seed) {
    unsigned long tree[v], i, j, count;
    Result res;

    //Initialize random generator
    if (seed)
        rg->init(maxWeight, seed);
    else
        rg->init(maxWeight);

    UndirectedGraph *g = new UndirectedGraph(v);

    /*  Generate a random permutation in the array tree. */
    GraphGen::initArray(tree, v);
    GraphGen::permute(tree, v);

    /*  Next generate a random spanning tree.
       The algorithm is:

         Assume that vertices tree[ 0 ],...,tree[ i - 1 ] are in
         the tree.  Add an edge incident on tree[ i ]
         and a random vertex in the set {tree[ 0 ],...,tree[ i - 1 ]}.
    */
    add_edge(vertex(tree[1], *g), vertex(tree[0], *g), EdgeWeight(AUTO_INDEX, rg->rand()), *g);

    for (i = 2; i < v; i++) {
        j = (unsigned long) rg->rand((int) i - 1);
        add_edge(vertex(tree[i], *g), vertex(tree[j], *g), EdgeWeight(AUTO_INDEX, rg->rand()), *g);
    }

    /* Add additional random edges until achieving at least desired number */

    count = v - 1;

    while (count < e) {
        i = (unsigned long) rg->rand((int) v - 1);
        j = (unsigned long) rg->rand((int) v - 1);

        if (i == j)
            continue;

        /**
         * res is a pair <Edge, bool> where bool is true iff no edge existed
         * between i and j, hence a correct insertion has been performed; false otherwise
         */
        res = add_edge(vertex(i, *g), vertex(j, *g), EdgeWeight(AUTO_INDEX, rg->rand()), *g);

        if (res.second)
            count++;

    }


    return *g;
};


/* set a[ i ] = i, for i = 0,...,end - 1 */
void GraphGen::initArray(unsigned long *a, unsigned long end) {
    unsigned long i;

    for (i = 0; i < end; i++)
        *a++ = i;
}


/* randomly permute a[ 0 ],...,a[ n - 1 ] */
void GraphGen::permute(unsigned long *a, unsigned long n) {
    unsigned long i;

    for (i = 0; i < n - 1; i++)
        swap(a + i + rg->rand((int) (n - i - 1)), a + i);
}

void GraphGen::swap(unsigned long *a, unsigned long *b) {
    unsigned long temp;

    temp = *a;
    *a = *b;
    *b = temp;
}