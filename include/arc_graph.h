#ifndef ALGORITHMS_ARC_GRAPH_H
#define ALGORITHMS_ARC_GRAPH_H

#include "i_graph.h"


class ArcGraph : public IGraph {
public:
    explicit ArcGraph(int n);
    explicit ArcGraph(const IGraph &graph);

    void add_edge(int from, int to) override;

    int vertices_count() const override;

    std::vector<int> get_next_vertices(int vertex) const override;
    std::vector<int> get_prev_vertices(int vertex) const override;

private:
    int size;
    std::vector<std::pair<int, int>> edges;
};

#endif //ALGORITHMS_ARC_GRAPH_H
