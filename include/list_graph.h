#ifndef ALGORITHMS_LIST_GRAPH_H
#define ALGORITHMS_LIST_GRAPH_H

#include <cassert>

#include "i_graph.h"


class ListGraph : public IGraph {
public:
    explicit ListGraph(int n);
    explicit ListGraph(const IGraph &graph);

    void add_edge(int from, int to) override;

    int vertices_count() const override;

    std::vector<int> get_next_vertices(int vertex) const override;
    std::vector<int> get_prev_vertices(int vertex) const override;

private:
    std::vector <std::vector<int>> adjacency_lists;
};

#endif  // ALGORITHMS_LIST_GRAPH_H
