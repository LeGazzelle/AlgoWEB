//
// Created by Gabriele Santi on 03/11/16.
//

#include "FastGraphs.hpp"


FastSubGraph::FastSubGraph(vertex_index_t n) {
    this->adjacencyLists = std::vector<AdjacencyList>(n);

//    for (vertex_index_t i = 0ULL; i < n; i++)
//        this->adjacencyLists[i] = std::list<AdjacentItem>();
}

vertex_index_t FastSubGraph::numVertices() const {
    return this->adjacencyLists.size();
}

AdjacencyList FastSubGraph::adjacentVertices(Vertex u) const {
    return this->adjacencyLists[u];
}

vertex_index_t FastSubGraph::degree(Vertex u) {
    return this->adjacencyLists[u].size();
}

/**
 * Add edge between node v1 and v2, dumb version: node v1 and v2 must
 * esist (this is always true as the list of nodes is a pre-initialized
 * vector) and edge between v1 and v2 musn't already esist, in order to
 * avoid double edges; this method does NOT check this to mantain
 * good performances.
 *
 * @param v1
 * @param v2
 * @param weight
 */
void FastSubGraph::addEdge(Vertex v1, Vertex v2, Weight w) {
    this->adjacencyLists[v1].emplace_back(w, v2);
    this->adjacencyLists[v2].emplace_back(w, v1);
}

FastSubGraph::~FastSubGraph() {
}

FastGraph::FastGraph(vertex_index_t n) : FastSubGraph(n) {
    this->edgeList = EdgeList();
    this->num_vertices = 0ULL;
}

EdgeList FastGraph::edges() {
    return this->edgeList;
}

void FastGraph::addEdge(Vertex v1, Vertex v2, Weight w) {
    //fare col vertex converter...
    FastSubGraph::addEdge(v1, v2, w);
    this->edgeList.push(WeightedEdge(v1, v2, w));
    this->num_vertices += 2; //FIXME differenziare se aggiunge zero, uno o due nodi
}

vertex_index_t FastGraph::numVertices() const {
    return FastSubGraph::numVertices();

    //FIXME finché non è risolto il fixme a riga 59 return this->num_vertices;
}

FastGraph::~FastGraph() {
}
