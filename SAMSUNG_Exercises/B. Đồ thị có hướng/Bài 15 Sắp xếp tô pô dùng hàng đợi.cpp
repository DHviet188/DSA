#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V);
    void addEdge(int u, int v);
    void topologicalSort();
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
}

void Graph::topologicalSort() {
    vector<int> indegree(V, 0);
    for (int u = 0; u < V; u++)
        for (int i : adj[u])
            indegree[i]++;

    queue<int> q;
    for (int i = 0; i < V; i++)
        if (indegree[i] == 0)
            q.push(i);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";
        for (int v : adj[u]) {
            if (--indegree[v] == 0)
                q.push(v);
        }
    }
}

int main() {
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    cout << "Thứ tự tô pô của đồ thị: ";
    g.topologicalSort();

    return 0;
}
