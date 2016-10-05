cmake_minimum_required(VERSION 3.6.0) #CMAKE version check
project(AlgoWEB CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -O2")
set(LIBS_DIR "src/utilities")
#set(STATIC_LIBS_DIR "src/utilities/static")
include_directories(${LIBS_DIR})
#link_directories(${STATIC_LIBS_DIR})

set(SOURCE_FILES src/MstW/Crt_MstW.cpp src/test/AlgoWEB.cpp src/Grandom/GraphGen.cpp src/Grandom/GraphGen.hpp src/AlgoWEB.hpp)
add_executable(AlgoWEB ${SOURCE_FILES})

#set(STATIC_LIB_FILES src/utilities/static/libboost_random.a)
#add_library(boost_random STATIC ${STATIC_LIB_FILES})
#set_target_properties(boost_random PROPERTIES LINKER_LANGUAGE CXX)
#add_dependencies(AlgoWEB boost_random)
#target_link_libraries(AlgoWEB boost_random)