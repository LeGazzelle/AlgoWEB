//
// Created by Gabriele Santi on 06/10/16.
//

#include "GraphIO.hpp"
#include "../UI/ProgressAnimations.hpp"


/**
 * Assume no duplicate edges
 *
 * @param fileName
 * @param maxWeight
 * @return
 */
FastGraph *GraphIO::readGraph(std::string fileName, weight_t *maxWeight) {
    FastGraph *fg;
    ProgressAnimations progressAnimations = ProgressAnimations();
    std::ifstream inFile(fileName);
    std::string edge, tmp;
    std::string::size_type pt;
    vertex_index_t vertices, lines, u, v, i = 0;
    weight_t w;

    *maxWeight = 0;

    std::cout << "Reading graph from file " << fileName << "...\n" << std::flush;

    if (inFile.is_open()) {
        if (getline(inFile, edge)) {
            vertices = std::stoul(edge);
            fg = new FastGraph(vertices);

            if (getline(inFile, edge)) {
                lines = std::stoul(edge);
                lines += 2; //number of lines of the file
            } else {
                return nullptr;
            }
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

            fg->addUndirectedEdge(u, v, w);

            i++;
            progressAnimations.printProgBar((unsigned) (100.0 * i / lines));
        }

        inFile.close();
        std::cout << " DONE\n" << std::flush;
        return fg;
    } else {
        std::cout << " ERROR\n";
        return nullptr;
    }
}

/**
 * This new version avoid to add duplicate edges!
 *
 * @param fileName
 * @param g
 * @return
 */
bool GraphIO::writeGraph(std::string fileName, FastGraph g) {
    std::ofstream outFile(fileName, std::ios::out);
    AdjacencyList *al;
    AdjacencyIterator ai;

    if (outFile.is_open()) {
        outFile << g.numVertices() << "\n";
        outFile << g.numEdges();

        for (vertex_index_t v = 0ULL; v < g.numVertices(); v++) {
            al = g.adjacentVertices(v);

            for (ai = al->begin(); ai != al->end(); ai++)
                if (ai->second > v) { //if ai->second < v it has been added already when v was equal to ai->second
                    outFile << "\n" << v << " "
                            << ai->second << " "
                            << ai->first;
                }
        }
        //no empty line at the end of the file

        outFile.close();
        return true;
    } else {
        return false;
    }
}