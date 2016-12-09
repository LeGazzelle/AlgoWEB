//
// Created by Gabriele Santi on 05/10/16.
//

#include "GraphGen.hpp"

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
 * @param arg optional argument; for Uniform and Gaussian model is the seed of the random generator, for the Small World
 * the probability of rewiring
 * @return a random, connected, weighted undirected graph
 */
FastGraph GraphGen::generate(vertex_index_t v, vertex_index_t e, weight_t maxWeight, unsigned int arg, LawType law) {
    if (law == UNIFORM) {
        UniformModel uniformModel(v, e, maxWeight, arg);
        return uniformModel.generate();
    } else if (law == GAUSSIAN) {
        GaussianModel gaussianModel(v, e, maxWeight, arg);
        return gaussianModel.generate();
    } else if (law == SMALLWORLD) {
        WattsStrogatzModel wattsStrogatzModel(v, e, maxWeight, arg);
        return wattsStrogatzModel.generate();
    } else if (law == SCALEFREE) {
        BarabasiAlbertModel barabasiAlbertModel(v, e, maxWeight);
        return barabasiAlbertModel.generate();
    } else {
        UniformModel uniformModel(v, e, maxWeight, arg);
        return uniformModel.generate();
    }
};