#include <cassert>

#include "set_graph.h"


SetGraph::SetGraph(int n) : edges(n) {}

SetGraph::SetGraph(const IGraph &graph) : edges(graph.vertices_count()) {
    for (int from = 0; from < graph.vertices_count(); from++) {
        for (auto to : graph.get_next_vertices(from)) {
            edges[from].insert(to);
        }
    }
}

void SetGraph::add_edge(int from, int to) {
    assert(from >= 0 && from < edges.size());
    assert(to >= 0 && to < edges.size());
    edges[from].insert(to);
}

int SetGraph::vertices_count() const {
    return edges.size();
}

std::vector<int> SetGraph::get_next_vertices(int vertex) const {
    assert(vertex >= 0 && vertex < edges.size());
    return std::vector<int>(edges[vertex].begin(), edges[vertex].end());
}

std::vector<int> SetGraph::get_prev_vertices(int vertex) const {
    std::vector<int> vertices;

    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].find(vertex) != edges[i].end()) {
            vertices.push_back(i);
        }
    }
    return vertices;
}
