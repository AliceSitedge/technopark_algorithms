#ifndef ALGORITHMS_SET_GRAPH_H
#define ALGORITHMS_SET_GRAPH_H

#include <unordered_set>

#include "i_graph.h"


class SetGraph : public IGraph {
public:
    explicit SetGraph(int n);
    explicit SetGraph(const IGraph &graph);

    void add_edge(int from, int to) override;

    int vertices_count() const override;

    std::vector<int> get_next_vertices(int vertex) const override;
    std::vector<int> get_prev_vertices(int vertex) const override;

private:
    std::vector<std::unordered_set<int>> edges;
};

#endif  // ALGORITHMS_SET_GRAPH_H
