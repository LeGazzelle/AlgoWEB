//
// Created by Gabriele Santi on 03/11/16.
//

#include "VertexConverter.hpp"

VertexConverter::VertexConverter(vertex_index_t dim) {
    this->vertices = new vertex_index_t[dim];
    this->next = 0;

    for (vertex_index_t i = 0LL; i < dim; i++)
        this->vertices[i] = NULL_VERTEX;
}

vertex_index_t VertexConverter::getVertexIndex(vertex_index_t globalIndex) {
    if (this->vertices[globalIndex] == NULL_VERTEX)
        this->vertices[globalIndex] = this->next++;

    return vertices[globalIndex];
}

vertex_index_t VertexConverter::getSize() const {
    return this->next;
}
