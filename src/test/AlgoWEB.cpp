//
// Created by Gabriele Santi on 25/09/16.
//
#include "../MstW/Crt_MstW.hpp"
#include "../Grandom/GraphGen.hpp"
#include "../FileIO/GraphMLUtils.hpp"

using namespace std;


template<typename UndirectedGraph>
void print_weighted_graph(UndirectedGraph const);

template<typename UndirectedGraph>
void print_adjacent_vertex(UndirectedGraph const);


int main(void) {
    cout << "AlgoWEB 2015-16" << endl;

    /**
     * UndirectedGraph g = ...; //<--- parse da file, creazione random...
     *
     * mstwUtilitez x = new maosmf();
     *
     * x.setGraph(g, w);
     *
     * time t1, t2;
     *
     * t1.start();
     * result s1 = mstwUtilises.kruskal();
     * t1.stop();
     *
     * t2.start();
     * result s2 = mstwUtilities.crtAlgorithm(eps); //volendo anche Prim
     * t2.stop();
     *
     * //print something
     *
     */

    size_t nV = 3;
    //UndirectedGraph g(nV);
    UndirectedGraph *g = new UndirectedGraph(nV);

    add_edge(vertex(0, *g), vertex(1, *g), Weight(2), *g);
    add_edge(vertex(1, *g), vertex(2, *g), Weight(1), *g);
    add_edge(vertex(2, *g), vertex(3, *g), Weight(3), *g);

    VertexIterator i, end;
    //NeighboursIterator ai, a_end;
    property_map<UndirectedGraph, vertex_index_t>::type
            index_map = get(vertex_index, *g);

    cout << "Tento di stampare gli indici dei nodi del grafo\n";
    for (boost::tie(i, end) = vertices(*g); i != end; ++i) {
        cout << "index: " << get(index_map, *i) << endl;
        //cout << "weight: " << get(ciao, *i) << endl;
    }


    //MSTWUtilities bho = new MSTWUtilities(g, 3); the old way
    MSTWUtilities bho(*g, 3);

    double result = bho.CRTAlgorithm(0.5);

    cout << "result: " << result << endl;

    GraphGen gg;

    UndirectedGraph g2 = gg.generate(10, 20, 10);

    //print_weighted_graph(g2);

    print_adjacent_vertex(g2);

    dynamic_properties dp;
    dp.property("name", get(vertex_index, g2));
    dp.property("weight", get(edge_weight, g2));
    GraphMLUtils::writeGraphML(g2, "/home/gabriel/tmp_dataset/ciao.txt", dp);


    //TODO LA READ
//    UndirectedGraph* g3 = new UndirectedGraph();
//    dynamic_properties dp2;
//    dp2.property("name", get(vertex_index, *g3));
//    dp2.property("weight", get(edge_weight, *g3));
//    std::ifstream inFile;
//    inFile.open("/home/gabriel/tmp_dataset/ciao.txt", std::ifstream::in);
//    read_graphml(inFile, g3, dp2);
//    inFile.close();
//    print_adjacent_vertex(g3);

    return 0; //EXIT_SUCCESS; seems to belong to stdlib.h
}

template<typename UndirectedGraph>
void print_weighted_graph(UndirectedGraph g) {
    WeightMap weight = get(edge_weight, g);
    EdgeIterator ei, eend;
    for (boost::tie(ei, eend) = edges(g); ei != eend; ++ei) {
        cout << get(vertex_index, g)[source(*ei, g)] << " ----("
             << get(weight, *ei) << ")---->"
             << get(vertex_index, g)[target(*ei, g)] << '\n';
    }
}

template<typename UndirectedGraph>
void print_adjacent_vertex(UndirectedGraph g) {
    WeightMap weight = get(edge_weight, g);
    cout << "Graph Print: (between parentesis the weights on the edges)" << endl;
    for (auto vertex = vertices(g); vertex.first != vertex.second; ++vertex.first) {
        cout << *vertex.first << " is connected with ";
        for (auto neighbour = adjacent_vertices(*vertex.first, g);
             neighbour.first != neighbour.second; ++neighbour.first) {
            Result res = edge(*vertex.first, *neighbour.first, g);
            cout << *neighbour.first << "(" << get(weight, res.first) << ") ";
        }
        cout << endl;
    }
}