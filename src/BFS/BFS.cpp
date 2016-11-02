//
// Created by Leonardo De Laurentiis on 08/10/16.
//

#include "BFS.hpp"


//Constructor with a given graph and a vertex from where the BFS starts
BFS::BFS(UndirectedGraph g, Vertex u, unsigned long Dstr) {
    this->graph = g;
    this->vertexU = u;
    this->visitedVertices = 0;
    this->visitedEdges = 0;
    this->completed = false;
    this->greaterThanDstar = false;
    this->uDeg = 0;
    this->Dstar = Dstr;
    this->edgesMatrixInit(num_vertices(g));
    this->toBeVisited = new std::queue<Vertex>();
    this->pause = false;
}

void BFS::edgesMatrixInit(const NumVertices n) {
    this->visitedEdgesMatrix.resize(n);
    unsigned long i, j;

    for (i = 0; i < n; i++) {
        this->visitedEdgesMatrix[i].resize(n);
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            this->visitedEdgesMatrix[i][j] = false;
    }
}

void BFS::nextStep(unsigned long pBFS) {
    NeighboursIterator ai, ai_end;
    Vertex source, target;
    unsigned long pauseBFS = pBFS ? pBFS : (2 * this->visitedEdges);
    VertexMap vMap = get(vertex_index, this->graph);
    source = this->toBeVisited->front();
    this->greaterThanDstar = boost::degree(source, this->graph) > this->Dstar;
    boost::tie(ai, ai_end) = adjacent_vertices(source, this->graph);
    if (this->pause) {
        ai = this->ni;
        this->pause = false;
    }

    for (; ai != ai_end; ++ai) {
        target = get(vMap, *ai);

        if (!this->visitedEdgesMatrix[source][target]) {

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
    NeighboursIterator ai, ai_end;
    unsigned long k = boost::degree(this->vertexU, this->graph);
    Vertex /*source, */target;
    VertexMap vMap = get(vertex_index, this->graph);
    //source = get(vertex_index, this->graph, this->vertexU);

    if (k) {
        for (boost::tie(ai, ai_end) = adjacent_vertices(this->vertexU, this->graph); ai != ai_end; ++ai) {
            target = get(vMap, *ai);

            this->toBeVisited->push(target);
            setVisitedEdge(this->vertexU, target);
        }
    }

    this->uDeg = k;
    this->visitedVertices = 1; //just u in this first step
    //if (num_vertices(this->graph) == this->visitedVertices) this->completed = true; //BFS Completed
    if (k > this->Dstar) greaterThanDstar = true;

}

void BFS::setVisitedEdge(unsigned long source, unsigned long target) {
    this->visitedEdgesMatrix[source][target] = true;
    this->visitedEdgesMatrix[target][source] = true;
    this->visitedEdges++;
}

void BFS::setVisitedVertex() {
    this->toBeVisited->pop();
    this->visitedVertices++;
}

//Destructor
BFS::~BFS() {}


unsigned long BFS::getVisitedVertices() const {
    return visitedVertices;
}

unsigned long BFS::getVisitedEdges() const {
    return visitedEdges;
}

bool BFS::isCompleted() const {
    return completed;
}


bool BFS::isGreaterThanDstar() const {
    return greaterThanDstar;
}


unsigned long BFS::getUDeg() const {
    return uDeg;
}