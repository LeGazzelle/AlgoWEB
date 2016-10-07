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
    int w;
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
        w = std::stoi(options[MAX_WEIGHT].arg);
    } else {
        std::cerr << "Missing compulsory argument: maximum weight\n";
        return -1;
    }

    if (options[TARGET_DIR]) {
        fileName = options[TARGET_DIR].arg;
        fileName += ".cwg";
    } else {
        fileName = "./out_rand_graph.cwg";
    }

    if (options[VERBOSE]) {
        __VERB = true;
    } else {
        __VERB = false;
    }

    //Random, weighted, connected, undirected graph generation
    GraphGen gg;
    UndirectedGraph g = gg.generate(v, e, w);

    //save file
    GraphIO::writeGraph(fileName, g);


    return 0;
}