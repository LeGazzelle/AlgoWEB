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
    this->i = 0;
    this->Dstar = Dstr;
    this->edgesMatrixInit(num_vertices(g));
    this->toBeVisited = new std::queue<Vertex>();
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

void BFS::nextStep() {
    NeighboursIterator ai, ai_end;
    Vertex source, target;
    bool pause = false;
    unsigned long pauseBFS = 2 * this->visitedEdges;
    VertexMap vMap = get(vertex_index, this->graph);
    WeightMap weight = get(edge_weight, this->graph);
    source = this->toBeVisited->front();
    this->greaterThanDstar = boost::degree(source, this->graph) > this->Dstar;

    for (boost::tie(ai, ai_end) = adjacent_vertices(source, this->graph); ai != ai_end; ++ai) {
        target = get(vMap, *ai);

        if (//weight[edge(source, target, this->graph).first] <= this->i &&
            !this->visitedEdgesMatrix[source][target]) {

            this->toBeVisited->push(target);
            setVisitedEdge(source, target);

            if (this->visitedEdges == pauseBFS) {
                pause = true;
                break;
            }
        }
    }

    if (pause) {
        return;
    } else {
        setVisitedVertex();
    }

    if (this->toBeVisited->empty()) {
        this->completed = true; //BFS Completed
        return;
    }

    nextStep();
}

void BFS::firstStep() {
    NeighboursIterator ai, ai_end;
    unsigned long k = boost::degree(this->vertexU, this->graph);
    Vertex source, target;
    VertexMap vMap = get(vertex_index, this->graph);
    WeightMap weight = get(edge_weight, this->graph);
    source = get(vertex_index, this->graph, this->vertexU);

    if (k) {
        for (boost::tie(ai, ai_end) = adjacent_vertices(source, this->graph); ai != ai_end; ++ai) {
            target = get(vMap, *ai);

            //if (weight[edge(source, target, this->graph).first] <= this->i) {
            this->toBeVisited->push(target);
            setVisitedEdge(source, target);
            //}
        }
    }

    this->uDeg = k;
    this->visitedVertices = 1; //just u in this first step
    if (num_vertices(this->graph) == this->visitedVertices) this->completed = true; //BFS Completed
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

void BFS::setI(int i) {
    this->i = i;
}