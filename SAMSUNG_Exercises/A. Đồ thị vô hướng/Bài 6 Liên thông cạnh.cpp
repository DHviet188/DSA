#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Graph {
    int V;
    list<int> *adj;
    void bridgeUtil(int v, vector<bool> &visited, vector<int> &disc,
                    vector<int> &low, vector<int> &parent);

public:
    Graph(int V);
    void addEdge(int v, int w);
    bool isEdgeConnected();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::bridgeUtil(int v, vector<bool> &visited, vector<int> &disc,
                       vector<int> &low, vector<int> &parent) {
    static int time = 0;
    visited[v] = true;
    disc[v] = low[v] = ++time;
    for (int i : adj[v]) {
        if (!visited[i]) {
            parent[i] = v;
            bridgeUtil(i, visited, disc, low, parent);
            low[v] = min(low[v], low[i]);
            if (low[i] > disc[v]) {
                cout << "Not Edge Connected";
            }
        }
        else if (i != parent[v])
            low[v] = min(low[v], disc[i]);
    }
}

bool Graph::isEdgeConnected() {
    vector<bool> visited(V, false);
    vector<int> disc(V), low(V), parent(V, -1);

    try {
        for (int i = 0; i < V; i++)
            if (!visited[i])
                bridgeUtil(i, visited, disc, low, parent);
    } catch (const char *msg) {
        return false;
    }
    return true;
}
