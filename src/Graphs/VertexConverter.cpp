//
// Created by Gabriele Santi on 03/11/16.
//

#include "VertexConverter.hpp"

VertexConverter::VertexConverter() {}

void VertexConverter::init(unsigned long long dim) {
    this->vertices = new unsigned long long[dim];

    for (long long i = 0LL; i < dim; i++)
        this->vertices[i] = NULL_VERTEX;
}

long long VertexConverter::getVertexIndex(unsigned long long globalIndex) {
    if (this->vertices[globalIndex] < 0LL)
        this->vertices[globalIndex] = this->next++;

    return vertices[globalIndex];
}