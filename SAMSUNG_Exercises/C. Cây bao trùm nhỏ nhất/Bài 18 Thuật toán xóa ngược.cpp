#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

class Graph {
    int V;
    vector<vector<int>> adj;
    void DFS(int v, vector<bool>& visited);

public:
    vector<Edge> edges;
    Graph(int V);
    void addEdge(int u, int v, int weight);
    void removeEdge(int u, int v);
    bool isConnected();
    vector<Edge> findMST();
};

Graph::Graph(int V) : V(V), adj(V) {}

void Graph::addEdge(int u, int v, int weight) {
    edges.push_back({u, v, weight});
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void Graph::removeEdge(int u, int v) {
    adj[u].erase(remove(adj[u].begin(), adj[u].end(), v), adj[u].end());
    adj[v].erase(remove(adj[v].begin(), adj[v].end(), u), adj[v].end());
}

void Graph::DFS(int v, vector<bool>& visited) {
    visited[v] = true;
    for (int u : adj[v])
        if (!visited[u])
            DFS(u, visited);
}

bool Graph::isConnected() {
    vector<bool> visited(V, false);
    DFS(0, visited);
    return all_of(visited.begin(), visited.end(), [](bool v) { return v; });
}

vector<Edge> Graph::findMST() {
    sort(edges.begin(), edges.end(), greater<Edge>());
    vector<Edge> mst;
    for (auto& e : edges) {
        removeEdge(e.u, e.v);
        if (!isConnected()) {
            addEdge(e.u, e.v, e.weight);
            mst.push_back(e);
        }
    }
    return mst;
}

int main() {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 15);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);

    vector<Edge> mst = g.findMST();
    for (Edge& e : mst)
        cout << e.u << " - " << e.v << " : " << e.weight << endl;
    return 0;
}
