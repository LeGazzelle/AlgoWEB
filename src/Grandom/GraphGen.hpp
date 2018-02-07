//
// Created by Gabriele Santi on 05/10/16.
//

#ifndef ALGOWEB_GRAPHGEN_HPP
#define ALGOWEB_GRAPHGEN_HPP

#include "GraphModel.hpp"


class GraphGen {
public:
    static FastGraph generate(vertex_index_t, vertex_index_t, weight_t, unsigned int, LawType);
};

#endif //ALGOWEB_GRAPHGEN_HPP
