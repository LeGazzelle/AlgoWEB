//
// Created by Gabriele Santi on 06/10/16.
//

#include "GraphIO.hpp"


FastGraph *GraphIO::readGraph(std::string fileName, int *maxWeight) {
    FastGraph *fg;
    std::ifstream inFile(fileName);
    std::string edge, tmp;
    std::string::size_type pt;
    unsigned long size, u, v;
    int w;

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
            w = std::stoi(tmp.substr(pt));

            if (w > *maxWeight)
                *maxWeight = w;

            fg->addEdge(u, v, w);
        }

        inFile.close();
        return fg;
    } else {
        return nullptr;
    }
}

bool GraphIO::writeGraph(std::string fileName, const FastGraph g) {
    std::ofstream outFile(fileName, std::ios::out);
    AdjacencyList al;
    AdjacencyIterator ai;

    if (outFile.is_open()) {
        outFile << g.numVertices() << "\n";

        for (vertex_index_t v = 0ULL; v < g.numVertices(); v++) {
            al = g.adjacentVertices(v);

            for (ai = al.begin(); ai != al.end(); ai++)
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