//
// Created by leo on 08/10/16.
//

#ifndef ALGOWEB_BFS_H
#define ALGOWEB_BFS_H


#include "../AlgoWEB.hpp"

class BFS {
public:

    BFS(UndirectedGraph g, Vertex u,unsigned int Dstr);
    void nextStep();
    void firstStep();

    ~BFS();

    int getVisitedVertices() const;

    void setVisitedVertices(int visitedNodes);

    int getVisitedEdges() const;

    void setVisitedEdges(int visitedEdges);

    bool isIsCompleted() const;

    void setIsCompleted(bool isCompleted);

    bool isIsGreaterThanDstar() const;

    void setIsGreaterThanDstar(bool isGreaterThanDstar);

    int getUDeg() const;

    void setUDeg(int uDeg);

    int getI() const;

    void setI(int i);

private:

    UndirectedGraph graph;
    Vertex vertexU;
    int visitedVertices;
    int visitedEdges;
    bool isCompleted;
    bool isGreaterThanDstar;
    int uDeg;
    int i;
    unsigned int Dstar;
};

#endif //ALGOWEB_BFS_H
