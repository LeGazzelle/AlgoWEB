//
// Created by leo on 05/10/16.
//

#include "GraphMLUtils.h"

//Default Constructor
GraphMLUtils::GraphMLUtils(void) {
   // this->graph = NULL;
   // this->file_name = "";
//    this->dp = nullptr;
}

//Constructor with given graph
GraphMLUtils::GraphMLUtils(UndirectedGraph* g, string fileoutput_name,dynamic_properties* dp) {
    this->graph=*g;
    this->file_name=fileoutput_name;
    this->dp=*dp;

}

//Destructor
GraphMLUtils::~GraphMLUtils() {}

//Write an UndirectedGraph to a file in GraphML File Format
int GraphMLUtils::writeGraphML() {
    ofstream outFile;
    outFile.open(file_name,ofstream::out);
    boost::write_graphml(outFile, this->graph, this->dp, false); //L'ultimo parametro indica se i vertici sono ordinati oppure no (write_graphml.html)
    outFile.flush();
    outFile.close();
    return 0;
}

//Read an UndirectedGraph (in GraphML File Format) from a file
int GraphMLUtils::readGraphML(string fileinput_name, UndirectedGraph *g,dynamic_properties* dynamicProperties) {
    ifstream inFile;
    inFile.open(fileinput_name,ifstream::in);
    boost::read_graphml(inFile,g,*dynamicProperties);
    inFile.close();
    return 0;
}


/*
 * #include <boost/graph/graphml.hpp>
//PROVA GENERATORE RANDOM UNIFORME 0,1
typedef boost::mt19937 RNGType;
RNGType rng;
boost::uniform_int<> one_to_six( 0, 1 );
boost::variate_generator< RNGType, boost::uniform_int<> >
        dice(rng, one_to_six);
for ( int i = 0; i < 30; i++ ) {
int n  = dice();
cout << n << endl;
}
dynamic_properties dp;
dp.property("name", get(vertex_index, g));
dp.property("weight", get(edge_weight, g));

write_graphml(std::cout, g, dp, true);
 * */