//
// Created by leo on 05/10/16.
//

#ifndef ALGOWEB_GRAPHMLUTILS_H
#define ALGOWEB_GRAPHMLUTILS_H

#include <boost/graph/graphml.hpp>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "../MstW/Crt_MstW.hpp"
#include <string>


using namespace boost;
using namespace std;

class GraphMLUtils {
public:
    GraphMLUtils(void);

    GraphMLUtils(UndirectedGraph* g, string fileoutput_name,dynamic_properties* dp);

    int writeGraphML();
    int readGraphML(string fileinput_name,UndirectedGraph* g,dynamic_properties* dynamicProperties);

    ~GraphMLUtils();

private:
    UndirectedGraph graph;
    string file_name;
    dynamic_properties dp;


};



#endif //ALGOWEB_GRAPHMLUTILS_H
