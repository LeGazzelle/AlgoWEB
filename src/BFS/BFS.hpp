//
// Created by Leonardo De Laurentiis on 08/10/16.
//

#ifndef ALGOWEB_BFS_H
#define ALGOWEB_BFS_H


#include <queue>
#include <vector>
#include "../AlgoWEB.hpp"
#include "../Graphs/FastGraphs.hpp"

class BFS {
public:

    BFS(FastGraph g, Vertex u, vertex_index_t Dstr);

    void nextStep();

    void firstStep();

    ~BFS();

    vertex_index_t getVisitedVertices() const;

    vertex_index_t getVisitedEdges() const;

    bool isCompleted() const;

    bool isGreaterThanDstar() const;

    vertex_index_t getUDeg() const;


private:
    FastGraph graph;
    Vertex vertexU;
    vertex_index_t visitedVertices;
    vertex_index_t visitedEdges;
    bool completed;
    bool greaterThanDstar;
    vertex_index_t uDeg;
    vertex_index_t Dstar;
    //data structures for BFS
    std::queue<Vertex> *toBeVisited;
    //BfsMatrix visitedEdgesMatrix; //initialized to false
    StatefulVertices verticesState;
    bool pause;
    AdjacencyList savedAl;
    AdjacencyIterator savedAi;

    //void edgesMatrixInit(vertex_index_t n);

    //void setVisitedEdge(Vertex source, Vertex target);

    void setVisited();

    void queue(Vertex v);
};

#endif //ALGOWEB_BFS_H
