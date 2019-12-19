//Требуется отыскать самый выгодный маршрут между городами.
//Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.
//Формат входных данных.
//Первая строка содержит число N – количество городов.
//Вторая строка содержит число M - количество дорог.
//Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
//Последняя строка содержит маршрут (откуда и куда нужно доехать).
//Формат выходных данных.
//Вывести длину самого выгодного маршрута.

#include <iostream>
#include <cassert>
#include <vector>
#include <set>

typedef std::pair<int, int> Edge;

class CListGraph {
public:
    explicit CListGraph(int n) : adjacency_lists(n) {}

    void add_edge(int from, int to, int value) {
        assert(from >= 0 && from < adjacency_lists.size());
        assert(to >= 0 && to < adjacency_lists.size());
        adjacency_lists[from].emplace_back(to, value);
    }

    int vertices_count() const {
        return adjacency_lists.size();
    }

    std::vector<Edge> get_next_vertices(int vertex) const {
        assert(vertex >= 0 && vertex < adjacency_lists.size());
        return adjacency_lists[vertex];
    }

    std::vector<Edge> get_prev_vertices(int vertex) const {
        std::vector<Edge> vertices;

        for (int from = 0; from < adjacency_lists.size(); from++) {
            for (auto to : adjacency_lists[from]) {
                if (to.first == vertex) {
                    vertices.emplace_back(from, to.second);
                }
            }
        }
        return vertices;
    }

private:
    std::vector<std::vector<Edge>> adjacency_lists;
};

std::vector<int> find_shortest_distances(const CListGraph &graph, int start_vertex) {
    std::vector<int> distances(graph.vertices_count(), INT32_MAX);
    distances[start_vertex] = 0;
    std::vector<int> parents(graph.vertices_count(), -1);

    std::set<std::pair<int, int>> set;
    set.emplace(0, start_vertex);

    while (!set.empty()) {
        auto current_vertex = set.erase(set.begin());

        for (auto vertex : graph.get_next_vertices(current_vertex->second)) {
            if (distances[vertex.first] == INT32_MAX) {
//                distances[vertex.first];
            }
        }
    }

    return distances;
}

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    CListGraph graph(n);

    int from = 0, to = 0, value = 0;
    for (int i = 0; i < m; i++) {
        std::cin >> from >> to >> value;
        graph.add_edge(from, to, value);
    }

    int start_vertex = 0, end_vertex = 0;
    std::cin >> start_vertex >> end_vertex;
    std::vector<int> distances = find_shortest_distances(graph, start_vertex);
    std::cout << distances[end_vertex];

    return 0;
}
