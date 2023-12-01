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

class DisjointSets {
public:
    vector<int> parent, rank;
    DisjointSets(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x);
    void unite(int x, int y);
};

class Graph {
    int V;
    vector<Edge> edges;
public:
    Graph(int V) : V(V) {}
    void addEdge(int u, int v, int w);
    vector<Edge> boruvkaMST();
};

int DisjointSets::find(int x) {
    if (x != parent[x])
        parent[x] = find(parent[x]);
    return parent[x];
}

void DisjointSets::unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) return;
    if (rank[rootX] < rank[rootY])
        parent[rootX] = rootY;
    else if (rank[rootY] < rank[rootX])
        parent[rootY] = rootX;
    else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

void Graph::addEdge(int u, int v, int w) {
    edges.push_back({u, v, w});
}

vector<Edge> Graph::boruvkaMST() {
    DisjointSets sets(V);
    vector<Edge> mst;
    int numTrees = V;
    vector<Edge> cheapest(V);

    while (numTrees > 1) {
        for (int i = 0; i < V; i++)
            cheapest[i] = {0, 0, INT_MAX};

        for (Edge& e : edges) {
            int setU = sets.find(e.u);
            int setV = sets.find(e.v);
            if (setU != setV) {
                if (e.weight < cheapest[setU].weight) cheapest[setU] = e;
                if (e.weight < cheapest[setV].weight) cheapest[setV] = e;
            }
        }

        for (int i = 0; i < V; i++) {
            Edge& e = cheapest[i];
            if (e.weight == INT_MAX) continue;
            int setU = sets.find(e.u);
            int setV = sets.find(e.v);
            if (setU != setV) {
                mst.push_back(e);
                sets.unite(setU, setV);
                numTrees--;
            }
        }
    }
    return mst;
}

int main() {
    int V = 4;
    Graph g(V);
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 6);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 3, 15);

    vector<Edge> mst = g.boruvkaMST();
    cout << "Cây bao trùm nhỏ nhất:\n";
    for (Edge& e : mst)
        cout << e.u << " - " << e.v << " : " << e.weight << endl;
    return 0;
}

