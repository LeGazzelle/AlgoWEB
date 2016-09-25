cmake_minimum_required(VERSION 3.6.0) #CMAKE version check
project(AlgoWEB)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

set(SOURCE_FILES src/test/libTest.cpp)
add_executable(AlgoWEB ${SOURCE_FILES})