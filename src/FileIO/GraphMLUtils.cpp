//
// Created by Leonardo De Laurentiis on 05/10/16.
//

#include "GraphMLUtils.hpp"


//Default Constructor
//GraphMLUtils::GraphMLUtils(void) {
   // this->graph = NULL;
   // this->file_name = "";
//    this->dp = nullptr;
//}

//Destructor
//GraphMLUtils::~GraphMLUtils() {}

//Write an UndirectedGraph to a file in GraphML File Format
int GraphMLUtils::writeGraphML(UndirectedGraph g, std::string fileoutput_name, dynamic_properties dp) {
    std::ofstream outFile;
    outFile.open(fileoutput_name, std::ofstream::out);
    write_graphml(outFile, g, dp,
                  false); //L'ultimo parametro indica se i vertici sono ordinati oppure no (guardare eventualmente nella doc "write_graphml.html")
    outFile.flush();
    outFile.close();
    return 0;
}

//Read an UndirectedGraph (in GraphML File Format) from a file
int GraphMLUtils::readGraphML(std::string fileinput_name, UndirectedGraph *g, dynamic_properties dynamicProperties) {
//    std::ifstream inFile;
//    inFile.open(fileinput_name, std::ifstream::in);
//    read_graphml(inFile, g, dynamicProperties);
//    inFile.close();
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


    dynamic_properties dp;
    dp.property("name", get(vertex_index, g));
    dp.property("weight", get(edge_weight, g));
    string s="/home/leo/Scrivania/example1.txt";
    GraphMLUtils* test= new GraphMLUtils(g,s,dp);
    test->writeGraphML();

    cout << "Dovrei aver creato il file\n";

 * */