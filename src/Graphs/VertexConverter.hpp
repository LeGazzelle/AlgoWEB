//
// Created by Gabriele Santi on 03/11/16.
//

#ifndef ALGOWEB_VERTEXCONVERTER_HPP
#define ALGOWEB_VERTEXCONVERTER_HPP

#include <climits>
#include "../AlgoWEB.hpp"

#define NULL_VERTEX ULLONG_MAX

class VertexConverter {
private:
    vertex_index_t next;
    vertex_index_t *vertices;

public:
    VertexConverter(vertex_index_t dim);

    vertex_index_t getVertexIndex(vertex_index_t globalIndex);

    vertex_index_t getSize() const;
};

#endif //ALGOWEB_VERTEXCONVERTER_HPP
