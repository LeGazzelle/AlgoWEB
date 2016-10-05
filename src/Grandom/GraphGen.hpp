//
// Created by Gabriele Santi on 05/10/16.
//

#ifndef ALGOWEB_GRAPHGEN_HPP
#define ALGOWEB_GRAPHGEN_HPP

#include <ctime>
#include "../AlgoWEB.hpp"

class GraphGen {
public:
    static UndirectedGraph generate(int, int, int);

private:
    static void swap(int *, int *);

    static void permute(int *, int);

    static void initArray(int *, int);
};

#endif //ALGOWEB_GRAPHGEN_HPP
