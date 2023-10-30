#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, cost;

    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
};

vector<int> parent;

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        parent[b] = a;
}

int main() {
    ifstream infile("connection.txt");
    ofstream outfile("connection.out");
    if (!infile.is_open() || !outfile.is_open()) {
        cerr << "Error opening files!" << endl;
        return 1;
    }

    int n, m;
    infile >> n >> m;

    vector<Edge> edges(m);
    parent.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < m; i++) {
        infile >> edges[i].u >> edges[i].v >> edges[i].cost;
    }

    sort(edges.begin(), edges.end());

    int total_cost = 0;
    vector<Edge> minimum_spanning_tree;

    for (Edge edge : edges) {
        if (find_set(edge.u) != find_set(edge.v)) {
            union_sets(edge.u, edge.v);
            total_cost += edge.cost;
            minimum_spanning_tree.push_back(edge);
        }
    }

    outfile << total_cost << endl;

    for (Edge edge : minimum_spanning_tree) {
        outfile << edge.u << " " << edge.v << " " << edge.cost << endl;
    }

    infile.close();
    outfile.close();

    return 0;
}
