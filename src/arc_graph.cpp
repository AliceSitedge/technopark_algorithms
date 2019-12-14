#include <cassert>

#include "arc_graph.h"


ArcGraph::ArcGraph(int n) : size(n) {}

ArcGraph::ArcGraph(const IGraph &graph) : size(graph.vertices_count()) {
    for (int from = 0; from < graph.vertices_count(); from++) {
        for (auto to : graph.get_next_vertices(from)) {
            edges.emplace_back(from, to);
        }
    }
}

void ArcGraph::add_edge(int from, int to) {
    assert(from >= 0 && from < size);
    assert(to >= 0 && to < size);
    edges.emplace_back(from, to);
}

int ArcGraph::vertices_count() const {
    return size;
}

std::vector<int> ArcGraph::get_next_vertices(int vertex) const {
    std::vector<int> vertices;

    for (auto edge : edges) {
        if (edge.first == vertex) {
            vertices.push_back(edge.second);
        }
    }
    return vertices;
}

std::vector<int> ArcGraph::get_prev_vertices(int vertex) const {
    std::vector<int> vertices;

    for (auto edge : edges) {
        if (edge.second == vertex) {
            vertices.push_back(edge.first);
        }
    }
    return vertices;
}
