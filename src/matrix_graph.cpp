#include <cassert>

#include "matrix_graph.h"


MatrixGraph::MatrixGraph(int n) : adjacency_matrix(n, std::vector<bool>(n, false)) {}

MatrixGraph::MatrixGraph(const IGraph &graph) : adjacency_matrix(graph.vertices_count(),
                                                                 std::vector<bool>(graph.vertices_count(), false)) {
    for (int from = 0; from < graph.vertices_count(); from++) {
        for (auto to : graph.get_next_vertices(from)) {
            adjacency_matrix[from][to] = true;
        }
    }
}

void MatrixGraph::add_edge(int from, int to) {
    assert(from >= 0 && from <= adjacency_matrix.size());
    assert(to >= 0 && to <= adjacency_matrix.size());
    adjacency_matrix[from][to] = true;
}

int MatrixGraph::vertices_count() const {
    return adjacency_matrix.size();
}

std::vector<int> MatrixGraph::get_next_vertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjacency_matrix.size());
    std::vector<int> vertices;

    for (int i = 0; i < adjacency_matrix[vertex].size(); i++) {
        if (adjacency_matrix[vertex][i] == true) {
            vertices.push_back(i);
        }
    }
    return vertices;
}

std::vector<int> MatrixGraph::get_prev_vertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjacency_matrix.size());
    std::vector<int> vertices;

    for (int from = 0; from < adjacency_matrix.size(); from++) {
        if (adjacency_matrix[from][vertex] == true) {
            vertices.push_back(from);
        }
    }
    return vertices;
}
