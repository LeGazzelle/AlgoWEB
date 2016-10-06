//
// Created by leo on 05/10/16.
//

#ifndef ALGOWEB_GRAPHMLUTILS_H
#define ALGOWEB_GRAPHMLUTILS_H

#include <boost/graph/graphml.hpp>
#include "../AlgoWEB.hpp"


using namespace boost;
using namespace std;

class GraphMLUtils {
public:
    GraphMLUtils(void);

    int writeGraphML(UndirectedGraph g, string fileoutput_name,dynamic_properties dp);
    int readGraphML(string fileinput_name,UndirectedGraph* g,dynamic_properties dynamicProperties);

    ~GraphMLUtils();
};



#endif //ALGOWEB_GRAPHMLUTILS_H
