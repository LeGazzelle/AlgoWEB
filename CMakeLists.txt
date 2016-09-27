cmake_minimum_required(VERSION 3.6.0) #CMAKE version check
project(AlgoWEB)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -O2")
include_directories(src/utilities)

set(SOURCE_FILES src/MstW/Crt_MstW.cpp src/test/AlgoWEB.cpp)
add_executable(AlgoWEB ${SOURCE_FILES})