#include <iostream>
#include <functional>
#include <queue>

#include "list_graph.h"


void bfs(const IGraph &graph, std::vector<bool> &visited, int vertex, const std::function<void(int)> &func) {
    visited[vertex] = true;
    std::queue<int> queue;
    queue.push(vertex);
    
    while (!queue.empty()) {
        int current_vertex = queue.front();
        queue.pop();

        func(current_vertex);
        for (auto next_vertex : graph.get_next_vertices(current_vertex)) {
            if (!visited[next_vertex]) {
                queue.push(next_vertex);
                visited[next_vertex] = true;
            }
        }
    }
}

void main_bfs(const IGraph &graph, const std::function<void(int)> &func) {
    std::vector<bool> visited(graph.vertices_count(), false);

    for (int i = 0; i < graph.vertices_count(); i++) {
        if (!visited[i]) {
            bfs(graph, visited, i, func);
        }
    }
}

void print(const IGraph &graph) {
    main_bfs(graph, [](int vert) {std::cout << vert << ' ';});
    std::cout << std::endl;
}

int main() {
    ListGraph graph(5);
    graph.add_edge(0, 2);
    graph.add_edge(0, 4);
    graph.add_edge(1, 0);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(2, 4);
    graph.add_edge(3, 2);
    print(graph);

    ListGraph graph1(graph);
    print(graph1);

    return 0;
}
