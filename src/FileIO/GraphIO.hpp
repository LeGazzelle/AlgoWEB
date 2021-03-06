//
// Created by Gabriele Santi on 06/10/16.
//

#ifndef ALGOWEB_GRAPHIO_HPP
#define ALGOWEB_GRAPHIO_HPP

#include <fstream>
#include <cmath>
#include "../Grandom/GraphGen.hpp"
#include "../UI/ProgressAnimations.hpp"

extern bool __VERB;

class GraphIO {
public:
    static FastGraph *readGraph(std::string, weight_t *);

    static bool writeGraph(std::string, const FastGraph);
};

#endif //ALGOWEB_GRAPHIO_HPP
