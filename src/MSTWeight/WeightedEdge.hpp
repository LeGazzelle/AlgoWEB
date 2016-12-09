//
// Created by Gabriele Santi on 10/10/16.
//

#include "../AlgoWEB.hpp"

class WeightedEdge {
public:
    Vertex source;
    Vertex target;
    weight_t weight;

    WeightedEdge() {}

    WeightedEdge(Vertex s, Vertex t, weight_t w) : source(s), target(t), weight(w) {}
};

class WeightedEdgeComparator {
public:
    WeightedEdgeComparator() {}

    bool operator()(const WeightedEdge &lhs, const WeightedEdge &rhs) const {
        return lhs.weight > rhs.weight;
    }
};