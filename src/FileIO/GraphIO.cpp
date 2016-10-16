//
// Created by Gabriele Santi on 06/10/16.
//

#include "GraphIO.hpp"

bool GraphIO::readGraph(std::string fileName, UndirectedGraph *g, int *maxWeight) {
    std::ifstream inFile(fileName);
    std::string edge, tmp;
    std::string::size_type pt;
    unsigned long u, v;
    int w;

    *maxWeight = 0;

    if (inFile.is_open()) {
        while (getline(inFile, edge)) {
            u = std::stoul(edge, &pt);
            pt++;
            tmp = edge.substr(pt);
            v = std::stoul(tmp, &pt);
            pt++;
            w = std::stoi(tmp.substr(pt));

            if (w > *maxWeight)
                *maxWeight = w;

            if (__VERB)
                std::cout << "adding edge (" << u << "," << v << ") with weight " << w << std::endl;

            add_edge(vertex(u, *g), vertex(v, *g), EdgeWeight(AUTO_INDEX, w), *g);
        }

        inFile.close();
        return true;
    } else {
        return false;
    }
}

bool GraphIO::writeGraph(std::string fileName, const UndirectedGraph g) {
    std::ofstream outFile(fileName, std::ios::out);
    ConstWeightMap weight= get(edge_weight, g);
    EdgeIterator ei, eend;

    if (outFile.is_open()) {
        for (boost::tie(ei, eend) = edges(g); ei != eend; ++ei) {
            outFile << get(vertex_index, g)[source(*ei, g)] << " "
                    << get(vertex_index, g)[target(*ei, g)] << " "
                    << get(weight, *ei) << "\n";
        }

        outFile.close();
        return true;
    } else {
        return false;
    }
}