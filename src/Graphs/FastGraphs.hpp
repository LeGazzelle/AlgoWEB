//
// Created by Gabriele Santi on 03/11/16.
//

#ifndef ALGOWEB_FASTGRAPHS_HPP
#define ALGOWEB_FASTGRAPHS_HPP

#include <iostream>
#include "../MSTWeight/WeightedEdge.hpp"
#include "VertexConverter.hpp"

typedef std::list<WeightedEdge> EdgeList;
typedef std::list<WeightedEdge>::iterator EdgeIterator;


class FastGraph {
private:
    EdgeList edgeList;
protected:
    std::vector<AdjacencyList> adjacencyLists;

public:
    FastGraph(vertex_index_t n);

    FastGraph(const FastGraph *other); //copy constructor

    virtual vertex_index_t numVertices() const;

    AdjacencyList adjacentVertices(Vertex u) const;

    vertex_index_t degree(Vertex u);

    void printByAdjList();

    void printByEdges();

    virtual void addUndirectedEdge(Vertex v1, Vertex v2, Weight w);

    virtual void addNoRepeatingUndirectedEdge(Vertex v1, Vertex v2, Weight w);

    EdgeList edges();

    virtual ~FastGraph();

    vertex_index_t numEdges();
};

class FastSubGraph : public FastGraph {
private:
    //need to track manually the number of vertices because the list of nodes is
    //pre-initialized to n and could always return n as size
    //it has been done with internal structure of VertexConverter
    VertexConverter vc;
public:
    FastSubGraph(vertex_index_t n);

    FastSubGraph(const FastSubGraph *other); //copy constructor

    void addUndirectedEdge(Vertex v1, Vertex v2, Weight w);

    void addNoRepeatingUndirectedEdge(Vertex v1, Vertex v2, Weight w);

    void printByAdjListLocal();

    void printByAdjListGlobal();

    vertex_index_t numVertices() const;

    ~FastSubGraph();
};

#endif //ALGOWEB_FASTGRAPHS_HPP
