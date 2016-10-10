//
// Created by Gabriele Santi on 10/10/16.
//

#include "../AlgoWEB.hpp"

class WeightedEdge {
public:
    Edge edge;
    //Vertex source;
    //Vertex target;
    int weight;

    WeightedEdge(Edge e, int w) : edge(e), weight(w) {}
};

class WeightedEdgeComparator
{
  bool reverse;
public:
  WeightedEdgeComparator(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const WeightedEdge& lhs, const WeightedEdge&rhs) const
  {
    if (reverse)
        return lhs.weight >= rhs.weight;
    else
        return lhs.weight < rhs.weight;
  }
};