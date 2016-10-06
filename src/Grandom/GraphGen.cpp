//
// Created by Gabriele Santi on 05/10/16.
//

#include "GraphGen.hpp"

class RandomGenerator {
public:
    RandomGenerator() {}

    void init(int max) {
        //FIXME debug uncomment below (default seed)
        //generator.seed((const uint32_t &) std::time(0));
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
 * It is assumed that e <= v(v-1)/2. (In this program, this assured
 * because of the call to fix_imbalanced_graph.)
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
UndirectedGraph GraphGen::generate(unsigned long v, unsigned long e, int maxWeight) {
    unsigned long tree[v], i, j, count;
    Result res;

    //Initialize random generator
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
    add_edge(vertex(tree[1], *g), vertex(tree[0], *g), Weight(rg->rand()), *g);

    for (i = 2; i < v; i++) {
        j = (unsigned long) rg->rand((int) i - 1);
        add_edge(vertex(tree[i], *g), vertex(tree[j], *g), Weight(rg->rand()), *g);
    }

    /* Add additional random edges until achieving at least desired number */

    count = v - 1;

    while (count < e) {
        i = (unsigned long) rg->rand((int) v - 1);
        j = (unsigned long) rg->rand((int) v - 1);

        if (i == j)
            continue;

//        if (i > j)
//            swap(&i, &j);

        /**
         * res is a pair <Edge, bool> where bool is true iff no edge existed
         * between i and j, hence a correct insertion has been performed; false otherwise
         */
        res = add_edge(vertex(i, *g), vertex(j, *g), Weight(rg->rand()), *g);

        if (res.second)
            count++;

    }


    return *g;
};


//void random_connected_graph(int v,
//                            int e,
//                            int max_wgt,
//                            int weight_flag,
//                            char *out_file) {
//    int i, j, count, index, *adj_matrix, *tree;
//
//    if ((adj_matrix = (int *) calloc(v * v, sizeof(int)))
//        == NULL) {
//        printf("Not enough room for this size graph\n");
//        return;
//    }
//
//    if ((tree = (int *) calloc(v, sizeof(int))) == NULL) {
//        printf("Not enough room for this size graph\n");
//        free(adj_matrix);
//        return;
//    }
//
//    printf("\n\tBeginning construction of graph.\n");
//
//    /*  Generate a random permutation in the array tree. */
//    init_array(tree, v);
//    permute(tree, v);
//
//    /*  Next generate a random spanning tree.
//        The algorithm is:
//
//          Assume that vertices tree[ 0 ],...,tree[ i - 1 ] are in
//          the tree.  Add an edge incident on tree[ i ]
//          and a random vertex in the set {tree[ 0 ],...,tree[ i - 1 ]}.
//     */
//
//    for (i = 1; i < v; i++) {
//        j = ran(i);
//        adj_matrix[tree[i] * v + tree[j]] =
//        adj_matrix[tree[j] * v + tree[i]] =
//                weight_flag ? 1 + ran(max_wgt) : 1;
//    }
//
//    /* Add additional random edges until achieving at least desired number */
//
//    for (count = v - 1; count < e;) {
//        i = ran(v);
//        j = ran(v);
//
//        if (i == j)
//            continue;
//
//        if (i > j)
//            swap(&i, &j);
//
//        index = i * v + j;
//        if (!adj_matrix[index]) {
//            adj_matrix[index] = weight_flag ? 1 + ran(max_wgt) : 1;
//            count++;
//        }
//    }
//
//    print_graph(v, count, out_file, adj_matrix, Undirected);
//
//    free(tree);
//    free(adj_matrix);
//}


/* set a[ i ] = i, for i = 0,...,end - 1 */
void GraphGen::initArray(unsigned long *a, unsigned long end) {
    unsigned long i;

    for (i = 0; i < end; i++)
        *a++ = i;
}


/* randomly permute a[ 0 ],...,a[ n - 1 ] */
void GraphGen::permute(unsigned long *a, unsigned long n) {
    unsigned long i;
    //size_t ul_size = sizeof(unsigned long);

    for (i = 0; i < n - 1; i++)
        swap(a + i + rg->rand((int) (n - i - 1)), a + i);
}

void GraphGen::swap(unsigned long *a, unsigned long *b) {
    unsigned long temp;

    temp = *a;
    *a = *b;
    *b = temp;
}