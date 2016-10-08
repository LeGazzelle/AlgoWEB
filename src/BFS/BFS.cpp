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
}

void BFS::nextStep() {


}

void BFS::firstStep() {
    NeighboursIterator ai, ai_end;
    unsigned int k = 0;
    for (boost::tie(ai, ai_end) = adjacent_vertices(this->vertexU, this->graph); ai != ai_end; ++ai)
        k++;
    this->uDeg = k;
    this->visitedVertices = k + 1; //The k nodes closed to u, plus u
    this->visitedEdges = k;
    if (num_vertices(this->graph) == (k + 1)) this->completed = true; //BFS Completed
    if (k > this->Dstar) greaterThanDstar = true;

}

//Destructor
BFS::~BFS() {}


int BFS::getVisitedVertices() const {
    return visitedVertices;
}

int BFS::getVisitedEdges() const {
    return visitedEdges;
}

bool BFS::isCompleted() const {
    return completed;
}


bool BFS::isGreaterThanDstar() const {
    return greaterThanDstar;
}


int BFS::getUDeg() const {
    return uDeg;
}
