#include <iostream>
#include <unordered_map>
#include <utility>

using namespace std;

typedef pair<int, int> Edge;

pair<int,int> make_edge(int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    return Edge(a, b);
}

int count_parallel_edges(int edges[][2], int n) {
    unordered_map<Edge, int, hash<Edge>> edge_count;
    int parallel_edges = 0;

    for (int i = 0; i < n; ++i) {
        Edge e = make_edge(edges[i][0], edges[i][1]);
        edge_count[e]++;

        if (edge_count[e] > 1) {
            parallel_edges++;
        }
    }

    return parallel_edges;
}

int main() {
    int edges[][2] = {{0, 1}, {1, 2}, {0, 1}};
    int n = sizeof(edges) / sizeof(edges[0]);

    cout << "Số cạnh song song: " << count_parallel_edges(edges, n) << endl;

    return 0;
}
