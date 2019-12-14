cmake_minimum_required(VERSION 3.13)
project(Algorithms)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        src/list_graph.cpp
        src/matrix_graph.cpp
        src/set_graph.cpp
        src/arc_graph.cpp)

include_directories(include)

add_executable(task1 task1.cpp ${SOURCE_FILES})
