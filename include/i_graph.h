#ifndef ALGORITHMS_I_GRAPH_H
#define ALGORITHMS_I_GRAPH_H

#include <vector>


struct IGraph {
    virtual ~IGraph() = default;

    virtual void add_edge(int from, int to) = 0;

    virtual int vertices_count() const = 0;

    virtual std::vector<int> get_next_vertices(int vertex) const = 0;
    virtual std::vector<int> get_prev_vertices(int vertex) const = 0;
};

#endif  // ALGORITHMS_I_GRAPH_H
