// Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то
// вершинами. Найдите количество различных кратчайших путей между зад анными вершинами.
// Требования: сложность O(V+E).
// Формат ввода.
// v: кол-во вершин (макс. 50000),
// n: кол-во ребер (макс. 200000),
// n пар реберных вершин,
// пара вершин u, w для запроса.
// Формат вывода.
// Количество кратчайших путей от u к w.

#include<iostream>
#include <queue>
#include <cassert>


class CListGraph {
public:
    explicit CListGraph(int n) : adjacency_lists(n) {}

    void add_edge(int from, int to) {
        assert(from >= 0 && from < adjacency_lists.size());
        assert(to >= 0 && to < adjacency_lists.size());
        adjacency_lists[from].push_back(to);
    }

    int vertices_count() const {
        return adjacency_lists.size();
    }

    std::vector<int> get_next_vertices(int vertex) const {
        assert(vertex >= 0 && vertex < adjacency_lists.size());
        return adjacency_lists[vertex];
    }

    std::vector<int> get_prev_vertices(int vertex) const {
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

private:
    std::vector<std::vector<int>> adjacency_lists;
};

std::vector<int> bfs(const CListGraph &graph, int start_vertex) {
    std::vector<int> distances(graph.vertices_count(), INT32_MAX);
    distances[start_vertex] = 0;
    std::vector<int> path_amounts(graph.vertices_count(), 0);
    path_amounts[start_vertex] = 1;

    std::queue<int> queue;
    queue.push(start_vertex);

    while (!queue.empty()) {
        int current_vertex = queue.front();
        queue.pop();

        for (auto vertex : graph.get_next_vertices(current_vertex)) {
            if (distances[vertex] > distances[current_vertex] + 1) {
                distances[vertex] = distances[current_vertex] + 1;
                path_amounts[vertex] = path_amounts[current_vertex];
                queue.push(vertex);
            } else if (distances[vertex] == distances[current_vertex] + 1) {
                path_amounts[vertex] += path_amounts[current_vertex];
            }
        }
    }
    return path_amounts;
}

int main() {
    int v = 0, n = 0;
    std::cin >> v >> n;
    CListGraph graph(v);

    int u = 0, w = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> u >> w;
        graph.add_edge(u, w);
        graph.add_edge(w, u);
    }

    int start_vertex = 0, end_vertex = 0;
    std::cin >> start_vertex >> end_vertex;
    std::vector<int> path_amounts = bfs(graph, start_vertex);
    std::cout << path_amounts[end_vertex];

    return 0;
}
