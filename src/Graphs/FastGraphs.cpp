//
// Created by Gabriele Santi on 03/11/16.
//

#include "FastGraphs.hpp"

bool operator==(const WeightedEdge& lhs, const WeightedEdge& rhs) {
    return lhs.source == rhs.source && lhs.target == rhs.target;
}
/*
 *  FASTGRAPH
 */

FastGraph::FastGraph(vertex_index_t n) {
    this->adjacencyLists = std::vector<AdjacencyList>(n);
    this->edgeList = EdgeList();
}

vertex_index_t FastGraph::numVertices() const {
    return this->adjacencyLists.size();
}

AdjacencyList *FastGraph::adjacentVertices(Vertex u) {
    return &this->adjacencyLists[u];
}

vertex_index_t FastGraph::degree(Vertex u) {
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
void FastGraph::addUndirectedEdge(Vertex v1, Vertex v2, Weight w) {
    this->adjacencyLists[v1].emplace_back(w, v2);
    this->adjacencyLists[v2].emplace_back(w, v1);

    this->edgeList.emplace_back(WeightedEdge(v1, v2, w));
}

/**
 * Add edge between node v1 and v2, smart version: if an
 * edge between v2 and v1 does esist, no edge will be added,
 * mantaining only one pair (v1,v2)-(v2,v1)
 *
 * @param v1
 * @param v2
 * @param weight
 * @return true if an insertion has been performed, false otherwise
 */
bool FastGraph::addNoRepeatingUndirectedEdge(Vertex v1, Vertex v2, Weight w) {
    if (this->hasEdge(v1, v2))
        return false;
    else {
        this->addUndirectedEdge(v1, v2, w);
        return true;
    }
}

EdgeList *FastGraph::edges() {
    return &this->edgeList;
}

FastGraph::~FastGraph() {
}

void FastGraph::printByAdjList() {
    AdjacencyList al;
    AdjacencyIterator ai;

    for (vertex_index_t v = 0ULL; v < this->numVertices(); v++) {
        al = this->adjacencyLists[v];

        std::cout << v << " ---> ";

        for (ai = al.begin(); ai != al.end(); ai++)
            std::cout << "(w:" << ai->first << ") "
                      << ai->second << ", ";
        std::cout << std::endl;
    }
}

void FastGraph::printByEdges() {
    EdgeIterator ei, eend = this->edgeList.end();

    for (ei = this->edgeList.begin(); ei != eend; ++ei) {
        std::cout << ei->source << " ----("
                  << ei->weight << ")---->"
                  << ei->target << '\n';
    }
}

FastGraph::FastGraph(const FastGraph *other) :
        edgeList(other->edgeList), adjacencyLists(other->adjacencyLists) {}

vertex_index_t FastGraph::numEdges() {
    return this->edgeList.size();
}

FastGraph::operator FastSubGraph() const {
    //BUG PRONE: cannot add vertices due to inconsistent state of vertex converter
    FastSubGraph ret = FastSubGraph(this->numVertices());
    ret.adjacencyLists = std::vector<AdjacencyList>(this->adjacencyLists);

    return ret;
}

bool FastGraph::rewire(vertex_index_t source, AdjacencyIterator& oldTarget, vertex_index_t newTarget) {
    vertex_index_t iter = newTarget;

    if (source == iter)
        ++iter;

    if (this->hasEdge(source, iter)) {
        iter = (iter + 1) % this->numVertices();
        if (iter == source)
            ++iter;
        if (iter == newTarget)
            return false;
    }

    this->adjacencyLists[oldTarget->second].remove(AdjacentItem(oldTarget->first, source));

    oldTarget->second = iter;

    this->adjacencyLists[iter].emplace_back(oldTarget->first, source);

    //TODO aggiornare la edgeList

    return true;

//    this->adjacencyLists[source].remove(AdjacentItem(weight, oldTarget));
//    this->adjacencyLists[oldTarget].remove(AdjacentItem(weight, source));
//
//    this->edgeList.remove(WeightedEdge(source, oldTarget, weight));
//
//    vertex_index_t iter = newTarget;
//
//    if (source == iter)
//        ++iter;
//
//    while (!this->addNoRepeatingUndirectedEdge(source, iter, weight)) {
//        iter = (iter + 1) % this->numVertices();
//        if (iter == source)
//            ++iter;
//        if (iter == newTarget)
//            return false;
//    }
//
//    return true;
}

bool FastGraph::hasEdge(vertex_index_t source, vertex_index_t target) {
    AdjacencyIterator ai_end = this->adjacencyLists[source].end();

    for (AdjacencyIterator ai = this->adjacencyLists[source].begin(); ai != ai_end; ++ai)
        if (ai->second == target)
            return true;

    return false;
}


/*
 *  FASTSUBGRAPH
 */

FastSubGraph::FastSubGraph() : FastGraph(vertex_index_t(0)), vc(0) {}

FastSubGraph::FastSubGraph(vertex_index_t n) : FastGraph(n), vc(n) {}

FastSubGraph::FastSubGraph(const FastSubGraph *other) :
        FastGraph(other), vc(other->vc) {}

void FastSubGraph::addUndirectedEdge(Vertex v1, Vertex v2, Weight w) {
    v1 = this->vc.getVertexIndex(v1);
    v2 = this->vc.getVertexIndex(v2);

    this->adjacencyLists[v1].emplace_back(w, v2);
    this->adjacencyLists[v2].emplace_back(w, v1);
}

vertex_index_t FastSubGraph::numVertices() const {
    return this->vc.getSize();
}

FastSubGraph::~FastSubGraph() {
}

void FastSubGraph::printByAdjListGlobal() {
    //TODO add support to VertexConverter class
}

void FastSubGraph::printByAdjListLocal() {
    FastGraph::printByAdjList();
}

bool FastSubGraph::addNoRepeatingUndirectedEdge(Vertex v1, Vertex v2, Weight w) {
    this->adjacencyLists[v1].emplace_back(w, v2);
    this->adjacencyLists[v2].emplace_back(w, v1);

    return true;
}
