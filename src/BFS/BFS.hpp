//
// Created by Leonardo De Laurentiis on 08/10/16.
//

#ifndef ALGOWEB_BFS_H
#define ALGOWEB_BFS_H


#include <queue>
#include <vector>
#include "../AlgoWEB.hpp"

class BFS {
public:

    BFS(UndirectedGraph g, Vertex u, unsigned long Dstr);

    void nextStep(unsigned long pBFS);

    void firstStep();

    ~BFS();

    unsigned long getVisitedVertices() const;

    unsigned long getVisitedEdges() const;

    bool isCompleted() const;

    bool isGreaterThanDstar() const;

    unsigned long getUDeg() const;


private:
    UndirectedGraph graph;
    Vertex vertexU;
    unsigned long visitedVertices;
    unsigned long visitedEdges;
    bool completed;
    bool greaterThanDstar;
    unsigned long uDeg;
    unsigned long Dstar;
    //data structures for BFS
    std::queue<Vertex> *toBeVisited;
    EdgesMatrix visitedEdgesMatrix; //initialized to false
    bool pause;
    NeighboursIterator ni;

    void edgesMatrixInit(NumVertices n);

    void setVisitedEdge(unsigned long source, unsigned long target);

    void setVisitedVertex();
};

#endif //ALGOWEB_BFS_H
