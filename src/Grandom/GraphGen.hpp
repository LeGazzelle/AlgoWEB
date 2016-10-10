//
// Created by Gabriele Santi on 05/10/16.
//

#ifndef ALGOWEB_GRAPHGEN_HPP
#define ALGOWEB_GRAPHGEN_HPP

#include <ctime>
#include "../AlgoWEB.hpp"

typedef std::pair<Edge, bool> Result;

class GraphGen {
public:
    static UndirectedGraph generate(unsigned long, unsigned long, unsigned int, unsigned int);

private:
    static void swap(unsigned long *, unsigned long *);

    static void permute(unsigned long *, unsigned long);

    static void initArray(unsigned long *, unsigned long);
};

#endif //ALGOWEB_GRAPHGEN_HPP
