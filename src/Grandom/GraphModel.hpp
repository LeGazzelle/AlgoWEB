//
// Created by Gabriele Santi on 24/11/16.
//

#ifndef ALGOWEB_GRAPHMODEL_HPP
#define ALGOWEB_GRAPHMODEL_HPP

#include <ctime>
#include <random>
#include <climits>
#include <unordered_map>
#include "../Graphs/FastGraphs.hpp"

typedef std::unordered_map<Edge, short, EdgeHash> EdgeMap;
typedef std::pair<EdgeMap::iterator, bool> EMapIter;


class GraphModel {
protected:
    vertex_index_t v;
    vertex_index_t e;
    weight_t maxWeight;
public:
    GraphModel(vertex_index_t, vertex_index_t, weight_t);

    virtual FastGraph generate() = 0;
};

class UniformModel : public GraphModel {
public:
    UniformModel(vertex_index_t, vertex_index_t, weight_t, unsigned int);

    FastGraph generate();
protected:
    unsigned int seed;

    void initArray(vertex_index_t pInt[]);

    void permute(vertex_index_t pInt[]);

    std::pair<std::unordered_map<Edge, short, EdgeHash>::iterator, bool>
    updateEdgesMap(EdgeMap *, vertex_index_t, vertex_index_t);

    void swap(vertex_index_t *, vertex_index_t *);

    std::pair<vertex_index_t, bool> findTarget(EdgeMap *, vertex_index_t, vertex_index_t);
};

class GaussianModel : public UniformModel {
public:
    GaussianModel(vertex_index_t, vertex_index_t, weight_t, unsigned int);

    FastGraph generate();
};

class WattsStrogatzModel : public GraphModel {
public:
    WattsStrogatzModel(vertex_index_t, vertex_index_t, weight_t, int beta);

    FastGraph generate();

private:
    double beta;
};

class BarabasiAlbertModel : public GraphModel {
public:
    BarabasiAlbertModel(vertex_index_t, vertex_index_t, weight_t);

    FastGraph generate();
};



#endif //ALGOWEB_GRAPHMODEL_HPP
