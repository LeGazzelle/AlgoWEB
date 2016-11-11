//
// Created by Gabriele Santi on 25/09/16.
//
#ifndef ALGOWEB_CRT_MSTW_HPP
#define ALGOWEB_CRT_MSTW_HPP

#include <algorithm>
#include <ctime>

#include "../utilities/randomsequence.hpp"
#include "../BFS/BFS.hpp"
#include "../Graphs/FastGraphs.hpp"
#include "../Graphs/VertexConverter.hpp"
#include "../UI/ProgressAnimations.hpp"

//utility for CRT
//class CRTsubgraphs {
//private:
//    std::vector<FastSubGraph> mSub;
//
//public:
//    FastSubGraph& operator[](weight_t idx)       { return mSub[idx-1]; }
//    const FastSubGraph& operator[](weight_t idx) const { return mSub[idx-1]; }
//
//    CRTsubgraphs(weight_t i) {
//        this->mSub = std::vector<FastSubGraph>(i);
//    }
//};

class MSTWCompare {
public:
    MSTWCompare(FastGraph g, weight_t maxWeight);

    CRTresult CRTAlgorithm(double eps);

//    long double prepareLightRun();
//
//    double LightCRTAlgorithm(double eps);

    double KruskalAlgorithm();

    double PrimAlgorithm();

    long double getAverageDegree();

    ~MSTWCompare();

private:
    FastGraph graph;
    //CRT management
    weight_t maxWeight;
    FastSubGraph g_i;
    vertex_index_t num_vert_G;
    std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, WeightedEdgeComparator> crtOrderedEdges;
    //CRT management (needed structures)
    //CRTsubgraphs subgraphs; //list of graphs, containint G_i at position i (transparently mapped to positions [0, w-1])
    //std::vector<FisherYatesSequence> fys;
    FisherYatesSequence *fys;
    //std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, WeightedEdgeComparator> copyOfOrderedEdges;
    //Prim management
    std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, WeightedEdgeComparator> primOrderedEdges;
    StatefulVertices visited;

    long double approxNumConnectedComps(double eps, vertex_index_t avgDeg, weight_t i);

    vertex_index_t approxGraphAvgDegree(double eps);

//    double lightApproxNumConnectedComps(double eps, vertex_index_t avgDeg, weight_t i);
//
//    vertex_index_t lightApproxGraphAvgDegree(double eps);

    vertex_index_t computeNumVertices(vertex_index_t n, double eps);

    vertex_index_t computeNumVerticesLemma4(vertex_index_t n, double eps);

    //void extractGraph(weight_t i);

//    FastSubGraph lightExtractGraph(weight_t i);

    vertex_index_t getRandomVertex(vertex_index_t);

    void extractSubGraph(weight_t);
};

//utility for Kruskal
class DisjointSets {
private:
    vertex_index_t *parent, *rnk;
    vertex_index_t n;

public:
    // Constructor.
    DisjointSets(vertex_index_t n);

    // Find the parent of a node 'u'
    // Path Compression
    vertex_index_t find(vertex_index_t u);

    // Union by rank
    void merge(vertex_index_t x, vertex_index_t y);
};

#endif //ALGOWEB_CRT_MSTW_HPP
