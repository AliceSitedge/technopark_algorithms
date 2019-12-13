#include "list_graph.h"


ListGraph::ListGraph(int n) : adjacency_lists(n) {}

ListGraph::ListGraph(const IGraph &graph) : adjacency_lists(graph.vertices_count()) {
    for (int i = 0; i < adjacency_lists.size(); i++) {
        adjacency_lists[i] = graph.get_next_vertices(i);
    }
}

void ListGraph::add_edge(int from, int to) {
    assert(from >= 0 && from < adjacency_lists.size());
    assert(to >= 0 && to < adjacency_lists.size());
    adjacency_lists[from].push_back(to);
}

int ListGraph::vertices_count() const {
    return adjacency_lists.size();
}

std::vector<int> ListGraph::get_next_vertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjacency_lists.size());
    return adjacency_lists[vertex];
}

std::vector<int> ListGraph::get_prev_vertices(int vertex) const {
    std::vector<int> vertices;

    for (int from = 0; from < adjacency_lists.size(); from++) {
        for (auto to : adjacency_lists[from]) {
            if (to == vertex) {
                vertices.push_back(from);
            }
        }
    }
    return vertices;
}
