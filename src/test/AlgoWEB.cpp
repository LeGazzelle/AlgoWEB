//
// Created by Gabriele Santi on 25/09/16.
//
#include "../MstW/Crt_MstW.hpp"
#include "../Grandom/GraphGen.hpp"

using namespace std;


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
    UndirectedGraph g(nV);

    add_edge(vertex(0, g), vertex(1, g), Weight(2), g);
    add_edge(vertex(1, g), vertex(2, g), Weight(1), g);
    add_edge(vertex(2, g), vertex(3, g), Weight(3), g);

    VertexIterator i, end;
    NeighboursIterator ai, a_end;
    property_map<UndirectedGraph, vertex_index_t>::type
            index_map = get(vertex_index, g);
    property_map<UndirectedGraph, edge_weight_t>::type ciao = get(edge_weight, g);

    cout << "Tento di stampare gli indici dei nodi del grafo\n";
    for (boost::tie(i, end) = vertices(g); i != end; ++i) {
        cout << "index: " << get(index_map, *i) << endl;
        //cout << "weight: " << get(ciao, *i) << endl;
    }


    //MSTWUtilities bho = new MSTWUtilities(g, 3); the old way
    MSTWUtilities bho(g, 3);

    double result = bho.CRTAlgorithm(0.5);


    cout << "result: " << result << endl;

    GraphGen gg;

    gg.generate(0, 0, 0);

    return 0; //EXIT_SUCCESS; seems to belong to stdlib.h
}