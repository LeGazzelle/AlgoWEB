//
// Created by gabriel on 06/10/16.
//

#ifndef ALGOWEB_GRAPHIO_HPP
#define ALGOWEB_GRAPHIO_HPP

#include "../AlgoWEB.hpp"

extern bool __VERB;

class GraphIO {
public:
    static bool readGraph(std::string, UndirectedGraph *);

    static bool writeGraph(std::string, UndirectedGraph);
};

#endif //ALGOWEB_GRAPHIO_HPP
