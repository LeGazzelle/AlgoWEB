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
    //this->edgesMatrixInit(g.numVertices()); //O(n^2)
    this->verticesState = BfsVertices(g.numVertices());
    //DEBUG
    //this->verticesState = {}; //initialize the entire array to UNEXPLORED
    this->toBeVisited = new std::queue<Vertex>();
    this->pause = false;
}

/*void BFS::edgesMatrixInit(const vertex_index_t n) {
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
}*/

void BFS::firstStep() {
    AdjacencyList al = this->graph.adjacentVertices(this->vertexU);
    vertex_index_t k = this->graph.degree(this->vertexU);
    AdjacencyIterator ai_end = al.end();
    Vertex target;

    if (k) {
        for (AdjacencyIterator ai = al.begin(); ai != ai_end; ++ai) {
            target = ai->second;

            queue(target);
        }
    }

    this->uDeg = k;
    //skip completeness check -- in the first step it's impossible to complete the BFS
    this->verticesState[this->vertexU] = EXPLORED;
    this->visitedVertices++; //just u in the first step -- no need to call setVisited since for the first vertex we do not use the queue
    if (k > this->Dstar) greaterThanDstar = true;
}

void BFS::nextStep() {
    AdjacencyIterator ai, ai_end;
    AdjacencyList al;
    Vertex source;

    vertex_index_t pauseBFS = 2 * this->visitedEdges;

    while (!this->toBeVisited->empty()) {
        source = this->toBeVisited->front();
        //optimization
        if (this->graph.degree(source) == 1) {
            setVisited(source);
            continue;
        }
        al = this->graph.adjacentVertices(source);

        //resume state, eventually
        if (!this->pause) {
            ai = al.begin();
        } else {
            ai = this->ni;
            this->pause = false;
        }
        ai_end = al.end();

        while (ai != ai_end) {
            if (this->verticesState[ai->second] != UNEXPLORED) {
                ai++;
                continue;
            }

            queue(ai->second);
            ai++;

            if (this->visitedEdges == pauseBFS) {
                //save state
                if (ai != ai_end) {
                    this->pause = true;
                    this->ni = ai;
                } else {
                    setVisited(source);
                }
                return;
            }
        }
        setVisited(source);
    }

    this->completed = true;
}

void BFS::queue(Vertex v) {
    this->toBeVisited->push(v);
    this->verticesState[v] = EXPLORED;
    this->visitedEdges++;
}

/*void BFS::setVisitedEdge(Vertex source, Vertex target) {
    this->visitedEdgesMatrix[source][target].edgeState = true;
    this->visitedEdgesMatrix[target][source].edgeState = true;
    this->visitedEdges++;
}*/

void BFS::setVisited(Vertex v) {
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