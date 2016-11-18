//
// Created by Gabriele Santi on 25/09/16.
//
#include "../MSTWeight/MSTWCompare.hpp"
#include "../FileIO/GraphIO.hpp"

using namespace std;


int main(int argc, char *argv[]) {
    cout << "AlgoWEB 2015-16" << endl;

    std::ofstream outfile;
    outfile.open("/home/gabriel/tmp_dataset/results/out.ssv", std::ios_base::app);
    FastGraph *g;
    weight_t maxWeight;
    g = GraphIO::readGraph(argv[1], &maxWeight);


    MSTWCompare *algo = new MSTWCompare(*g, maxWeight);

    cout << "Average degree d = " << algo->getAverageDegree() << "; epsilon = " << stod(argv[2]) << endl;

    outfile << g->numEdges() << " ";

    /*******/
#if 0
    clock_t krk_begin = clock();
    double krk_ans = algo->KruskalAlgorithm();
    clock_t krk_end = clock();

    long double elapsed_krk = double(krk_end - krk_begin) / CLOCKS_PER_SEC;

    cout << "Risultato Kruskal:\t" << krk_ans << endl;
    cout << "Tempo: " << elapsed_krk << endl << "--------------------\n";
    outfile << elapsed_krk << " ";
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
    outfile << elapsed_prm << " ";
#endif
    /*******/

    /*******/
#if 1
    CRTresult crt_ans = algo->CRTAlgorithm(stod(argv[2]));


    cout << "Risultato CRT:\t" << crt_ans.res << endl;
    cout << "Tempo: " << crt_ans.time << endl << "--------------------\n";
    outfile << crt_ans.time << std::endl;
#endif
    /*******/


    return 0;
}