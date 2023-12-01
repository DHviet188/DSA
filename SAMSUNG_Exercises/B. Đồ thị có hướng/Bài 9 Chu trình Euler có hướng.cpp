#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std;

class Graph {
    int V;
    vector<list<int>> adj;

    bool isStronglyConnected();
    void DFSUtil(int v, vector<bool>& visited);

public:
    Graph(int V);
    void addEdge(int u, int v);
    bool hasEulerianCycle();
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
}

void Graph::DFSUtil(int v, vector<bool>& visited) {
    visited[v] = true;
    for (int next : adj[v])
        if (!visited[next])
            DFSUtil(next, visited);
}

bool Graph::isStronglyConnected() {
    vector<bool> visited(V, false);
    DFSUtil(0, visited);
    for (bool v : visited)
        if (!v) return false;

    Graph gr(V);
    for (int v = 0; v < V; v++)
        for (int i : adj[v])
            gr.addEdge(i, v);

    fill(visited.begin(), visited.end(), false);
    gr.DFSUtil(0, visited);
    for (bool v : visited)
        if (!v) return false;

    return true;
}

bool Graph::hasEulerianCycle() {
    if (!isStronglyConnected()) return false;

    vector<int> in_degree(V, 0), out_degree(V, 0);
    for (int u = 0; u < V; u++)
        for (int v : adj[u]) {
            out_degree[u]++;
            in_degree[v]++;
        }

    for (int i = 0; i < V; i++)
        if (in_degree[i] != out_degree[i])
            return false;

    return true;
}

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(0, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);

    if (g.hasEulerianCycle())
        cout << "Đồ thị có chu trình Euler." << endl;
    else
        cout << "Đồ thị không có chu trình Euler." << endl;

    return 0;
}
