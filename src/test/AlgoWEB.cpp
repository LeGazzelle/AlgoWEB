//
// Created by Gabriele Santi on 25/09/16.
//
#include "../MstW/Crt_MstW.hpp"
#include "../Grandom/GraphGen.hpp"

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

//    property_map<UndirectedGraph, edge_weight_t>::type
//            weight = get(edge_weight, g2);
//    EdgeIterator ei, eend;
//    for (boost::tie(ei, eend) = edges(g2); ei != eend; ++ei) {
//        cout << get(vertex_index, g2)[source(*ei, g2)] << " ----("
//             << get(weight, *ei) << ")---->"
//             << get(vertex_index, g2)[target(*ei, g2)] << '\n';
//    }

    //print_weighted_graph(g2);
    WeightMap weight = get(edge_weight, g2);
    EdgeIterator ei, eend;
    for (boost::tie(ei, eend) = edges(g2); ei != eend; ++ei) {
        cout << get(vertex_index, g2)[source(*ei, g2)] << " ----("
             << get(weight, *ei) << ")---->"
             << get(vertex_index, g2)[target(*ei, g2)] << '\n';
    }

    print_adjacent_vertex(g2);

    return 0; //EXIT_SUCCESS; seems to belong to stdlib.h
}

template<typename UndirectedGraph>
void print_weighted_graph(UndirectedGraph const g) {
    WeightMap weight = get(edge_weight, g);
    EdgeIterator ei, eend;
    for (boost::tie(ei, eend) = edges(g); ei != eend; ++ei) {
        cout << get(vertex_index, g)[source(*ei, g)] << " ----("
             << get(weight, *ei) << ")---->"
             << get(vertex_index, g)[target(*ei, g)] << '\n';
    }
}

template<typename UndirectedGraph>
void print_adjacent_vertex(UndirectedGraph const g) {
    for (auto vertex = vertices(g); vertex.first != vertex.second; ++vertex.first) {
        std::cout << *vertex.first << " is connected with ";
        for (auto neighbour = adjacent_vertices(*vertex.first, g);
             neighbour.first != neighbour.second; ++neighbour.first) {
            std::cout << *neighbour.first << " ";
        }
        std::cout << std::endl;
    }
}