cmake_minimum_required(VERSION 3.6.0) #CMAKE version check
project(AlgoWEB CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Wextra -O3")
set(LIBS_DIR "src/utilities")
set(STATIC_LIBS_DIR "src/utilities/static")
include_directories(${LIBS_DIR})
link_directories(${STATIC_LIBS_DIR})

set(SOURCE_FILES src/AlgoWEB.hpp src/FileIO/GraphIO.cpp src/FileIO/GraphIO.hpp src/Graphs/FastGraphs.cpp src/Graphs/FastGraphs.hpp src/Graphs/VertexConverter.cpp src/Graphs/VertexConverter.hpp)
set(ALGO_WEB_SOURCE_FILES src/test/AlgoWEB.cpp ${SOURCE_FILES} src/BFS/BFS.cpp src/BFS/BFS.hpp src/MSTWeight/WeightedEdge.hpp src/MSTWeight/MSTWCompare.cpp src/utilities/randomsequence.hpp src/Graphs/FastGraphs.cpp src/Graphs/FastGraphs.hpp src/Graphs/VertexConverter.cpp src/Graphs/VertexConverter.hpp src/UI/ProgressAnimations.hpp)
set(GRANDOM_SOURCE_FILES src/test/grandom.cpp src/test/grandom.hpp ${SOURCE_FILES} src/Grandom/GraphGen.cpp src/Grandom/GraphGen.hpp src/Grandom/GraphModel.cpp src/Grandom/GraphModel.hpp)
add_executable(AlgoWEB ${ALGO_WEB_SOURCE_FILES})
add_executable(Grandom ${GRANDOM_SOURCE_FILES})


#STATIC LIBRARIES, BUILD FOR X86_64
set(STATIC_LIB_GRAPH src/utilities/static/libboost_graph.a)
set(STATIC_LIB_REGEX src/utilities/static/libboost_regex.a)
add_library(boost_graph STATIC ${STATIC_LIB_GRAPH})
add_library(boost_regex STATIC ${STATIC_LIB_REGEX})

set_target_properties(boost_graph PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(boost_regex PROPERTIES LINKER_LANGUAGE CXX)
add_dependencies(AlgoWEB boost_graph boost_regex)
target_link_libraries(AlgoWEB boost_graph boost_regex)