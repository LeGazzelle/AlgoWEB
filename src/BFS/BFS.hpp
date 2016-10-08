//
// Created by Leonardo De Laurentiis on 08/10/16.
//

#ifndef ALGOWEB_BFS_H
#define ALGOWEB_BFS_H


#include "../AlgoWEB.hpp"

class BFS {
public:

    BFS(UndirectedGraph g, Vertex u, unsigned long Dstr);

    void nextStep();

    void firstStep();

    ~BFS();

    int getVisitedVertices() const;

    int getVisitedEdges() const;

    bool isCompleted() const;

    bool isGreaterThanDstar() const;

    int getUDeg() const;

private:

    UndirectedGraph graph;
    Vertex vertexU;
    int visitedVertices;
    int visitedEdges;
    bool completed;
    bool greaterThanDstar;
    int uDeg;
    int i;
    unsigned long Dstar;
};

#endif //ALGOWEB_BFS_H
