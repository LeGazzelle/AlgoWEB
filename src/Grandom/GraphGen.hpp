//
// Created by Gabriele Santi on 05/10/16.
//

#ifndef ALGOWEB_GRAPHGEN_HPP
#define ALGOWEB_GRAPHGEN_HPP

#include <ctime>
#include <random>
//#include "../AlgoWEB.hpp"
#include "../Graphs/FastGraphs.hpp"

class GraphGen {
public:
    static FastGraph generate(vertex_index_t, vertex_index_t, weight_t, unsigned int);

private:
    static void swap(vertex_index_t *, vertex_index_t *);

    static void permute(vertex_index_t *, vertex_index_t);

    static void initArray(vertex_index_t *, vertex_index_t);

    static BfsMatrix edgesMatrixInit(const vertex_index_t);

    static inline void updateEdgesMatrix(BfsMatrix *em, vertex_index_t, vertex_index_t);
};

#endif //ALGOWEB_GRAPHGEN_HPP
