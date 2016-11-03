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
    this->edgesMatrixInit(num_vertices(g)); //O(n^2)
    this->toBeVisited = new std::queue<Vertex>();
    this->pause = false;
}

void BFS::edgesMatrixInit(const NumVertices n) {
    this->visitedEdgesMatrix.resize(n);
    unsigned long i, j;

    for (i = 0; i < n; i++) { //O(n)
        this->visitedEdgesMatrix[i].resize(n);
    }

    for (i = 0; i < n; i++) { //O(n^2)
        for (j = 0; j < n; j++)
            this->visitedEdgesMatrix[i][j] = false;
    }
}

clock_t BFS::nextStep(unsigned long pBFS) {
    clock_t start, end, tot = 0;
    NeighboursIterator ai, ai_end;
    Vertex source, target;
    unsigned long pauseBFS = pBFS ? pBFS : (2 * this->visitedEdges);
    source = this->toBeVisited->front();

    start = clock();
    VertexMap vMap = get(vertex_index, this->graph);
    this->greaterThanDstar = boost::degree(source, this->graph) > this->Dstar;
    boost::tie(ai, ai_end) = adjacent_vertices(source, this->graph);
    end = clock();
    tot += (end - start);

    if (this->pause) {
        ai = this->ni;
        this->pause = false;
    }

    for (; ai != ai_end; ++ai) {
        start = clock();
        target = get(vMap, *ai);
        end = clock();
        tot += (end - start);

        if (!this->visitedEdgesMatrix[source][target]) {

            this->toBeVisited->push(target);
            setVisitedEdge(source, target);

            if (this->visitedEdges == pauseBFS && ai != ai_end) {
                this->pause = true;
                this->ni = ++ai;
                return tot;
            }
        }
    }

    setVisitedVertex();

    if (this->toBeVisited->empty()) {
        this->completed = true; //BFS Completed
        return tot;
    }

    return tot + nextStep(pauseBFS);
}

clock_t BFS::firstStep() {
    clock_t start, end, tot = 0;
    NeighboursIterator ai, ai_end;
    //DEBUG measure
    start = clock();
    unsigned long k = boost::degree(this->vertexU, this->graph);
    VertexMap vMap = get(vertex_index, this->graph);
    if (k)
        boost::tie(ai, ai_end) = adjacent_vertices(this->vertexU, this->graph);
    end = clock();
    tot += (end - start);
    Vertex target;


    if (k) {
        for (; ai != ai_end; ++ai) {
            start = clock();
            target = get(vMap, *ai);
            end = clock();
            tot += (end - start);

            this->toBeVisited->push(target);
            setVisitedEdge(this->vertexU, target);
        }
    }

    this->uDeg = k;
    this->visitedVertices = 1; //just u in this first step
    //in the first step it's impossible to complete the BFS
    if (k > this->Dstar) greaterThanDstar = true;

    return tot;
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
BFS::~BFS() {
    delete this->toBeVisited;
}


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