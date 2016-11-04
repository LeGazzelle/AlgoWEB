//
// Created by Gabriele Santi on 03/11/16.
//

#ifndef ALGOWEB_VERTEXCONVERTER_HPP
#define ALGOWEB_VERTEXCONVERTER_HPP

#include <climits>

#define NULL_VERTEX ULLONG_MAX

class VertexConverter {
private:
    unsigned long long next;
    unsigned long long *vertices;

public:
    VertexConverter();

    void init(unsigned long long dim);

    long long getVertexIndex(unsigned long long globalIndex);
};

#endif //ALGOWEB_VERTEXCONVERTER_HPP
