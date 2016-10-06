//
// Created by Leonardo De Laurentiis on 05/10/16.
//

#ifndef ALGOWEB_GRAPHMLUTILS_H
#define ALGOWEB_GRAPHMLUTILS_H

#include "../AlgoWEB.hpp"


//using namespace boost;
//using namespace std;

class GraphMLUtils {
public:
    //GraphMLUtils(void);

    static int writeGraphML(UndirectedGraph g, std::string fileoutput_name, dynamic_properties dynamicProperties);
    static int readGraphML(std::string fileinput_name, UndirectedGraph* g, dynamic_properties dynamicProperties);

    //~GraphMLUtils();
};



#endif //ALGOWEB_GRAPHMLUTILS_H
