cmake_minimum_required(VERSION 3.6.0) #CMAKE version check
project(AlgoWEB CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -O2")
set(LIBS_DIR "src/utilities")
set(STATIC_LIBS_DIR "src/utilities/static")
include_directories(${LIBS_DIR})
link_directories(${STATIC_LIBS_DIR})

set(SOURCE_FILES src/MstW/Crt_MstW.cpp src/test/AlgoWEB.cpp src/Grandom/GraphGen.cpp src/Grandom/GraphGen.hpp src/AlgoWEB.hpp src/FileIO/GraphIO.cpp src/FileIO/GraphIO.hpp)
add_executable(AlgoWEB ${SOURCE_FILES})

#STATIC LIBRARIES, BUILD FOR X86_64
set(STATIC_LIB_GRAPH src/utilities/static/libboost_graph.a)
set(STATIC_LIB_REGEX src/utilities/static/libboost_regex.a)
add_library(boost_graph STATIC ${STATIC_LIB_GRAPH})
add_library(boost_regex STATIC ${STATIC_LIB_REGEX})

set_target_properties(boost_graph PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(boost_regex PROPERTIES LINKER_LANGUAGE CXX)
add_dependencies(AlgoWEB boost_graph)
add_dependencies(AlgoWEB boost_regex)
target_link_libraries(AlgoWEB boost_graph)
target_link_libraries(AlgoWEB boost_regex)