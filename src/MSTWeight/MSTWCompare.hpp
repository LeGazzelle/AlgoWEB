//
// Created by Gabriele Santi on 25/09/16.
//
#ifndef ALGOWEB_CRT_MSTW_HPP
#define ALGOWEB_CRT_MSTW_HPP

#include <algorithm>

#include "../AlgoWEB.hpp"
#include "../utilities/randomsequence.hpp"
#include "../BFS/BFS.hpp"
#include "WeightedEdge.hpp"
#include <boost/graph/random.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

class VertexConverter {
private:
    long long next;
    long long *vertices;

public:
    VertexConverter();

    void init(unsigned long dim);

    long long getVertexIndex(long long globalIndex);
};

class CRTChronoResult {
private:
    long double boost_time;
    long double approxGraphAvgDegreeTime;
    long double extractGraphTime;
    long double bfsTime;

public:
    double CRTresult;

    CRTChronoResult() {
        this->boost_time = 0.0;
        this->approxGraphAvgDegreeTime = 0.0;
    }

    void addPartialDiff(clock_t start, clock_t end) {
        this->boost_time += double(end - start);
    }

    void addPartialBfs(clock_t tot) {
        this->bfsTime += double(tot);
    }

    void addPartialBoost(clock_t tot) {
        this->boost_time += double(tot);
    }

    void addPartialApproxGraphAvgDegree(clock_t tot) {
        this->approxGraphAvgDegreeTime += double(tot);
    }

    void addPartialExtractGraph(clock_t tot) {
        this->extractGraphTime += double(tot);
    }


    long double getBfsTime() {
        return this->bfsTime / CLOCKS_PER_SEC;
    }

    long double getBoostTime() {
        return this->boost_time / CLOCKS_PER_SEC;
    }

    long double getApproxGraphAvgDegreeTime() {
        return this->approxGraphAvgDegreeTime / CLOCKS_PER_SEC;
    }

    long double getExtractGraphTime() {
        return this->extractGraphTime / CLOCKS_PER_SEC;
    }
};

/*class RandomVertexExtractor {
private:
    Vertex *vindexes;
    unsigned long size;

    void scramble();

public:
    RandomVertexExtractor(unsigned long dim);

    Vertex extractRandomVertex();

    void prepare();
};*/

class MSTWCompare {
public:
    MSTWCompare(UndirectedGraph g, int maxWeight);

    CRTChronoResult *CRTAlgorithm(double eps);

    long double prepareLightRun();

    CRTChronoResult *LightCRTAlgorithm(double eps);

    double KruskalAlgorithm();

    double PrimAlgorithm();

    long double getAverageDegree();

    ~MSTWCompare();

private:
    UndirectedGraph graph;
    int maxWeight;
    //management
    boost::random::mt19937 generator;
    UndirectedGraph g_i;
    NumVertices num_vert_G;
    std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, WeightedEdgeComparator> orderedEdges;
    VertexConverter vc;
    //management for light runs
    std::vector<UndirectedGraph> subgraphs;
    std::vector<FisherYatesSequence> fys;
    std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, WeightedEdgeComparator> copyOfOrderedEdges;
    //Chrono result
    CRTChronoResult *crtChronoResult;

    double approxNumConnectedComps(double eps, unsigned long avgDeg, int i);

    unsigned long approxGraphAvgDegree(double eps);

    double lightApproxNumConnectedComps(double eps, unsigned long avgDeg, int i);

    unsigned long lightApproxGraphAvgDegree(double eps);

    unsigned long computeNumVertices(unsigned long n, double eps);

    unsigned long computeNumVerticesLemma4(unsigned long n, double eps);

    void extractGraph(int i);

    UndirectedGraph lightExtractGraph(int i);
};

#endif //ALGOWEB_CRT_MSTW_HPP
