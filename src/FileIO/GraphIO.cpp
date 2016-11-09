//
// Created by Gabriele Santi on 06/10/16.
//

#include "GraphIO.hpp"


FastGraph *GraphIO::readGraph(std::string fileName, weight_t *maxWeight) {
    FastGraph *fg;
    std::ifstream inFile(fileName);
    std::string edge, tmp;
    std::string::size_type pt;
    vertex_index_t size, u, v;
    weight_t w;

    *maxWeight = 0;

    if (inFile.is_open()) {
        if (getline(inFile, edge)) {
            size = std::stoul(edge);
            fg = new FastGraph(size);
        } else {
            return nullptr;
        }
        while (getline(inFile, edge)) {
            u = std::stoul(edge, &pt);
            pt++;
            tmp = edge.substr(pt);
            v = std::stoul(tmp, &pt);
            pt++;
            w = (weight_t) std::stoul(tmp.substr(pt));

            if (w > *maxWeight)
                *maxWeight = w;

            fg->addNoRepeatingUndirectedEdge(u, v, w);
        }

        inFile.close();
        return fg;
    } else {
        return nullptr;
    }
}

bool GraphIO::writeGraph(std::string fileName, FastGraph g) {
    std::ofstream outFile(fileName, std::ios::out);
    AdjacencyList *al;
    AdjacencyIterator ai;

    if (outFile.is_open()) {
        outFile << g.numVertices() << "\n";

        for (vertex_index_t v = 0ULL; v < g.numVertices(); v++) {
            al = g.adjacentVertices(v);

            for (ai = al->begin(); ai != al->end(); ai++)
                outFile << v << " "
                        << ai->second << " "
                        << ai->first << "\n";
        }


        outFile.close();
        return true;
    } else {
        return false;
    }
}