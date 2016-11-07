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

const double EPSILON = 0.49;
const std::string CWG_FILE = "/home/gabriel/tmp_dataset/test_10k_40k_25.cwg";


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

    FastGraph *g;
    FastGraph *g2;
    weight_t maxWeight;
    g = GraphIO::readGraph(CWG_FILE, &maxWeight);


    MSTWCompare *algo = new MSTWCompare(*g, maxWeight);

    cout << "Average degree d = " << algo->getAverageDegree() << endl;

    /*******/
#if 1
    clock_t krk_begin = clock();
    double krk_ans = algo->KruskalAlgorithm();
    clock_t krk_end = clock();

    long double elapsed_krk = double(krk_end - krk_begin) / CLOCKS_PER_SEC;

    cout << "Risultato Kruskal:\t" << krk_ans << endl;
    cout << "Tempo: " << elapsed_krk << endl << "--------------------\n";
#endif
    /*******/

    /*******/
#if 1
    clock_t prm_begin = clock();
    double prm_ans = algo->PrimAlgorithm();
    clock_t prm_end = clock();

    long double elapsed_prm = double(prm_end - prm_begin) / CLOCKS_PER_SEC;

    cout << "Risultato Prim:\t" << prm_ans << endl;
    cout << "Tempo: " << elapsed_prm << endl << "--------------------\n";
#endif
    /*******/

    /*******/
#if 0
    long double elapsed_preparation_lcrt = algo->prepareLightRun();
    clock_t lcrt_begin = clock();
    double lcrt_ans = algo->LightCRTAlgorithm(EPSILON);
    clock_t lcrt_end = clock();

    long double elapsed_calculus_lcrt = double(lcrt_end - lcrt_begin) / CLOCKS_PER_SEC;
    elapsed_preparation_lcrt /= CLOCKS_PER_SEC;


    cout << "Risultato Light CRT:\t" << lcrt_ans << endl;
    cout << "Tempo per la preparazione: " << elapsed_preparation_lcrt << endl << "-------\n";
    cout << "Tempo per il calcolo: " << elapsed_calculus_lcrt << endl << "--------------------\n";
#endif
    /*******/

    /*******/
#if 1
    g2 = GraphIO::readGraph(CWG_FILE, &maxWeight);
    MSTWCompare *algo2 = new MSTWCompare(*g2, maxWeight);
    clock_t crt_begin = clock();
    double crt_ans = algo2->CRTAlgorithm(EPSILON);
    clock_t crt_end = clock();

    long double elapsed_crt = double(crt_end - crt_begin) / CLOCKS_PER_SEC;


    cout << "Risultato CRT:\t" << crt_ans << endl;
    cout << "Tempo: " << elapsed_crt << endl << "--------------------\n";
#endif
    /*******/

//    FisherYatesSequence fys = FisherYatesSequence(15);
//
//    for (int k = 1; k <= 30; k++) {
//        cout << fys.next() << ", ";
//        if (k % 15 == 0)
//            cout << endl;
//    }


    return 0; //EXIT_SUCCESS; seems to belong to stdlib.h
}

void print_weighted_graph(FastGraph g) {
    EdgeList edgeList = g.edges();
    EdgeIterator ei, eend = edgeList.end();

    for (ei = edgeList.begin(); ei != eend; ++ei) {
        cout << ei->source << " ----("
             << ei->weight << ")---->"
             << ei->target << '\n';
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