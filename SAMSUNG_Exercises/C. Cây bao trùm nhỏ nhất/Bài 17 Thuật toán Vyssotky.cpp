#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

class UnionFind {
public:
    vector<int> parent;
    UnionFind(int n) : parent(n) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            parent[x] = y;
        }
    }
};

vector<Edge> findMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    UnionFind uf(V);
    vector<Edge> result;
    for (Edge e : edges) {
        if (uf.find(e.u) != uf.find(e.v)) {
            result.push_back(e);
            uf.unite(e.u, e.v);
        }
    }
    return result;
}

int main() {
    int V = 4;
    vector<Edge> edges = {{0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};
    vector<Edge> mst = findMST(V, edges);
    for (Edge e : mst)
        cout << e.u << " - " << e.v << " : " << e.weight << endl;
    return 0;
}
