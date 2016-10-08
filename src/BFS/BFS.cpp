//
// Created by leo on 08/10/16.
//

#include "BFS.hpp"


//Constructor with a given graph and a vertex from where the BFS starts
BFS::BFS(UndirectedGraph g, Vertex u,unsigned int Dstr) {
    this->graph = g;
    this->vertexU = u;
    this->visitedVertices=0;
    this->visitedEdges=0;
    this->isCompleted= false;
    this->isGreaterThanDstar= false;
    this->uDeg=0;
    this->i=0;
    this->Dstar=Dstr;
}

void BFS::nextStep() {



}

void BFS::firstStep() {
    NeighboursIterator ai, ai_end;
    int k=0;
    for (tie(ai, ai_end) = adjacent_vertices(this->vertexU, this->graph); ai != ai_end; ++ai)
        k++;
    this->uDeg=k;
    this->visitedVertices=k+1; //The k nodes closed to u, plus u
    this->visitedEdges=k;
    if(num_vertices(this->graph)==(k+1)) this->isCompleted=true; //BFS Completed
    if(k>this->Dstar) isGreaterThanDstar=true;

}

//Destructor
BFS::~BFS() {}


int BFS::getVisitedVertices() const {
    return visitedVertices;
}

void BFS::setVisitedVertices(int visitedNodes) {
    BFS::visitedVertices = visitedNodes;
}

int BFS::getVisitedEdges() const {
    return visitedEdges;
}

void BFS::setVisitedEdges(int visitedEdges) {
    BFS::visitedEdges = visitedEdges;
}

bool BFS::isIsCompleted() const {
    return isCompleted;
}

void BFS::setIsCompleted(bool isCompleted) {
    BFS::isCompleted = isCompleted;
}

bool BFS::isIsGreaterThanDstar() const {
    return isGreaterThanDstar;
}

void BFS::setIsGreaterThanDstar(bool isGreaterThanDstar) {
    BFS::isGreaterThanDstar = isGreaterThanDstar;
}

int BFS::getUDeg() const {
    return uDeg;
}

void BFS::setUDeg(int uDeg) {
    BFS::uDeg = uDeg;
}

int BFS::getI() const {
    return i;
}

void BFS::setI(int i) {
    BFS::i = i;
}
