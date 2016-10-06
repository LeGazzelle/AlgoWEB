//
// Created by gabriel on 06/10/16.
//

#ifndef ALGOWEB_GRAPHIO_HPP
#define ALGOWEB_GRAPHIO_HPP

#include "../AlgoWEB.hpp"

class GraphIO {
    static void readGraph(std::string, UndirectedGraph *);

    static void writeGraph(std::string, UndirectedGraph);
};

#endif //ALGOWEB_GRAPHIO_HPP
