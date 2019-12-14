#ifndef ALGORITHMS_MATRIX_GRAPH_H
#define ALGORITHMS_MATRIX_GRAPH_H

#include "i_graph.h"


class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(int n);
    explicit MatrixGraph(const IGraph &graph);

    void add_edge(int from, int to) override;

    int vertices_count() const override;

    std::vector<int> get_next_vertices(int vertex) const override;
    std::vector<int> get_prev_vertices(int vertex) const override;

private:
    std::vector<std::vector<bool>> adjacency_matrix;
};

#endif  // ALGORITHMS_MATRIX_GRAPH_H
