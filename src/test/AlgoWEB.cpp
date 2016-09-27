//
// Created by Gabriele Santi on 25/09/16.
//
#include <iostream>
#include "../MstW/Crt_MstW.hpp"

using namespace std;


int main(void) {
    cout << "ALGOWeb 2015-16" << endl;

    size_t nV = 3;
    UndirectedGraph g(nV);

    add_edge(vertex(0, g), vertex(1, g), Weight(2), g);
    add_edge(vertex(1, g), vertex(2, g), Weight(1), g);
    add_edge(vertex(2, g), vertex(3, g), Weight(3), g);

    graph_traits<UndirectedGraph>::vertex_iterator i, end;
    graph_traits<UndirectedGraph>::adjacency_iterator ai, a_end;
    property_map<UndirectedGraph, vertex_index_t>::type
            index_map = get(vertex_index, g);

    cout << "Tento di stampare gli indici dei nodi del grafo\n";
    for (boost::tie(i, end) = vertices(g); i != end; ++i) {
        cout << get(index_map, *i) << endl;
    }

    MSTWUtilities bho(g, 3);

    double result = bho.CRTAlgorithm(0.5);

    cout << "result: " << result << endl;

    return 0; //EXIT_SUCCESS; seems to belong to stdlib.h
}