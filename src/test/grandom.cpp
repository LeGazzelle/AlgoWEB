//
// Created by Gabriele Santi on 07/10/16.
//
#include "grandom.hpp"


int main(int argc, char *argv[]) {
    argc -= (argc > 0);
    argv += (argc > 0);
    option::Stats stats(usage, argc, argv);

    std::vector<option::Option> options(stats.options_max);
    std::vector<option::Option> buffer(stats.buffer_max);
    option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);

    //arguments
    unsigned long v, e;
    unsigned int w, s;
    std::string fileName;

    if (parse.error())
        return -1;

    if (options[HELP] || argc == 0) {
        option::printUsage(std::cout, usage);
        return 0;
    }

    if (options[VERTICES]) {
        v = std::stoul(options[VERTICES].arg);
    } else {
        std::cerr << "Missing compulsory argument: #vertices\n";
        return -1;
    }

    if (options[EDGES]) {
        e = std::stoul(options[EDGES].arg);
    } else {
        std::cerr << "Missing compulsory argument: #edges\n";
        return -1;
    }

    if (options[MAX_WEIGHT]) {
        w = (unsigned int) std::stoi(options[MAX_WEIGHT].arg);
    } else {
        std::cerr << "Missing compulsory argument: maximum weight\n";
        return -1;
    }

    //Facultative arguments
    if (options[TARGET_DIR]) {
        fileName = options[TARGET_DIR].arg;
        fileName += ".cwg";
    } else {
        fileName = "./out_rand_graph.cwg";
    }

    if (options[SEED]) {
        s = (unsigned int) std::stoi(options[SEED].arg);
    } else {
        s = 0;
    }

    if (options[VERBOSE]) {
        __VERB = true;
    } else {
        __VERB = false;
    }

    //Other sanitary checks
    if (e < v - 1) {
        std::cerr << "Cannot produce a connected graph with " << v
                  << " vertices with just " << e << " edges!\n";
        return -1;
    }

    if (e > (v * (v - 1)) / 2) {
        std::wcerr << e << " edges are too much for a graph with just " << v
                   << " vertices (we are not dealing with multigraphs "
                           "here); setting 'e' to the maximum " << (v * (v - 1)) / 2 << std::endl;
        e = (v * (v - 1)) / 2;
    }

    //Random, weighted, connected, undirected graph generation
    UndirectedGraph g = GraphGen::generate(v, e, w, s);

    //save file
    GraphIO::writeGraph(fileName, g);


    return 0;
}