//
// Created by Gabriele Santi on 03/11/16.
//

#ifndef ALGOWEB_FASTGRAPHS_HPP
#define ALGOWEB_FASTGRAPHS_HPP

#include "../MSTWeight/WeightedEdge.hpp"

typedef std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, WeightedEdgeComparator> EdgeList;


class FastSubGraph {
protected:
    std::vector<AdjacencyList> adjacencyLists;

public:
    FastSubGraph(vertex_index_t n);

    virtual vertex_index_t numVertices() const;

    AdjacencyList adjacentVertices(Vertex u) const;

    vertex_index_t degree(Vertex u);

    virtual void addEdge(Vertex v1, Vertex v2, Weight w);

    virtual ~FastSubGraph();
};

class FastGraph : public FastSubGraph {
private:
    EdgeList edgeList;
    //need to track manually the number of vertices because the list of nodes is
    //pre-initialized to n and could always return n as size
    vertex_index_t num_vertices;
public:
    FastGraph(vertex_index_t n);

    //std::vector<Vertex> vertices(); ??? da rivedere
    EdgeList edges();

    void addEdge(Vertex v1, Vertex v2, Weight w);

    vertex_index_t numVertices() const;

    ~FastGraph();
};

#endif //ALGOWEB_FASTGRAPHS_HPP
