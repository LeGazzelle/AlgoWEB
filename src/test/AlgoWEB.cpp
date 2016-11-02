//
// Created by Gabriele Santi on 25/09/16.
//
//#include <chrono>
#include "../MSTWeight/MSTWCompare.hpp"
#include "../FileIO/GraphIO.hpp"

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

//    size_t nV = 3;
//    //UndirectedGraph g(nV);
//    UndirectedGraph *g = new UndirectedGraph(nV);
//
//    add_edge(vertex(0, *g), vertex(1, *g), Weight(2), *g);
//    add_edge(vertex(1, *g), vertex(2, *g), Weight(1), *g);
//    add_edge(vertex(2, *g), vertex(3, *g), Weight(3), *g);
//
//    VertexIterator i, end;
//    //NeighboursIterator ai, a_end;
//    property_map<UndirectedGraph, vertex_index_t>::type
//            index_map = get(vertex_index, *g);
//
//    cout << "Tento di stampare gli indici dei nodi del grafo\n";
//    for (boost::tie(i, end) = vertices(*g); i != end; ++i) {
//        cout << "index: " << get(index_map, *i) << endl;
//        //cout << "weight: " << get(ciao, *i) << endl;
//    }
//
//
//    //MSTWCompare bho = new MSTWCompare(g, 3); the old way
//    MSTWCompare bho(*g, 3);
//
//    double result = bho.CRTAlgorithm(0.5);
//
//    cout << "result: " << result << endl;
//
//    GraphGen gg;
//
//    UndirectedGraph g2 = gg.generate(10, 20, 10, 0);
//
//    //print_weighted_graph(g2);
//
//    print_adjacent_vertex(g2);
//
//    GraphIO::writeGraph("/home/gabriel/tmp_dataset/test.txt", g2);
//
//    UndirectedGraph *g3 = new UndirectedGraph();
//    GraphIO::readGraph("/home/gabriel/tmp_dataset/test.txt", g3);
//
//    print_adjacent_vertex(*g3);

    UndirectedGraph *g = new UndirectedGraph();
    int maxWeight;
    GraphIO::readGraph("/home/gabriel/tmp_dataset/test_medium_big.cwg", g, &maxWeight);

    MSTWCompare *algo = new MSTWCompare(*g, maxWeight);

    cout << "Average degree d = " << algo->getAverageDegree() << endl;

    /*******/
#if 1
    clock_t krk_begin = clock();
    double krk_ans = algo->KruskalAlgorithm();
    clock_t krk_end = clock();

    double elapsed_krk = double(krk_end - krk_begin) / CLOCKS_PER_SEC;

    cout << "Risultato Kruskal:\t" << krk_ans << endl;
    cout << "Tempo: " << elapsed_krk << endl << "--------------------\n";
#endif
    /*******/

    /*******/
#if 1
    clock_t prm_begin = clock();
    double prm_ans = algo->PrimAlgorithm();
    clock_t prm_end = clock();

    double elapsed_prm = double(prm_end - prm_begin) / CLOCKS_PER_SEC;

    cout << "Risultato Prim:\t" << prm_ans << endl;
    cout << "Tempo: " << elapsed_prm << endl << "--------------------\n";
#endif
    /*******/

    /*******/
#if 1
    double elapsed_preparation_lcrt = algo->prepareLightRun();
    clock_t lcrt_begin = clock();
    double lcrt_ans = algo->LightCRTAlgorithm(0.25);
    clock_t lcrt_end = clock();

    double elapsed_calculus_lcrt = double(lcrt_end - lcrt_begin) / CLOCKS_PER_SEC;
    elapsed_preparation_lcrt /= CLOCKS_PER_SEC;


    cout << "Risultato Light CRT:\t" << lcrt_ans << endl;
    cout << "Tempo per la preparazione: " << elapsed_preparation_lcrt << endl << "-------\n";
    cout << "Tempo per il calcolo: " << elapsed_calculus_lcrt << endl << "--------------------\n";
#endif
    /*******/

    /*******/
#if 1
    clock_t crt_begin = clock();
    //auto crt_begin_hr = chrono::high_resolution_clock::now();
    double crt_ans = algo->CRTAlgorithm(0.25);
    //auto crt_end_hr = chrono::high_resolution_clock::now();
    clock_t crt_end = clock();

    //auto elapsed_crt_hr = chrono::duration_cast<chrono::nanoseconds>(crt_end_hr - crt_begin_hr).count() / 1000000000.0;
    double elapsed_crt = double(crt_end - crt_begin) / CLOCKS_PER_SEC;

    cout << "Risultato CRT:\t" << crt_ans << endl;
    cout << "Tempo: " << elapsed_crt << /*" oppure " << elapsed_crt_hr << */endl << "--------------------\n";
#endif
    /*******/


    //DEBUG test

//    for (int j = 1; j <= maxWeight; j++) {
//        G_i = algo->computeG_i(j);
//
//        cout << "G_i per i = " << j << endl;
//        print_adjacent_vertex(G_i);
//    }

    //DEBUG end


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

//template<typename UndirectedGraph>
//void print_adjacent_vertex(const UndirectedGraph g) {
//    ConstWeightMap weight = get(edge_weight, g);
//    cout << "Graph Print: (between parentesis the weights on the edges)" << endl;
//    for (pair<VertexIterator, VertexIterator> vertices = boost::vertices(g); vertices.first != vertices.second; ++vertices.first) {
//        cout << *vertices.first << " is connected with ";
//        for (auto neighbour = adjacent_vertices(*vertices.first, g);
//             neighbour.first != neighbour.second; ++neighbour.first) {
//            Result res = edge(*vertices.first, *neighbour.first, g);
//            cout << *neighbour.first << "(" << get(weight, res.first) << ") ";
//        }
//        cout << endl;
//    }
//    cout << "#vertices: " << num_vertices(g) << ", #edges: " << num_edges(g) << endl;
//}