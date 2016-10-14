//
// Created by gabriel on 06/10/16.
//

#ifndef ALGOWEB_GRAPHIO_HPP
#define ALGOWEB_GRAPHIO_HPP

#include <fstream>
#include "../AlgoWEB.hpp"

extern bool __VERB;

class GraphIO {
public:
    static bool readGraph(std::string, UndirectedGraph *, int *);

    static bool writeGraph(std::string, const UndirectedGraph);
};

#endif //ALGOWEB_GRAPHIO_HPP
