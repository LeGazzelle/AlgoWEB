//
// Created by Gabriele Santi on 05/10/16.
//

#ifndef ALGOWEB_ALGOWEB_HPP
#define ALGOWEB_ALGOWEB_HPP

#include <list>
#include <vector>
#include <queue>

typedef unsigned long long Vertex;
typedef unsigned long long vertex_index_t;
typedef unsigned int Weight;
typedef unsigned int weight_t;
typedef std::pair<weight_t, vertex_index_t> AdjacentItem;
typedef std::list<AdjacentItem> AdjacencyList;
typedef std::list<AdjacentItem>::iterator AdjacencyIterator;
typedef std::vector<std::vector<bool>> BfsMatrix;
typedef std::vector<bool> StatefulVertices; //false stands for UNEXPLORED, true for QUEUED/EXPLORED

struct Edge {
    vertex_index_t source;
    vertex_index_t target;

    Edge(vertex_index_t s, vertex_index_t t) {
        source = s;
        target = t;
    }

    inline bool operator==(const Edge &other) const {
        return this->source == other.source && this->target == other.target;
    }

    ~Edge() {}
};

struct EdgeHash {
    std::size_t operator()(Edge const &e) const {
        std::size_t h1 = std::hash<vertex_index_t>{}(e.source);
        std::size_t h2 = std::hash<vertex_index_t>{}(e.target);

        return h1 ^ (h2 << 1);
    }
};

enum LawType {
    UNIFORM,
    GAUSSIAN,
    SMALLWORLD,
    SCALEFREE
};

typedef struct _result {
    double res;
    double time;
} CRTresult;

#endif //ALGOWEB_ALGOWEB_HPP