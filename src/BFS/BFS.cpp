//
// Created by Leonardo De Laurentiis on 08/10/16.
//

#include "BFS.hpp"


//Constructor with a given graph and a vertex from where the BFS starts
BFS::BFS(FastGraph g, Vertex u, vertex_index_t Dstr) : graph(g) {
    this->vertexU = u;
    this->visitedVertices = 0;
    this->visitedEdges = 0;
    this->completed = false;
    this->greaterThanDstar = false;
    this->uDeg = 0;
    this->Dstar = Dstr;
    this->edgesMatrixInit(g.numVertices()); //O(n^2)
    this->toBeVisited = new std::queue<Vertex>();
    this->pause = false;
}

void BFS::edgesMatrixInit(const vertex_index_t n) {
    this->visitedEdgesMatrix.resize(n);
    vertex_index_t i;

    for (i = 0; i < n; i++) { //O(n)
        this->visitedEdgesMatrix[i].resize(n);
        this->visitedEdgesMatrix[i] = {}; //initialize the entire array to: false for edgeState, UNEXPLORED for vertexState
    }

//    for (i = 0; i < n; i++) { //O(n^2)
//        for (j = 0; j < n; j++)
//            this->visitedEdgesMatrix[i][j].edgeState = false;
//    }
}

void BFS::nextStep(vertex_index_t pBFS) {
    AdjacencyIterator ai, ai_end;
    AdjacencyList al;
    Vertex source, target;
    vertex_index_t pauseBFS = pBFS ? pBFS : (2 * this->visitedEdges);
    source = this->toBeVisited->front();
    al = this->graph.adjacentVertices(source);
    ai_end = al.end();
    this->greaterThanDstar = this->graph.degree(source) > this->Dstar;
    if (this->pause) {
        ai = this->ni;
        this->pause = false;
    } else {
        ai = al.begin();
    }

    for (; ai != ai_end; ++ai) {
        target = ai->second;

        if (!this->visitedEdgesMatrix[source][target].edgeState) {

            this->toBeVisited->push(target);
            setVisitedEdge(source, target);

            if (this->visitedEdges == pauseBFS && ai != ai_end) {
                this->pause = true;
                this->ni = ++ai;
                return;
            }
        }
    }

    setVisitedVertex();

    if (this->toBeVisited->empty()) {
        this->completed = true; //BFS Completed
        return;
    }

    nextStep(pauseBFS);
}

void BFS::firstStep() {
    AdjacencyIterator ai, ai_end;
    AdjacencyList al = this->graph.adjacentVertices(this->vertexU);
    vertex_index_t k = this->graph.degree(this->vertexU);
    ai_end = al.end();
    Vertex target;

    if (k) {
        for (ai = al.begin(); ai != ai_end; ++ai) {
            target = ai->second;

            this->toBeVisited->push(target);
            setVisitedEdge(this->vertexU, target);
        }
    }

    this->uDeg = k;
    this->visitedVertices = 1; //just u in this first step
    //in the first step it's impossible to complete the BFS
    if (k > this->Dstar) greaterThanDstar = true;

}

void BFS::setVisitedEdge(Vertex source, Vertex target) {
    this->visitedEdgesMatrix[source][target].edgeState = true;
    this->visitedEdgesMatrix[target][source].edgeState = true;
    this->visitedEdges++;
}

void BFS::setVisitedVertex() {
    this->toBeVisited->pop();
    this->visitedVertices++;
}

//Destructor
BFS::~BFS() {
    delete this->toBeVisited;
}


vertex_index_t BFS::getVisitedVertices() const {
    return visitedVertices;
}

vertex_index_t BFS::getVisitedEdges() const {
    return visitedEdges;
}

bool BFS::isCompleted() const {
    return completed;
}


bool BFS::isGreaterThanDstar() const {
    return greaterThanDstar;
}


vertex_index_t BFS::getUDeg() const {
    return uDeg;
}